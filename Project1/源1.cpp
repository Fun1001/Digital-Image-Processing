#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

//ex1¡¢2
int main()
{
	cv::Mat srcMat = imread("E:\\1.jpg");
		int height = srcMat.rows;
		int width = srcMat.cols;
		uchar threshold = 100;
		for (int j = 0; j < height; j++)
		{
			for (int i = 0; i < width; i++)
			{
				uchar average = (srcMat.at<Vec3b>(j,i)[0] + srcMat.at<Vec3b>(j,i)[1] + srcMat.at<Vec3b>(j,i)[2])/3;
				srcMat.at<Vec3b>(j,i)[0] = average;
				srcMat.at<Vec3b>(j,i)[1] = average;
				srcMat.at<Vec3b>(j,i)[2] = average;
			}
		}
		imshow("test1", srcMat);
		cv::Mat srcMat1=imread("E:\\1.jpg",0);
		imshow("test2", srcMat1);
		waitKey(0);
		return 0;
}