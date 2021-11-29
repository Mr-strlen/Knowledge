import tkinter as tk
from tkinter import ttk,filedialog,messagebox
from PIL import Image, ImageTk
import numpy as np
import cv2
import os,math
from matplotlib.backends.backend_tkagg import (
    FigureCanvasTkAgg, NavigationToolbar2Tk)
from matplotlib.backend_bases import key_press_handler
from matplotlib.figure import Figure

class MedicalPhoto(object):
    def __init__(self,width=0,height=0,origin_data=0):
        self.width=width
        self.height=height
        self.origin_data=origin_data
        self.enhance_data=0 #处理后的数据
        self.watch_data=0 #在缩放显示后的数据（图层）
        #记录操作
        self.gray=[0,4095]
        self.liner_a=1
        self.log_c=1
        self.gamma=0
        self.histequal=False
        self.gray_reserve=False
        self.localpre_h=0
        self.localpre_w=0
        self.enlarge=1
        self.rotation=0
        self.mirror='none'
        self.transp=False
        self.sharpfilter='none'
        self.highabfilter=False
        self.smoothfilter='none'
        self.filter_size='3x3'
        #记录上一次操作
        self.last_gray=[0,4095]
        self.last_liner_a=1
        self.last_log_c=1
        self.last_gamma=0
        self.last_histequal=False
        self.last_gray_reserve=False
        self.last_localpre_h=0
        self.last_localpre_w=0
        self.last_enlarge=1
        self.last_rotation=0
        self.last_mirror='none'
        self.last_transp=False
        self.last_sharpfilter='none'
        self.last_highabfilter=False
        self.last_smoothfilter='none'
        self.last_filter_size='3x3'
        

## 初始化
win=tk.Tk()
# 设置窗体大小
win_w=1050
win_h=650
# 窗体居中
w_t=win.winfo_screenwidth()
h_t=win.winfo_screenheight()
x=(w_t-win_w)/2.0
y=(h_t-win_h)/2.0
win.geometry("%dx%d+%d+%d" % (win_w, win_h, x, y))
win.resizable(0, 0)  # 设置窗口大小不可变
win.configure(bg='#3c3f41') #背景色
win.title("x光医疗图像处理系统")

##不同部分设计
#标题
frame_title=tk.Frame(win,width=1050, height=30, bg='#3c3f41')
frame_title.grid(row=0,column=0,columnspan=3)
frame_title.grid_propagate(0) #设置为0可使组件大小不变
temp=tk.Label(frame_title,text="医 疗 图 像 预 处 理 系 统",font=('microsoft yahei', 13, 'bold'),bg='#3c3f41')
temp.grid(row=1)

#图片显示
frame_img=tk.Frame(win,height=600,width=400,padx=5,pady=5,bg='white')
frame_img.grid(row=1,column=0,rowspan=4)
frame_img.grid_propagate(0)
      
''' 文件操作 '''
# 读取raw文件 并创建图片对象
m_photo=MedicalPhoto()
def fileopen(filepath):
    f = open(filepath, 'rb')
    width=int.from_bytes(f.read(4), byteorder='little', signed=False)
    height=int.from_bytes(f.read(4), byteorder='little', signed=False)
    data=[]
    for i in range(0,height):
        temp=[]
        for j in range(0, width):
            t=int.from_bytes(f.read(2), byteorder='little', signed=False) & 4095
            temp.append(t)
        data.append(temp)
    f.close()
    m_photo.origin_data=np.array(data,dtype="uint16")

    m_photo.height=height
    m_photo.width=width
    m_photo.enhance_data=graywindowmap()
    m_photo.watch_data=m_photo.enhance_data

# 文件写入
def filesave(filepath):
    f=open(filepath,"wb")
    tmp=m_photo.width.to_bytes(length=4, byteorder='little', signed=False)
    f.write(tmp)
    tmp=m_photo.height.to_bytes(length=4, byteorder='little', signed=False)
    f.write(tmp)
    # 反向拓展到0-4095
    data=np.round((m_photo.enhance_data-np.min(m_photo.enhance_data))/(np.max(m_photo.enhance_data)-np.min(m_photo.enhance_data))*4095.0)
    for i in range(0,m_photo.height):
        for j in range(0,m_photo.width):
            t=int(data[i,j])
            tmp=t.to_bytes(length=2, byteorder='little', signed=False)
            f.write(tmp)
    f.close()


