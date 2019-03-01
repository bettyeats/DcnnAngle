# 说明

## 代码说明

1. main.cpp:

读入视频，解帧；
实例化对象；
```
Dispatcher mDispatcher;
```
调用对象的detect方法，得到8个点，3个角度和脸部宽度。

2. Dispatcher.cpp:

持有对象mLandmaker，这个对象是8点模型。
持有对象mDcnc，这个对象是5点模型。

检测步骤：
使用opencv的face_cascade.detectMultiScale检测人脸框；
将图片裁取后，使用5点模型检测5个点；
根据5点，使用对象mFaceAlig对图片进行矫正；
矫正后的图片，用8点模型进行检测；
使用EstimatePose估算角度。

3. Landmaker.cpp:

初始化level1 和 level2的模型；
使用对象的Classify方法执行模型前向；
```
OneLevel_obj.Classify(croppedImg, Pts);
```
返回的点是归一化后的数值，在0-1之间。
按照原论文裁取小的图像分别给level2的16个模型。每个点2个模型，算平均。

4. CaffeClassify.cpp:

使用的caffe官方c++调用库，可以不用管。

## 依赖

依赖opencv2.4.13(core\calib3d\contrib\highgui\imgproc\video\videostab\objdetect)
libgif.4
libevent
caffe1.0.0
glog
boost_system

无版本数字代表版本无关

## 打点及打角度代码
    打点
```
for (int i = 0; i < 16; i+=2)
{
float x = features[i];
float y = features[i + 1];
cv::circle(img_rz,cv::Point(x,y), 2, cv::Scalar(0, 255, 0), -1);
}

```
    打角度
```
#include <iostream>
ostringstream outtext;
// Print on image
outtext << "Yaw: " << concat.at(0);
cv::putText(img_rz, outtext.str(), cv::Point(10, 40), cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(0, 255, 0));

```
    写出
```
int count = 0;
string filename = "./" + std::to_string(count) + ".jpg";
cv::imwrite(filename, frame);
count ++;
```
