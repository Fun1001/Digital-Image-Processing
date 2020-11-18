#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;


int main()
{
	cv::Mat inverseMat;
	cv::Mat binaryMat;
	cv::Mat dstMat;
	cv::Mat disMat = imread("E:\\4.png");
	cv::Mat srcMat = imread("E:\\4.png",0);
	inverseMat = ~srcMat;//反算
	cv::threshold(inverseMat,binaryMat,150,255,THRESH_OTSU);//二值化

	//闭运算
	Mat kernel = getStructuringElement(MORPH_RECT, Size(10, 11));
	morphologyEx(binaryMat, binaryMat, MORPH_CLOSE, kernel, Point(-1, -1), 1);

	//通过findcontours寻找连通域
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binaryMat, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	
	for (int i = 0; i < contours.size(); i++)
	{
		//获取最小外接四边形
		RotatedRect rbox = minAreaRect(contours[i]);

		//画轮廓
		drawContours(disMat,contours,i,Scalar(0,255,255),-1,8);
		cv::Point2f vtx[4];
		rbox.points(vtx);
		
		//计算长宽比
		float Y = sqrt((vtx[0].y - vtx[1].y) * (vtx[0].y - vtx[1].y) + (vtx[0].x - vtx[1].x) * (vtx[0].x - vtx[1].x));
		float X = sqrt((vtx[1].y - vtx[2].y) * (vtx[1].y - vtx[2].y) + (vtx[1].x - vtx[2].x) * (vtx[1].x - vtx[2].x));
		//判断条件
		if ((X/Y) >= 0.9&&((X * Y) > 20) )
		{
			if ((X / Y) <= 1.1&&((X*Y)>20))
			{
				for (int i = 0; i < 4; ++i)
				{
					cv::line(disMat, vtx[i], vtx[i < 3 ? i + 1 : 0], Scalar(0, 0, 255), 2, CV_AA);
				}
			}
		}
	}
	
	cv::imshow("src",disMat);
	waitKey(0);
	return 0;

}