## 灰度窗映射
def graywindowmap():
    new_img=np.zeros((m_photo.height,m_photo.width))
    new_img=m_photo.origin_data.astype(np.float64)
    new_img=(new_img-m_photo.gray[0])/(m_photo.gray[1]-m_photo.gray[0])*255.0
    new_img[new_img>255]=255
    new_img[new_img<0]=0
    # for i in range(0,m_photo.height):
    #     for j in range(0,m_photo.width):
    #         if m_photo.origin_data[i,j]<m_photo.gray[0]:
    #             new_img[i,j]=0
    #         elif m_photo.origin_data[i,j]>m_photo.gray[1]:
    #             new_img[i,j]=255
    #         else:
    #             new_img[i,j]=(m_photo.origin_data[i,j]-m_photo.gray[0])/(m_photo.gray[1]-m_photo.gray[0])*255.0
    return new_img

#对所有可控制的参数进行校准
def InitParm():
    e_graylow.delete(0,4)
    e_graylow.insert(0,str(m_photo.gray[0]))
    e_grayhigh.delete(0,10)
    e_grayhigh.insert(0,str(m_photo.gray[1]))
    e_line_a.delete(0,4)
    e_line_a.insert(0,str(m_photo.liner_a))
    e_log_c.delete(0,4)
    e_log_c.insert(0,str(m_photo.log_c))
    s_gamma.set(m_photo.gamma)
    if m_photo.histequal:
        c_hist.select()
    else:
        c_hist.deselect()
    if m_photo.gray_reserve:
        c_reverse.select()
    else:
        c_reverse.deselect()
    s_height.set(m_photo.localpre_h)
    s_width.set(m_photo.localpre_w)
    if float(m_photo.enlarge)==1:
        s_enlage.set(0)
    elif float(m_photo.enlarge)<1:
        s_enlage.set(int(-1/m_photo.enlarge))
    s_revolve.set(m_photo.rotation)
    combo_mirror.set(m_photo.mirror)
    if m_photo.transp:
        c_transp.select()
    else:
        c_transp.deselect()
    combo_sharp.set(m_photo.sharpfilter)
    if m_photo.highabfilter:
        c_highabfilter.select()
    else:
        c_highabfilter.deselect()
    combo_smooth.set(m_photo.smoothfilter)
    combo_filtersize.set(m_photo.filter_size)


# 记录上一步操作
def RecordGrayStep():
    m_photo.last_gray=m_photo.gray
    m_photo.last_liner_a=m_photo.liner_a
    m_photo.last_log_c=m_photo.log_c
    m_photo.last_gamma=m_photo.gamma
    m_photo.last_histequal=m_photo.histequal
    m_photo.last_gray_reserve=m_photo.gray_reserve
    m_photo.last_localpre_h=m_photo.localpre_h
    m_photo.last_localpre_w=m_photo.localpre_w
    m_photo.last_enlarge=m_photo.enlarge
    m_photo.last_rotation=m_photo.rotation
    m_photo.last_mirror=m_photo.mirror
    m_photo.last_transp=m_photo.transp

def RecordEnhanceStep():
    m_photo.last_sharpfilter=m_photo.sharpfilter
    m_photo.last_highabfilter=m_photo.highabfilter
    m_photo.last_smoothfilter=m_photo.smoothfilter
    m_photo.last_filter_size=m_photo.filter_size


#进行灰度相关的变换
def GrayChange():
    if m_photo.gray[0]==m_photo.last_gray[0] and m_photo.gray[1]==m_photo.last_gray[1] and\
    m_photo.liner_a==m_photo.last_liner_a and m_photo.log_c==m_photo.last_log_c and m_photo.gamma==m_photo.last_gamma and\
    m_photo.last_histequal==m_photo.histequal and m_photo.last_gray_reserve==m_photo.gray_reserve and\
    m_photo.sharpfilter==m_photo.last_sharpfilter and m_photo.last_smoothfilter==m_photo.smoothfilter and\
    m_photo.highabfilter==m_photo.last_highabfilter and m_photo.filter_size==m_photo.last_filter_size:
        #未进行任何操作
        temp=m_photo.enhance_data
        
    else:
        #灰度映射
        temp=graywindowmap()
        height,width=np.shape(temp)
        # 线性变换
        if m_photo.liner_a!=1:
            for y in range(height):
                for x in range(width):
                    t=int(temp[y,x])*m_photo.liner_a
                    if t>255:
                        temp[y,x]=255
                    elif t<0:
                        temp[y,x]=0
                    else:
                        temp[y,x]=t
        # 指数变换
        if m_photo.log_c!=1:
            for y in range(height):
                for x in range(width):
                    t=np.log(int(temp[y,x])+1)*m_photo.log_c
                    if t>255:
                        temp[y,x]=255
                    elif t<0:
                        temp[y,x]=0
                    else:
                        temp[y,x]=t                   
        # Gamma变换
        if m_photo.gamma!=0:
            for y in range(height):
                for x in range(width):
                    t=int(temp[y,x])/255
                    t=int(pow(t,m_photo.gamma)*255)
                    if t>255:
                        temp[y,x]=255
                    elif t<0:
                        temp[y,x]=0
                    else:
                        temp[y,x]=t
        #直方图均衡化
        if m_photo.histequal:
