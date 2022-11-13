import cv2
import numpy as np 
import winsound 
import time

filehandle=open('record.txt',mode='w')
#指定打开的文件名
 
img = cv2.imread("C:/Users/LENOVO/Desktop/211.jpg", 0)
def get_person_image():
    capture = cv2.VideoCapture(0)
    result,image_data = capture.read()      # result是拍照的结果（true或者false），image_data是图片数据
    cv2.imwrite('C:/Users/LENOVO/Desktop/211.jpg', image_data)    #写入到当前项目的根目录下
    capture.release() 
print("  s后检测")
time.sleep(5)       #15*60=900s
print("start!")
get_person_image()
img = cv2.imread("C:/Users/LENOVO/Desktop/211.jpg", 0)
img = img[220:250, 200:460] 

cropped=img[:,0:130]

cropped1 = img[:, 130:259] 
cv2.imshow('Canny', cropped1)
cv2.waitKey(0)
cv2.destroyAllWindows()
 
img = cv2.GaussianBlur(cropped,(3,3),0) #用高斯平滑处理原图像降噪。
canny = cv2.Canny(cropped, 10, 30) #最大最小阈值
img1 = cv2.GaussianBlur(cropped1,(3,3),0) #用高斯平滑处理原图像降噪。
canny1 = cv2.Canny(cropped1, 10, 30) #最大最小阈值
 
cv2.imshow('Canny', canny1)
cv2.waitKey(0)
cv2.destroyAllWindows()
jud=sum(sum(canny))
jud1=sum(sum(canny1))
if ((jud>0)and(jud1>0)):
    print("阳性")
    winsound.Beep(440,5111) #主板蜂鸣器
    winsound.MessageBeep() #喇叭
    filehandle.write('2022/10/5  A  阳性 \n')
if ((jud>0)and(jud1==0)):
    print("阴性")
    filehandle.write('2022/10/5  A 阴性 \n')
if (jud==0):
    print("无效")