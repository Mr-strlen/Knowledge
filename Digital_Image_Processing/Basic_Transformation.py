### 将基本变换封装为一个函数
import numpy as np
import cv2
import math
import matplotlib.pyplot as plt

## RGB转灰度
def img_rgb2gray(img):
    new_img=np.zeros((height,width,3),dtype=np.uint8)
    for y in range(height):
        for x in range(width):
            temp=0.299*img[y,x,0]+0.587*img[y,x,0]+0.114*img[y,x,0]
            if temp>255:
                temp=255
            new_img[y, x]=[temp,temp,temp]
    return new_img

## 输出灰度图像的灰度直方图
def img_grayhist(img,bins=32):
    temp=np.array(img)
    data=temp.reshape((height*width*3))
    plt.hist(data,density=True,bins=bins)
    plt.show()


## 图像反转
def img_graytransform_reverse(img):
    new_img=np.ones((height,width,3),dtype=np.uint8)*255-img
    return new_img

## 灰度变换函数
def img_graytransform(img,a=1,b=0,c=1,gama=0,e=0,func="gama"):
    new_img=np.zeros((height,width,3),dtype=np.uint8)
    for y in range(height):
        for x in range(width):
            if func=="linear":
                temp=int(img[y,x,0])*a+b
            elif func=="log":
                temp=np.log(int(img[y,x,0])+1)*c
            elif func=="gama":
                temp=int(img[y,x,0])/255
                temp=int(pow(temp+e,gama)*255)
            
            if temp>255:
                new_img[y,x]=[255,255,255]
            elif temp<0:
                new_img[y,x]=[0,0,0]
            else:
                new_img[y,x]=[temp,temp,temp]
    return new_img

'''
# 线性变换 ax+b
def img_graytransform_linear(img,a=1,b=0):
    new_img=np.zeros((height,width,3),dtype=np.uint8)
    for y in range(height):
        for x in range(width):
            temp=int(img[y,x,0])*a+b
            if temp>255:
                new_img[y,x]=[255,255,255]
            elif temp<0:
                new_img[y,x]=[0,0,0]
            else:
                new_img[y,x]=[temp,temp,temp]
    return new_img

# 指数变换 clog(1+x)
def img_graytransform_log(img,c=1):
    new_img=np.zeros((height,width,3),dtype=np.uint8)
    for y in range(height):
        for x in range(width):
            temp=np.log(int(img[y,x,0])+1)*c
            if temp>255:
                new_img[y,x]=[255,255,255]
            elif temp<0:
                new_img[y,x]=[0,0,0]
            else:
                new_img[y,x]=[temp,temp,temp]
    return new_img

# 幂次变换/伽马变换 c(x+e)^gama
def img_graytransform_gama(img,gama=0,e=0,c=1):
    new_img=np.zeros((height,width,3),dtype=np.uint8)
    for y in range(height):
        for x in range(width):
            temp=int(img[y,x,0])/255
            temp=int(pow(temp+e,gama)*255)
            if temp>255:
                new_img[y,x]=[255,255,255]
            elif temp<0:
                new_img[y,x]=[0,0,0]
            else:
                new_img[y,x]=[temp,temp,temp]
    return new_img
'''
## 直方图均衡化
def img_histequal(img,bins=256):
    dmax=255
    tran_func=dict(zip([i for i in range(bins)],[0 for i in range(bins)]))
    hist=dict(zip([i for i in range(bins)],[0 for i in range(bins)]))
    
    # 统计灰度分布
    for y in range(height):
        for x in range(width):
            hist[img[y,x,0]]+=1
    
    total=0
    for i in range(bins):
        total+=hist[i]
        tran_func[i]=round(dmax*total/height/width)
    
    new_img=np.zeros((height,width,3),dtype=np.uint8)
    for y in range(height):
        for x in range(width):
            new_img[y,x]=[tran_func[img_gray[y,x,0]],tran_func[img_gray[y,x,1]],tran_func[img[y,x,2]]]
    return new_img