#            temp = cv2.equalizeHist(temp.astype(np.uint8))
#            res = np.hstack((temp.astype(np.uint8),temp))
            clahe = cv2.createCLAHE(clipLimit=2.0, tileGridSize=(8,8))
            temp = clahe.apply(temp.astype(np.uint8))
        height,width=np.shape(temp)
        #图像反转
        if m_photo.gray_reserve:
            temp=np.ones((height,width),dtype=np.uint8)*255-temp.astype(np.uint8)
    m_photo.enhance_data=temp
    RecordGrayStep()

#进行图像增强
def EnhanceChange():
    if m_photo.gray[0]==m_photo.last_gray[0] and m_photo.gray[1]==m_photo.last_gray[1] and\
        m_photo.liner_a==m_photo.last_liner_a and m_photo.log_c==m_photo.last_log_c and m_photo.gamma==m_photo.last_gamma and\
        m_photo.last_histequal==m_photo.histequal and m_photo.last_gray_reserve==m_photo.gray_reserve and\
        m_photo.sharpfilter==m_photo.last_sharpfilter and m_photo.last_smoothfilter==m_photo.smoothfilter and\
        m_photo.highabfilter==m_photo.last_highabfilter and m_photo.filter_size==m_photo.last_filter_size:
        #未进行任何操作
        temp=m_photo.enhance_data
    else:
        # 锐化滤波
        temp=m_photo.enhance_data
        #高斯滤波
        #gaussianBlur=cv2.GaussianBlur(temp.astype(np.uint8),(3,3),0)
        gaussianBlur=temp.astype(np.uint8)
        ret,binary=cv2.threshold(gaussianBlur,127,255,cv2.THRESH_BINARY) #
        if m_photo.sharpfilter=="Roberts":
            #Roberts算子
            kernelx=np.array([[-1,0],[0,1]],dtype=int)
            kernely=np.array([[0,-1],[1,0]],dtype=int)
            x=cv2.filter2D(binary,cv2.CV_16S,kernelx)
            y=cv2.filter2D(binary,cv2.CV_16S,kernely)
            absX=cv2.convertScaleAbs(x)
            absY=cv2.convertScaleAbs(y)
            temp=cv2.addWeighted(absX,0.5,absY,0.5,0)
        elif m_photo.sharpfilter=="Prewitt":
            #Prewitt算子
            kernelx=np.array([[1,1,1],[0,0,0],[-1,-1,-1]],dtype=int)
            kernely=np.array([[-1,0,1],[-1,0,1],[-1,0,1]],dtype=int)
            x=cv2.filter2D(binary,cv2.CV_16S,kernelx)
            y=cv2.filter2D(binary,cv2.CV_16S,kernely)
            absX=cv2.convertScaleAbs(x)
            absY=cv2.convertScaleAbs(y)
            temp=cv2.addWeighted(absX,0.5,absY,0.5,0)
        elif m_photo.sharpfilter=="Sobel":
            #Sobel算子
            x=cv2.Sobel(binary,cv2.CV_16S,1,0)
            y=cv2.Sobel(binary,cv2.CV_16S,0,1)
            absX=cv2.convertScaleAbs(x)
            absY=cv2.convertScaleAbs(y)
            temp=cv2.addWeighted(absX,0.5,absY,0.5,0)
        elif m_photo.sharpfilter=="Laplacian":
            #拉普拉斯算法
            dst=cv2.Laplacian(binary,cv2.CV_16S,ksize=3)
            temp=cv2.convertScaleAbs(dst)
        
        #高提升滤波
        if m_photo.highabfilter:
            A=2
            print("ok")
            height,width=np.shape(temp)
            new_img=np.zeros((height,width),dtype=np.float64)
            filter_core=np.array([[0,1,0],[1,-4,1],[0,1,0]])
