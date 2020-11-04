#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main()
{
	cv::Mat dstMat;
	cv::Mat srcMat = imread("E:\\timg.jpg");
	if (srcMat.empty()) return -1;
	//变换前四点坐标
	const cv::Point2f src_pt[] = {
									cv::Point2f(150,150),
									cv::Point2f(150,300),
									cv::Point2f(350,300),
									cv::Point2f(350,150) };
	//变换后四点坐标
	const cv::Point2f dst_pt[] = {
									cv::Point2f(200,150),
									cv::Point2f(200,300),
									cv::Point2f(340,270),
									cv::Point2f(340,180) };
	//投影变换行列计算
	const cv::Mat perspective_matrix = cv::getPerspectiveTransform(src_pt, dst_pt);
	cv::warpPerspective(srcMat, dstMat, perspective_matrix, srcMat.size());

	cv::imshow("src", srcMat);
	cv::imshow("dst", dstMat);
	waitKey(0);
	return 0;

}