#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main()
{
	cv::Mat dstMat;
	cv::Mat BinMat;
	cv::Point2f point1, point2, point3, point4;
	cv::Mat srcMat = imread("E:\\pic.jpg",0);
	if (srcMat.empty()) return -1;
	//变换前四点坐标
	//第一个点
	for(int j=0;j<srcMat.rows;j++)
	{ 
		for (int i = 0; i < srcMat.cols;i++)
		{
			if (srcMat.at<uchar>(j,i)< 240 )
			{
				point1.x = i;
				point1.y = j;
				break;
			}
		}
		if (srcMat.at<uchar>(j, point1.x) < 240) 
		{
			break;
		}
	}
	cout << point1.x << endl << point1.y<<endl;
	//第二个点
	for (int i = 0; i < srcMat.cols; i++)
	{
		for (int j = 0; j < srcMat.rows; j++)
		{
			if (srcMat.at<uchar>(j, i) < 240)
			{
				point2.x = i;
				point2.y = j;
				break;
			}
		}
		if (srcMat.at<uchar>(point2.y, i) < 240)
		{
			break;
		}
	}
//	cout << point2.x << endl << point2.y << endl;
	//第三个点
	for (int j = srcMat.rows-1 ; j >0; j--)
	{
		for (int i = 0; i < srcMat.cols; i++)
		{
			if (srcMat.at<uchar>(j, i) < 240)
			{
				point3.x = i;
				point3.y = j;
				break;
			}
		}
		if (srcMat.at<uchar>(j, point3.x) < 240) {
			break;
		}
	}
//	cout << point3.x << endl << point3.y << endl;
	//第四个点
	for (int i =srcMat.cols-1; i >0 ; i--)
	{
		for (int j = 0; j < srcMat.rows; j++)
		{
			if (srcMat.at<uchar>(j, i) < 240)
			{
				point4.x = i;
				point4.y = j;
				break;
			}
		}
		if (srcMat.at<uchar>(point4.y, i) < 240)
		{
			break;
		}
	}
//	cout << point4.x << endl << point4.y << endl;
	const cv::Point2f src_pt[] = {
									cv::Point2f(point1.x,point1.y),
									cv::Point2f(point2.x,point2.y),
									cv::Point2f(point3.x,point3.y),
									cv::Point2f(point4.x,point4.y) };
	//变换后四点坐标
	const cv::Point2f dst_pt[] = {
									cv::Point2f(0,0),
									cv::Point2f(0,srcMat.rows),
									cv::Point2f(srcMat.cols,srcMat.rows),
									cv::Point2f(srcMat.cols,0) };
	//投影变换行列计算
	const cv::Mat perspective_matrix = cv::getPerspectiveTransform(src_pt, dst_pt);
	cv::warpPerspective(srcMat, dstMat, perspective_matrix, srcMat.size());

	cv::imshow("src", srcMat);
	cv::imshow("dst", dstMat);
	waitKey(0);
	return 0;

}