#            filter_core=np.array([[1,1,1],[1,-8,1],[1,1,1]])
#            filter_core=np.array([[1,4,1],[4,-20,4],[1,4,1]])
            for y in range(1,height-1):
                for x in range(1,width-1):
                    t=np.sum(filter_core*temp[y-1:y+2,x-1:x+2])
                    if t<-255:
                        t=-255
                    if t>255:
                        t=255
                    new_img[y,x]=A*temp[y,x]-t
            # 映射回0-255
            new_img=255.0*(new_img-np.min(new_img))/(np.max(new_img)-np.min(new_img))
            temp=np.round(new_img)
            
        #平滑滤波
        if m_photo.filter_size=="3x3":
            k=3
        elif m_photo.filter_size=="5x5":
            k=5
        elif m_photo.filter_size=="7x7":
            k=7
        elif m_photo.filter_size=="9x9":
            k=9

        if m_photo.smoothfilter=="Average":
            temp=cv2.blur(temp.astype(np.uint8),(k,k))
        elif m_photo.smoothfilter=="Median":
            temp=cv2.medianBlur(temp.astype(np.uint8),k)
        elif m_photo.smoothfilter=="Gaussian":
            temp=cv2.GaussianBlur(temp.astype(np.uint8),(k,k),0)

    m_photo.enhance_data=temp  
    RecordEnhanceStep()
    

# 显示图片
def ShowImg():
    if m_photo.height==0:
        tk.messagebox.showwarning('警告','未导入图片')
        return 0
    InitParm()
    GrayChange()
    EnhanceChange()
    #对可视化图层进行操作
    if m_photo.enlarge==1 and m_photo.rotation==0 and m_photo.mirror=='none' and m_photo.transp==False:#没有操作
        m_photo.watch_data=m_photo.enhance_data
    else:
        temp=m_photo.enhance_data
        
        if m_photo.enlarge!=1: #放大
            temp=cv2.resize(m_photo.enhance_data,(0,0), fx=m_photo.enlarge, fy=m_photo.enlarge, interpolation=cv2.INTER_CUBIC)
        if m_photo.rotation!=0: #旋转
            h_t,w_t=np.shape(temp)
            matRotate = cv2.getRotationMatrix2D((int(h_t*0.5),int(w_t*0.5)), m_photo.rotation, 1) # mat rotate 1 center 2 angle 3 缩放系数
            temp = cv2.warpAffine(temp,matRotate,(h_t,w_t))
        
        h_t,w_t=np.shape(temp)
        tempi=np.zeros((h_t,w_t),dtype=np.uint8)
        if m_photo.mirror=="vertical": #镜像
            for y in range(h_t):
                for x in range(w_t):
                    tempi[y,x]=temp[h_t-1-y,x]
            temp=tempi
        elif m_photo.mirror=="horizontal":
            h_t,w_t=np.shape(temp)
            for y in range(h_t):
                for x in range(w_t):
                    tempi[y,x]=temp[y,w_t-1-x]
            temp=tempi
        if m_photo.transp!=False: #转置
            temp=np.transpose(temp)
        m_photo.watch_data=temp

    
    dt_h,dt_w=600,400 #画框的长款固定
    watch_h,watch_w=np.shape(m_photo.watch_data)
    if watch_h<=600 or watch_w<=400:
        new_pic=m_photo.watch_data
    else:
        start_h=int(np.floor(m_photo.localpre_h/100*(watch_h-600)))
        start_w=int(np.floor(m_photo.localpre_w/100*(watch_h-400)))
        new_pic=m_photo.watch_data[start_h:dt_h+start_h,start_w:start_w+dt_w]

    temp=new_pic.astype(np.uint8)
    
    img_change = Image.fromarray(temp)
    img_tk = ImageTk.PhotoImage(img_change)
    
    empty=np.ones((600,400),dtype=np.uint8)*255
    empty_change = Image.fromarray(empty)
    img_empty = ImageTk.PhotoImage(empty_change)
    image=tk.Label(frame_img,image=img_empty)
    image.image=img_empty
    image.place(x=0,y=0)
    
    image=tk.Label(frame_img,image=img_tk)
    image.image=img_tk
    image.place(x=0,y=0)
    
