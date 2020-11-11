#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main()
{
	cv::Mat canny;
	cv::Mat srcMat = imread("E:\\2.jpg");
	cv::Canny(srcMat,canny,50,125);

	//»ô·ò±ä»»
	std::vector<cv::Vec2f> lines;
	cv::HoughLines(canny, lines, 1, CV_PI / 180, 90);

	cv::Mat lineMat;
	cv::HoughLines(canny,lineMat,1,CV_PI/180,100);

	//»­Ïß
	std::vector<cv::Vec2f>::iterator it = lines.begin();
	for (;it!=lines.end(); ++it)
	{
		float rho = (*it)[0], theta = (*it)[1];
		cv::Point pt1, pt2;
		double a = cos(theta);
		double b = sin(theta);
		double x0 = a * rho;
		double y0 = b * rho;
		pt1.x = cv::saturate_cast<int>(x0 + 1000 * (-b));
		pt1.y = cv::saturate_cast<int>(y0 + 1000 * (a));
		pt2.x = cv::saturate_cast<int>(x0 - 1000 * (-b));
		pt2.y = cv::saturate_cast<int>(y0 - 1000 * (a));
		cv::line(srcMat, pt1, pt2, cv::Scalar(0, 0, 255), 1, CV_AA);
	}

	cv::imshow("src", srcMat);
	cv::imshow("canny", canny);
	waitKey(0);
	return 0;

}