#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat Erode, Dilate, Open, Close;
	cv::Mat Binary;
	cv::Mat src = imread("E:\\coin.jpg", 0);							//灰度图

	cv::threshold(src, Binary, 0, 255, THRESH_OTSU);					//二值化
	
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));			//3*3矩形

	erode(Binary, Erode, kernel);										//腐蚀
	dilate(Binary, Dilate, kernel);										//膨胀
	morphologyEx(Binary, Open, MORPH_OPEN, kernel);						//开运算
	morphologyEx(Binary, Close, MORPH_CLOSE, kernel);					//闭运算

	imshow("Binary", Binary);
	imshow("Erode", Erode);
	imshow("Dilate", Dilate);
	imshow("Open", Open);
	imshow("Close", Close);

	waitKey(0);
	return 0;
}