#打开目录选择文件 并显示图片
def OpenFile():
    filepath = filedialog.askopenfilename(initialdir=os.getcwd(),title=u"选择文件")
    fileopen(filepath)
    ShowImg()

def SaveFile():
    if m_photo.height==0:
        tk.messagebox.showwarning('警告','未导入图片')
        return 
    filepath = filedialog.askdirectory(initialdir=os.getcwd(),title=u"选择文件夹")
    print(filepath)
    filesave(filepath+'/new_image.raw')

# 还原到原始状态
def ReturnBack():
    m_photo.gray=[0,4095]
    if m_photo.height==0:
        m_photo.enhance_data=m_photo.origin_data
        tk.messagebox.showwarning('警告','未导入图片')
    else:
        m_photo.enhance_data=graywindowmap()
    m_photo.watch_data=m_photo.enhance_data
    
    m_photo.liner_a=1
    m_photo.log_c=1
    m_photo.gamma=0
    m_photo.histequal=False
    m_photo.gray_reserve=False
    m_photo.localpre_h=0
    m_photo.localpre_w=0
    m_photo.enlarge=1
    m_photo.rotation=0
    m_photo.mirror='none'
    m_photo.transp=False
    m_photo.sharpfilter='none'
    m_photo.highabfilter=False
    m_photo.smoothfilter='none'
    m_photo.filter_size='3x3'
    if m_photo.height!=0:
        ShowImg()
    
frame_file=tk.LabelFrame(win,width=300, height=70,padx=5,pady=5,text="文件操作",font=('microsoft yahei', 11, 'bold'),bg="lightyellow")
frame_file.grid(row=1,column=1)
frame_file.grid_propagate(0) 
open_file=tk.Button(frame_file, text='打开图像',command=OpenFile)
open_file.grid(padx=20,row=0,column=1)
save_file=tk.Button(frame_file, text='保存图像',command=SaveFile)
save_file.grid(padx=20,row=0,column=2)
origin_file=tk.Button(frame_file, text='原图像',command=ReturnBack)
origin_file.grid(padx=20,row=0,column=5)

''' 基本增强 '''
# 改变灰度映射区间
def GrayInterval():
    low_t=int(e_graylow.get())
    high_t=int(e_grayhigh.get())
    if low_t<0 or high_t>4095 or low_t>high_t:#异常判断
        tk.messagebox.showwarning('警告','灰度区间无效')
    else:
        m_photo.gray=[low_t,high_t]
        print(m_photo.gray)
        ShowImg()
    
# 线性变换
def GrayLinear():
    if m_photo.log_c!=1 or m_photo.gamma!=0:
        tk.messagebox.showwarning('警告','只能进行一种灰度变换')
        return 0
    line_a=float(e_line_a.get())
    m_photo.liner_a=line_a
    print(m_photo.liner_a)
    ShowImg()
# 对数变换
def GrayLog():
    if m_photo.liner_a!=1 or m_photo.gamma!=0:
        tk.messagebox.showwarning('警告','只能进行一种灰度变换')
        return 0
    line_a=float(e_log_c.get())
    m_photo.log_c=line_a
    print(m_photo.log_c)
    ShowImg()
# gamma变换
def GrayGamma():
    if m_photo.liner_a!=1 or m_photo.log_c!=1:
        tk.messagebox.showwarning('警告','只能进行一种灰度变换')
        return 0
    gamma=int(s_gamma.get())
    m_photo.gamma=gamma
    print(m_photo.gamma)
    ShowImg()
# 直方图均衡
def HistEqual():
    if hist_check.get()==1:
        m_photo.histequal=True
    else:
        m_photo.histequal=False
    print(m_photo.histequal)
    ShowImg()
# 灰度反转
def GrayReverse():
    if reverse_check.get()==1:
        m_photo.gray_reserve=True
    else:
        m_photo.gray_reserve=False
    print(m_photo.gray_reserve)
    ShowImg()

