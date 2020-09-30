#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main()
{
	cv::Mat src_pic = imread("E:/timg.jpg");
	
	cv::Point pt;
	pt.x = 50;
	pt.y = 50;

	cv::Point pt1;
	cv::Point pt2;
	pt1.x = 20;
	pt1.y = 20;
	pt2.x = 50;
	pt2.y = 50;

	cv::Rect rect;
	rect.x = 30;
	rect.y = 30;
	rect.width=100;
	rect.height=200;

	circle(src_pic, pt, 50, CV_RGB(255, 0, 0), 1, 8, 0);
	line(src_pic, pt1, pt2, CV_RGB(255, 0, 0), 1, 8, 0);
	rectangle(src_pic, rect, CV_RGB(255, 0, 0), 1, 8, 0);

	imshow("draw", src_pic);

	waitKey(0);
	return 0;
}
