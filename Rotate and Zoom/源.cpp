#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main()
{
	cv::Mat dstMat;
	cv::Mat srcMat = imread("E:\\timg.jpg");
	if (srcMat.empty()) return -1;
	//��ת-40�ȣ����ų߶�Ϊ0.5
	float angle = -10.0, scale = 0.5;
	//��ת����Ϊͼ������
	cv::Point2f center(srcMat.cols * 0.5, srcMat.rows * 0.5);
	//��ñ任����
	const cv::Mat affine_matrix = cv::getRotationMatrix2D(center, angle, scale);
	cv::warpAffine(srcMat, dstMat, affine_matrix, srcMat.size());

	cv::imshow("src", srcMat);
	cv::imshow("dst", dstMat);
	waitKey(0);
	return 0;

}