# 原图像灰度分布
def ShowOriginHist():
    if m_photo.height==0:
        tk.messagebox.showwarning('警告','未导入图片')
        return 0
    charts=tk.Toplevel()
    charts.wm_title("原图像直方图")

    fig = Figure(figsize=(5, 4), dpi=100)
    canvas = FigureCanvasTkAgg(fig, master=charts)  # A tk.DrawingArea.
    canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=1)
    toolbar = NavigationToolbar2Tk(canvas, charts)
    toolbar.update()
    canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=1)
    
    fig.clear()
    ax = fig.add_subplot(111)
    temp=m_photo.origin_data.astype(np.uint8)
    ax.hist(temp.ravel(),256,[0, 256])
    ax.set_yscale("log")
    canvas.draw()
    charts.mainloop()

# 均衡后灰度分布
def ShowChangeHist():
    if m_photo.height==0:
        tk.messagebox.showwarning('警告','未导入图片')
        return 0
    charts=tk.Toplevel()
    charts.wm_title("均衡后直方图")
    
    fig = Figure(figsize=(5, 4), dpi=100)
    canvas = FigureCanvasTkAgg(fig, master=charts)  # A tk.DrawingArea.
    canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=1)
    toolbar = NavigationToolbar2Tk(canvas, charts)
    toolbar.update()
    canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=1)
    
    fig.clear()
    ax = fig.add_subplot(111)
    temp=m_photo.enhance_data.astype(np.uint8)
    ax.hist(temp.ravel(),256,[0, 256])
    ax.set_yscale("log")
    canvas.draw()
    charts.mainloop()


frame_enhance=tk.LabelFrame(win,width=300, height=340,padx=5,pady=5,text="基本增强",font=('microsoft yahei', 11, 'bold'),bg="lightyellow")
frame_enhance.grid(row=2,column=1,rowspan=2)
frame_enhance.grid_propagate(0)
#第1行
tk.Label(frame_enhance, text="灰度区间选择").grid(padx=5,pady=5,row=0,column=0)
e_graylow=tk.Entry(frame_enhance,width=8)
e_graylow.grid(row=0,column=1)
e_graylow.insert(0,'0')
tk.Label(frame_enhance, text="—").grid(padx=5,pady=5,row=0,column=2)
e_grayhigh=tk.Entry(frame_enhance,width=8)
e_grayhigh.grid(row=0,column=3)
e_grayhigh.insert(0,'4095')
tk.Button(frame_enhance, text="确定",command=GrayInterval).grid(padx=10,pady=5,row=0,column=4)
#第2行
tk.Label(frame_enhance, text="线性变换").grid(padx=5,pady=5,row=1,column=0)
tk.Label(frame_enhance, text="a=").grid(padx=5,pady=5,row=1,column=1)
e_line_a=tk.Entry(frame_enhance,width=8)
e_line_a.grid(row=1,column=2,columnspan=2)
e_line_a.insert(0,'1')
tk.Button(frame_enhance, text="确定",command=GrayLinear).grid(padx=10,pady=5,row=1,column=4)
#第3行
tk.Label(frame_enhance, text="对数变换").grid(padx=5,pady=5,row=2,column=0)
tk.Label(frame_enhance, text="c=").grid(padx=5,pady=5,row=2,column=1)
e_log_c=tk.Entry(frame_enhance,width=8)
e_log_c.grid(row=2,column=2,columnspan=2)
e_log_c.insert(0,'1')
tk.Button(frame_enhance, text="确定",command=GrayLog).grid(padx=10,pady=5,row=2,column=4)
#第4行
tk.Label(frame_enhance, text="Gamma变换").grid(padx=5,row=3,column=0)
s_gamma=tk.Scale(frame_enhance,from_=0,to=20,orient=tk.HORIZONTAL)
s_gamma.grid(pady=5,row=3,column=1,columnspan=3)
tk.Button(frame_enhance, text="确定",command=GrayGamma).grid(padx=10,pady=5,row=3,column=4)
#第5行
hist_check=tk.IntVar()
tk.Label(frame_enhance, text="直方图均衡").grid(padx=5,pady=5,row=4,column=0)
c_hist=tk.Checkbutton(frame_enhance, text="Enabled",variable=hist_check)
c_hist.grid(padx=5,pady=5,row=4,column=1,columnspan=2)
c_hist.deselect()
tk.Button(frame_enhance, text="确定",command=HistEqual).grid(padx=10,pady=5,row=4,column=4)
#第6行
tk.Button(frame_enhance, text="原图像直方图",command=ShowOriginHist).grid(padx=5,pady=5,row=5,column=0,columnspan=2)
tk.Button(frame_enhance, text="均衡后直方图",command=ShowChangeHist).grid(padx=5,pady=5,row=5,column=2,columnspan=2)

