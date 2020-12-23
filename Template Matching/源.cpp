#include<opencv2/opencv.hpp>
#include<iostream>
#include<highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
	VideoCapture capvideo(0);//打开摄像头
	if (!capvideo.isOpened())//打开失败
	{
		std::cout << "can not open the cap" << std::endl;
		return -1;
	}

	int cnt = 0;
	Mat frame;
	Mat tempMat;
	Mat refMat;
	Mat resultMat;
	Mat dispMat;
	while (1)
	{
		capvideo >> frame;
		if (frame.empty()) break;
		if (cnt == 10)//在第10帧获取模板图像
		{
			Rect2d r;
			r = selectROI(frame, true);
			tempMat = frame(r);
			tempMat.copyTo(refMat);
			destroyAllWindows();
			break;
		}
		cnt++;
		waitKey(30);
	}

	while (1)
	{
		capvideo >> frame;

		
		//模板匹配主函数
		int match_method = 0;
		matchTemplate(frame, refMat, resultMat, match_method);
		//归一化
		normalize(resultMat, resultMat, 0, 1, NORM_MINMAX, -1, Mat());

		double minVal;
		double maxVal;
		Point minLoc;
		Point maxLoc;
		Point matchLoc;

		//寻找极值
		minMaxLoc(resultMat, &minVal, &minVal, &minLoc, &maxLoc, Mat());

		if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED)
		{
			matchLoc = minLoc;
		}
		else
		{
			matchLoc = maxLoc;
		}

		//画框
		frame.copyTo(dispMat);
		rectangle(dispMat, matchLoc,Point(matchLoc.x+refMat.cols, matchLoc.y+refMat.rows), Scalar::all(0),2,8,0);
		cnt++;
		imshow("111", refMat);
		imshow("hhh", dispMat);
		waitKey(30);
		
	}
	return 0;
}