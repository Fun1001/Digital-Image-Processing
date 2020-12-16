#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main()
{
	VideoCapture capvideo(0);//打开摄像头
	if (!capvideo.isOpened())//打开失败
	{
		std::cout << "can not open the cap" << std::endl;
		return -1;
	}

	int cnt = 0;
	Mat frame;
	Mat bgMat;
	Mat subMat;
	Mat bny_subMat;

	while (1)
	{
		capvideo >> frame;
		cvtColor(frame, frame, COLOR_BGR2GRAY);

		if (cnt == 0)//在第一帧获取背景图像
		{
			frame.copyTo(bgMat);
		}
		else//从第二帧开始背景差分
		{
			absdiff(frame, bgMat, subMat);//当前帧与背景差分，得出差异
			threshold(subMat, bny_subMat, 50, 255, CV_THRESH_BINARY);//差分结果二值化

			imshow("bny_subMat", bny_subMat);
			imshow("subMat", subMat);

			waitKey(30);
		}
		cnt++;
	}
	return 0;
}