#第7行
reverse_check=tk.IntVar()
tk.Label(frame_enhance, text="灰度反转").grid(padx=5,pady=5,row=6,column=0)
c_reverse=tk.Checkbutton(frame_enhance, text="Enabled",variable=reverse_check)
c_reverse.grid(padx=5,pady=5,row=6,column=1,columnspan=2)
c_reverse.deselect()
tk.Button(frame_enhance, text="确定",command=GrayReverse).grid(padx=10,pady=5,row=6,column=4)


''' 位置调节 '''
# 改变图像显示位置
def ChangePhoto():
    m_photo.localpre_h=s_height.get()
    m_photo.localpre_w=s_width.get()
    ShowImg()
    
frame_local=tk.LabelFrame(win,width=300, height=180,padx=5,pady=5,text="窗位调节",font=('microsoft yahei', 11, 'bold'),bg="lightyellow")
frame_local.grid(row=4,column=1)
frame_local.grid_propagate(0)
#第1行
tk.Label(frame_local, text="高度").grid(padx=5,row=0,column=0)
v_h=tk.IntVar()
s_height=tk.Scale(frame_local,from_=0,to=100,orient=tk.HORIZONTAL,variable=v_h)
s_height.grid(padx=10,pady=5,row=0,column=1)
s_height.set(0)
tk.Entry(frame_local,textvariable=v_h,width=6).grid(padx=10,pady=5,row=0,column=2)
tk.Label(frame_local, text="%").grid(padx=1,row=0,column=3)

#第2行
tk.Label(frame_local, text="宽度").grid(padx=5,row=1,column=0)
v_w=tk.IntVar()
s_width=tk.Scale(frame_local,from_=0,to=100,orient=tk.HORIZONTAL,variable=v_w)
s_width.grid(padx=10,pady=5,row=1,column=1)
s_width.set(0)
tk.Entry(frame_local,textvariable=v_w,width=6).grid(padx=10,pady=5,row=1,column=2)
tk.Label(frame_local, text="%").grid(padx=1,row=1,column=3)

#第3行
tk.Button(frame_local, text="确定",command=ChangePhoto).grid(padx=10,row=2,column=0,columnspan=4)



''' 工具 '''
# 放大图像
def EnlargePhoto():
    times=int(s_enlage.get())
    if times>0:
        m_photo.enlarge=times
    elif times<0: 
        m_photo.enlarge=-1/times
    else:
        m_photo.enlarge=1
    # print(m_photo.enlarge)
    ShowImg()
    
# 旋转图像
def RotatePhoto():
    theta=int(s_revolve.get())
    m_photo.rotation=theta
    ShowImg()
    
# 镜像图像
def MirrorPhoto():
    method=combo_mirror.get()
    m_photo.mirror=method
    ShowImg()
    
# 转置图像
def ReversePhoto():
    if transp_check.get()==1:
        m_photo.transp=True
    else:
        m_photo.transp=False
    ShowImg()

frame_tool=tk.LabelFrame(win,width=260, height=260,padx=5,pady=5,text="工具",font=('microsoft yahei', 11, 'bold'),bg="lightyellow")
frame_tool.grid(row=1,column=2,rowspan=2)
frame_tool.grid_propagate(0)

#第1行
tk.Label(frame_tool, text="放大").grid(padx=10,pady=10,row=0,column=0)
s_enlage=tk.Scale(frame_tool,from_=-16,to=16,orient=tk.HORIZONTAL,resolution=2)
s_enlage.grid(pady=10,row=0,column=1)
s_enlage.set(0)
tk.Button(frame_tool, text="确定",command=EnlargePhoto).grid(padx=10,pady=10,row=0,column=2)

#第2行
tk.Label(frame_tool, text="旋转").grid(padx=10,pady=10,row=1,column=0)
s_revolve=tk.Scale(frame_tool,from_=-180,to=180,orient=tk.HORIZONTAL,resolution=10)
s_revolve.grid(pady=10,row=1,column=1)
s_enlage.set(0)
tk.Button(frame_tool, text="确定",command=RotatePhoto).grid(padx=10,row=1,column=2)

