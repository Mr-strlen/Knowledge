import os
import struct
import numpy as np
import cv2
from matplotlib import pyplot as plt
import Basic_Transformation as BF


## 读取raw文件
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
    img=np.array(data,dtype="uint16")
    return img,width,height


## 灰度窗映射
def graywindowmap(low,high,img,height,width):
    for i in range(0,height):
        for j in range(0,width):
            if img[i,j]<low:
                img[i,j]=0
            elif img[i,j]>high:
                img[i,j]=255
            else:
                img[i,j]=(img[i,j]-low)/(high-low)*255.0
    return img.astype(np.uint8)

img,width,height=fileopen(r"lumbar_enhance.raw")
img_t=graywindowmap(0,4095,img,height,width)
cv2.imwrite('lumbar_enhance.jpg',img_t)
'''
img1,width1,height1=fileopen("lung.raw")
img2,width2,height2=fileopen("lumbar.raw")
img3,width3,height3=fileopen("vertebra.raw")
img1=img1.astype(np.int64)
img2=img2.astype(np.int64)
img3=img3.astype(np.int64)
cv2.imwrite('lung.jpg', graywindowmap(0,4095,img1,height1,width1))
cv2.imwrite('lumbar.jpg', graywindowmap(0,4095,img2,height2,width2))
cv2.imwrite('vertebra.jpg', graywindowmap(0,4095,img3,height3,width3))
# 统计灰度

img_new1=graywindowmap(128,4000,img1,height1,width1)
img_new2=graywindowmap(128,4000,img2,height2,width2)
img_new3=graywindowmap(128,4000,img3,height3,width3)

#hist1 = cv2.calcHist([img_new1.astype(np.uint8)], [0], None, [256], [0, 256])
#hist2 = cv2.calcHist([img_new2.astype(np.uint8)], [0], None, [256], [0, 256])
#hist3 = cv2.calcHist([img_new3.astype(np.uint8)], [0], None, [256], [0, 256])
#
#plt.figure()
#plt.yscale("log")
#plt.plot(hist1)
#plt.plot(hist2)
#plt.plot(hist3)
#plt.xlim([0, 256])
#plt.legend(['lung','lumbar','vertebra'])
#plt.show()


clahe = cv2.createCLAHE(clipLimit=2.0, tileGridSize=(8,8))
cl1 = clahe.apply(img_new1.astype(np.uint8))

img_t=BF.img_sobelfilter(cl1,filter_kind=3,padding="replicate",methods="high",A=2)
img_t=BF.img_graytransform_reverse(img_t)
cv2.imwrite(r'lung_new.jpg', img_t.astype(np.uint8))
#img_t=BF.img_sobelfilter(cl1,filter_kind=3,padding="replicate",methods="high",A=1.5)
#
#cv2.imwrite(r'lung_new2.jpg', img_t)
#img_t=BF.img_sobelfilter(cl1,filter_kind=3,padding="replicate",methods="high",A=2)
#cv2.imwrite(r'lung_new3.jpg', img_t)
#
#img_t=BF.img_sobelfilter(cl1,filter_kind=3,padding="replicate",methods="high",A=3)
#cv2.imwrite(r'lung_new4.jpg', img_t)
#
#img_t=BF.img_sobelfilter(cl1,filter_kind=3,padding="replicate",methods="high",A=0.7)
#cv2.imwrite(r'lung_new5.jpg', img_t)
img_t=img_t.astype(np.uint8)
height,width=np.shape(img_t)
## 文件写入
#f=open("lung_enhance.raw","wb")
#tmp=width.to_bytes(length=4, byteorder='little', signed=False)
#f.write(tmp)
#tmp=height.to_bytes(length=4, byteorder='little', signed=False)
#f.write(tmp)
#for i in range(0,height):
#    for j in range(0,width):
#        t=img_t[i][j]
#        tmp=t.to_bytes(length=2, byteorder='little', signed=False)
#        f.write(tmp)
#f.close()


# 转换到255看看图
#img=(img-np.min(img))/(np.max(img)-np.min(img))*255.0



## 细节增强
def detailehancer(img):
    return img
'''


