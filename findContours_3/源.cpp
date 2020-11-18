#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;


int main()
{
	double scale = 1;

	//颜色提取
	double i_minH = 0;
	double i_maxH = 20;

	double i_minS = 43;
	double i_maxS = 255;

	double i_minV = 46;
	double i_maxV = 255;

	cv::Mat srcMat = imread("E:\\5.jpg");
	cv::Mat disMat = imread("E:\\5.jpg");
	cv::Mat hsvMat;
	cv::Mat detectMat;
	cv::Mat binaryMat;

	Size ReslmgSiz = Size(srcMat.cols * scale, srcMat.rows * scale);
	cv::Mat rsrcMat = Mat(ReslmgSiz,srcMat.type());
	resize(srcMat, rsrcMat, ReslmgSiz, INTER_LINEAR);

	cvtColor(rsrcMat, hsvMat, COLOR_BGR2HSV);

	rsrcMat.copyTo(detectMat);
	cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);

	cv::threshold(detectMat, binaryMat, 0, 255, THRESH_OTSU);//二值化
	
	//闭运算
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
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
		drawContours(binaryMat, contours, i, Scalar(0, 255, 255), 1, 8);
		cv::Point2f vtx[4];
		rbox.points(vtx);

		//计算长、宽
		float Y = sqrt((vtx[0].y - vtx[1].y) * (vtx[0].y - vtx[1].y) + (vtx[0].x - vtx[1].x) * (vtx[0].x - vtx[1].x));
		float X = sqrt((vtx[1].y - vtx[2].y) * (vtx[1].y - vtx[2].y) + (vtx[1].x - vtx[2].x) * (vtx[1].x - vtx[2].x));
		//判断条件
		if (((X * Y) > 500))
		{
			for (int i = 0; i < 4; ++i)
			{
				cv::line(disMat, vtx[i], vtx[i < 3 ? i + 1 : 0], Scalar(0, 0, 255), 2, CV_AA);
			}
		}
	}
	
	cv::imshow("src", disMat);
	waitKey(0);
	return 0;

}