## 图像平移
def img_move(img,v=(0,0),expand=False):
    vx,vy=v
    if not expand:
        new_img=np.zeros((height,width,3),dtype=np.uint8)
        for y in range(height):
            for x in range(width):
                if 0<=y-vy<height and 0<=x-vx<width:
                    temp=img[y-vy,x-vx]
                else:
                    temp=[255,255,255]
                new_img[y,x]=temp
    else:
        new_img=np.ones((height+abs(vy),width+abs(vx),3),dtype=np.uint8)*255
        for y in range(relu(vy),height+abs(vy)):
            for x in range(relu(vx),width+abs(vx)):
                new_img[y,x]=img[y-relu(vy),x-relu(vx)]
    return new_img
def relu(x):
    if x>=0:
        return x
    else:
        return 0

## 图像翻转
def img_mirror(img,methods="vertical"):
    new_img=np.zeros((height,width,3),dtype=np.uint8)
    if methods=="vertical":
        for y in range(height):
            for x in range(width):
                new_img[y,x]=img[height-1-y,x]
    elif methods=="horizontal":
        for y in range(height):
            for x in range(width):
                new_img[y,x]=img[y,width-1-x]
    return new_img

## 图像转置
def img_transpose(img):
    new_img=np.zeros((width,height,3),dtype=np.uint8)
    for y in range(height):
        for x in range(width):
            new_img[x,y]=img[y,x]
    return new_img

'''
## 旋转 前向映射，缺失点太多，效果太差
def img_rotation(x0,y0,theta,img):
    new_img=np.zeros((height, width, 3), dtype=np.uint8)
    radian = math.radians(theta)
    cos_r = np.cos(radian)
    sin_r = np.sin(radian)
    
    for y in range(height):
        for x in range(width):
            x_new=(x-x0)*cos_r-(y-y0)*sin_r+x0
            y_new=(x-x0)*sin_r+(y-y0)*cos_r+y0
            if x_new>width or y_new>height or x_new<0 or y_new<0:
                continue
            else:
                new_img[math.ceil(y_new)-1, math.ceil(x_new)-1] = img[int(y), int(x)]
    return new_img
'''

## 双线性插值：x,y目标点坐标
def bilinear_interpolation(x,y,img):
    x_low,y_low=int(x),int(y)
    x_high,y_high=x_low+1,y_low+1
    if x_high>width-1 and y_high>height-1:
        v4,v1,v2,v3=0,img[y_low,x_low].astype(np.int),img[y_high,x_low].astype(np.int),img[y_low,x_high].astype(np.int)
    if x_high>width-1 and y_high<height:
        v3,v4,v1,v2=0,0,img[y_low,x_low].astype(np.int),img[y_high,x_low].astype(np.int)
    if y_high>height-1 and x_high<width:
        v2,v4,v1,v3=0,0,img[y_low,x_low].astype(np.int),img[y_low,x_high].astype(np.int)
    if x_high<width and y_high<height:
        v1,v2,v3,v4=img[y_low,x_low].astype(np.int),img[y_high,x_low].astype(np.int),img[y_low,x_high].astype(np.int),img[y_high,x_high].astype(np.int)
    # print([v1,v2,v3,v4])
    t11=(y-y_low)*(v2-v1)+v1
    t12=(y-y_low)*(v4-v3)+v3
    t21=(x-x_low)*(t12-t11)+t11
    return np.round(t21)

## 旋转 后向映射：x0,y0围绕点;theta旋转角 
def img_rotation(x0,y0,theta,img):
    new_img=np.zeros((height,width,3),dtype=np.uint8)
    radian = math.radians(-theta)
    cos_r = np.cos(radian)
    sin_r = np.sin(radian)
    
    for y_new in range(height):
        for x_new in range(width):
            x=(x_new-x0)*cos_r-(y_new-y0)*sin_r+x0
            y=(x_new-x0)*sin_r+(y_new-y0)*cos_r+y0
            if x>width or y>height or x<0 or y<0:
                continue
            else:     
                #new_img[y_new, x_new] = img[int(y),int(x)] #直接取值
                new_img[y_new, x_new]=bilinear_interpolation(x,y,img) #双线性差值                
    return new_img