#第3行
tk.Label(frame_tool, text="镜像").grid(padx=10,pady=10,row=2,column=0)
combo_mirror=ttk.Combobox(frame_tool,height=2,width=10,state='readonly',cursor='arrow',values=['none','vertical','horizontal'])   
combo_mirror.grid(pady=10,row=2,column=1)
combo_mirror.set('none')
tk.Button(frame_tool, text="确定",command=MirrorPhoto).grid(padx=10,row=2,column=2)

#第4行
transp_check=tk.IntVar()
tk.Label(frame_tool, text="转置").grid(padx=10,pady=10,row=3,column=0)
c_transp=tk.Checkbutton(frame_tool, text="Enabled",variable=transp_check)
c_transp.grid(padx=5,pady=5,row=3,column=1,columnspan=1)
c_transp.deselect()
tk.Button(frame_tool, text="确定",command=ReversePhoto).grid(padx=10,pady=5,row=3,column=2)


''' 空间滤波 '''
# 锐化滤波器类型
def SharpPhoto():
    method=combo_sharp.get()
    m_photo.sharpfilter=method
    print(m_photo.sharpfilter)
    ShowImg()
# 高提升滤波
def HighAbPhoto():
    if highabfilter_check.get()==1:
        m_photo.highabfilter=True
    else:
        m_photo.highabfilter=False
    print(m_photo.highabfilter)
    ShowImg()
# 平滑滤波器类型
def SmoothPhoto():
    method=combo_smooth.get()
    m_photo.smoothfilter=method
    # print(m_photo.smoothfilter)
    ShowImg()
# 平滑滤波模板
def FilterSizePhoto():
    method=combo_filtersize.get()
    m_photo.filter_size=method
    # print(m_photo.filter_size)
    ShowImg()
frame_filter=tk.LabelFrame(win,width=260, height=300,padx=5,pady=5,text="空间滤波",font=('microsoft yahei', 11, 'bold'),bg="lightyellow")
frame_filter.grid(row=3,column=2,rowspan=2)
frame_filter.grid_propagate(0)

#第1行
tk.Label(frame_filter, text="锐化滤波",bg="lightyellow",font=('microsoft yahei', 10)).grid(padx=5,row=0,column=0)

#第2行
tk.Label(frame_filter, text="滤波器类型").grid(padx=5,row=1,column=0)
combo_sharp=ttk.Combobox(frame_filter,height=2,width=10,state='readonly',cursor='arrow',values=['none','Laplacian','Roberts','Prewitt','Sobel'])   
combo_sharp.grid(pady=10,row=1,column=1)
combo_sharp.set('none')
tk.Button(frame_filter, text="确定",command=SharpPhoto).grid(padx=10,row=1,column=2)
#第3行
highabfilter_check=tk.IntVar()
tk.Label(frame_filter, text="高提升滤波").grid(padx=10,pady=10,row=2,column=0)
c_highabfilter=tk.Checkbutton(frame_filter, text="Enabled",variable=highabfilter_check)
c_highabfilter.grid(padx=5,pady=5,row=2,column=1)
c_highabfilter.deselect()
tk.Button(frame_filter, text="确定",command=HighAbPhoto).grid(padx=10,pady=5,row=2,column=2)

#第4行
tk.Label(frame_filter, text="平滑滤波",bg="lightyellow",font=('microsoft yahei', 10)).grid(padx=5,row=3,column=0)

#第5行
tk.Label(frame_filter, text="滤波器类型").grid(padx=5,row=4,column=0)
combo_smooth=ttk.Combobox(frame_filter,height=2,width=10,state='readonly',cursor='arrow',values=['none','Gaussian','Average','Median'])   
combo_smooth.grid(pady=10,row=4,column=1)
combo_smooth.set('none')
tk.Button(frame_filter, text="确定",command=SmoothPhoto).grid(padx=10,row=4,column=2)

#第6行
tk.Label(frame_filter, text="选择模板").grid(padx=5,row=5,column=0)
combo_filtersize=ttk.Combobox(frame_filter,height=2,width=10,state='readonly',cursor='arrow',values=['3x3','5x5','7x7','9x9'])   
combo_filtersize.grid(pady=10,row=5,column=1)
combo_filtersize.set('3x3')
tk.Button(frame_filter, text="确定",command=FilterSizePhoto).grid(padx=10,row=5,column=2)
    
      
## 程序运行
win.mainloop()