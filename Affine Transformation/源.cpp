#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main()
{
	cv::Mat dstMat;
	cv::Mat srcMat = imread("E:\\timg.jpg");
	if (srcMat.empty()) return -1;
	//变换前三点坐标
	const cv::Point2f src_pt[] = {
									cv::Point2f(200,200),
									cv::Point2f(250,200),
									cv::Point2f(200,100) };
	//变换后三点坐标
	const cv::Point2f dst_pt[] = {
									cv::Point2f(300,100),
									cv::Point2f(300,50),
									cv::Point2f(200,100) };
	cv::Point2f center(srcMat.cols * 0.5, srcMat.rows * 0.5);
	//计算仿射矩阵
	const cv::Mat affine_matrix = cv::getAffineTransform(src_pt, dst_pt);
	cv::warpAffine(srcMat, dstMat, affine_matrix, srcMat.size());

	cv::imshow("src", srcMat);
	cv::imshow("dst", dstMat);
	waitKey(0);
	return 0;

}