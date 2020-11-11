#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main()
{
	cv::Mat dstMat;
	cv::Mat srcMat = imread("E:\\timg.jpg");
	if (srcMat.empty()) return -1;
	//旋转-40度，缩放尺度为0.5
	float angle = -10.0, scale = 1;
	//旋转中心为图像中心
	cv::Point2f center(srcMat.cols * 0.5, srcMat.rows * 0.5);
	cv::Mat rot = cv::getRotationMatrix2D(center,angle,scale);
	//获取外界四边形
	cv::Rect bbox = cv::RotatedRect(center,srcMat.size(),angle).boundingRect();
	//调整仿射矩阵参数
	rot.at<double>(0, 2) += bbox.width * 0.5 - center.x;
	rot.at<double>(1, 2) += bbox.height * 0.5 - center.y;
	//获得变换矩阵
	cv::warpAffine(srcMat, dstMat, rot, bbox.size());

	cv::imshow("src", srcMat);
	cv::imshow("dst", dstMat);
	waitKey(0);
	return 0;

}