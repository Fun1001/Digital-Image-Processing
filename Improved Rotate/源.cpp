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
	float angle = -10.0, scale = 1;
	//��ת����Ϊͼ������
	cv::Point2f center(srcMat.cols * 0.5, srcMat.rows * 0.5);
	cv::Mat rot = cv::getRotationMatrix2D(center,angle,scale);
	//��ȡ����ı���
	cv::Rect bbox = cv::RotatedRect(center,srcMat.size(),angle).boundingRect();
	//��������������
	rot.at<double>(0, 2) += bbox.width * 0.5 - center.x;
	rot.at<double>(1, 2) += bbox.height * 0.5 - center.y;
	//��ñ任����
	cv::warpAffine(srcMat, dstMat, rot, bbox.size());

	cv::imshow("src", srcMat);
	cv::imshow("dst", dstMat);
	waitKey(0);
	return 0;

}