## 图像放大 后向映射，非整数双线性插值：x0,y0围绕点;times放大倍数
def img_enlarge(x0,y0,times,img):
    new_img=np.zeros((height,width,3),dtype=np.uint8)
    for y_new in range(height):
        for x_new in range(width):
            x=(x_new-x0)/times+x0
            y=(y_new-y0)/times+y0
            if x>width or y>height or x<0 or y<0:
                continue
            if y_new%times==0 and x_new%times==0:
                new_img[y_new, x_new] = img[int(y),int(x)]
            else:
                new_img[y_new, x_new]=bilinear_interpolation(x,y,img)
    return new_img

## 均值平滑 k为奇数
def img_filter(img,k=3,padding="zeros",sigma=1,methods="gaussian"):
    new_img=new_img=np.zeros((height,width,3),dtype=np.uint8)
    dt=int((k-1)/2)
    # 填充矩阵
    if padding=="zeros": #零填充
        tmp_img=np.r_[np.zeros((dt,width,3)),img.astype(np.int),np.zeros((dt,width,3))]
        tmp_img=np.hstack((np.zeros((height+k-1,dt,3)),tmp_img))
        tmp_img=np.hstack((tmp_img,np.zeros((height+k-1,dt,3))))
    elif padding=="reflection": #镜像填充
        ttmp_img=np.r_[img[-dt:,:,:],img.astype(np.int),img[:dt,:,:]]
        tmp_img=np.hstack((ttmp_img[:,-dt:,:],ttmp_img))
        tmp_img=np.hstack((tmp_img,ttmp_img[:,:dt,:]))
    elif padding=="replicate": #重复填充
        tmp_img=np.r_[np.repeat(img[:1,:,:],dt,axis=0),img.astype(np.int),np.repeat(img[-1:,:,:],dt,axis=0)]
        tmp_img=np.hstack((np.repeat(tmp_img[:,:1,:],dt,axis=1),tmp_img))
        tmp_img=np.hstack((tmp_img,np.repeat(tmp_img[:,-1:,:],dt,axis=1)))
    # 滑窗平移
    if methods=="average":
        filter_core=np.ones((k,k))/k/k
    elif methods=="gaussian":
        filter_core=np.zeros((k,k))
        sigma2=pow(sigma,2)
        for i in range(0,k):
            for j in range(0,k):
               filter_core[i,j]=np.exp(-(pow(i-dt,2)+pow(j-dt,2))/2/sigma2)/2/np.pi/sigma2
        filter_core=filter_core/np.sum(filter_core)     
    for y in range(height):
        for x in range(width):
            temp=np.round(np.sum(filter_core*tmp_img[y:y+dt*2+1,x:x+2*dt+1,0]))
            new_img[y,x]=[temp,temp,temp]
    return new_img


plt.close("all")
# img=cv2.imread('./test/Lena.bmp')
# img=cv2.imread('./test/LenaRGB.bmp')
img=cv2.imread('./test/wife_middle.jfif')

height,width=img.shape[:2]
img_gray=img_rgb2gray(img)
img_new=img_filter(img_gray,k=7,methods="average")
cv2.imshow("test1",img_new)

img_new=img_filter(img_gray,k=7,methods="gaussian")
cv2.imshow("test2",img_new)

img_new=img_filter(img_gray,k=7,sigma=3,methods="gaussian")
cv2.imshow("test3",img_new)
# height,width=img.shape[:2]
# x0=math.ceil(width/2) #设定旋转放大的参考点
# y0=math.ceil(height/2)
# theta=45
# img_rotation=img_rotation(x0,y0,theta,img)
# cv2.imwrite('./barbara_rotation.bmp', img_rotation)
# img_enlarge=img_enlarge(x0,y0,3,img_rotation)
# cv2.imwrite('./barbara_enlarge.bmp', img_enlarge)
# cv2.imshow("test",img_enlarge)



