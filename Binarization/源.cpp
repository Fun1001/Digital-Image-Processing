#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat result_a;
	Mat result_b;

	Mat srcMat = imread("E:\\timg.jpg",0);

	threshold(srcMat, result_a, 100, 255, THRESH_OTSU);
	adaptiveThreshold(srcMat, result_b, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV,35,10);

	imshow("threshold", result_a);
	imshow("adaptiveThreshold", result_b);

	waitKey(0);

	return 0;
}
