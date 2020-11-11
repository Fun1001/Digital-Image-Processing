#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main()
{
	cv::Mat canny;
	cv::Mat srcMat = imread("E:\\2.jpg");
	cv::Canny(srcMat, canny, 50, 125);

	//»ô·ò±ä»»
	std::vector<cv::Vec4i> lines;
	cv::HoughLinesP(canny, lines, 1, CV_PI / 180, 35,10,10);

	cv::Mat lineMat;
	cv::HoughLinesP(canny, lineMat, 1, CV_PI / 180, 35,10,10);

	//»­Ïß
	for (int i=0; i < lines.size(); i++)
	{
		cv::Vec4i linex = lines[i];
		cv::line(srcMat, cv::Point(linex[0],linex[1]), cv::Point(linex[2],linex[3]), cv::Scalar(0, 255, 0), 1, CV_AA);
	}

	cv::imshow("src", srcMat);
	cv::imshow("canny", canny);
	waitKey(0);
	return 0;

}