#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

string window_name = "binaryMat";

void threshod_Mat(int th, void* data)
{
	Mat src = *(Mat*)(data);

	Mat dst;
	//二值化
	threshold(src, dst, th, 255, 0);

	imshow(window_name, dst);

}

int main()
{
	int lowTh = 30;
	int maxTh = 255;

	Mat srcMat = imread("E:\\timg.jpg",0);
	if (!srcMat.data)//判断图像是否载入
	{
		cout << "图像载入失败！" << std::endl;
		return 0;
	}

	imshow(window_name, srcMat);
	createTrackbar("threshold",
					window_name,
					&lowTh,
					maxTh,
					threshod_Mat,
					&srcMat);

	waitKey(0);

	return 0;

}