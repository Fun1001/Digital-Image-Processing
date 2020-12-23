#include<opencv2/opencv.hpp>
#include<iostream>
#include<highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
	VideoCapture capvideo(0);//������ͷ
	if (!capvideo.isOpened())//��ʧ��
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
		if (cnt == 10)//�ڵ�10֡��ȡģ��ͼ��
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

		//ģ��ƥ��������
		int match_method = 0;
		matchTemplate(frame, refMat, resultMat, match_method);
		//��һ��
		normalize(resultMat, resultMat, 0, 1, NORM_MINMAX, -1, Mat());

		double minVal;
		double maxVal;
		Point minLoc;
		Point maxLoc;
		Point matchLoc;

		//Ѱ�Ҽ�ֵ
		minMaxLoc(resultMat, &minVal, &minVal, &minLoc, &maxLoc, Mat());

		if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED)
		{
			matchLoc = minLoc;
		}
		else
		{
			matchLoc = maxLoc;
		}

		//����
		frame.copyTo(dispMat);
		rectangle(dispMat, matchLoc,Point(matchLoc.x+refMat.cols, matchLoc.y+refMat.rows), Scalar::all(0),2,8,0);
		cnt++;
		imshow("111", refMat);
		imshow("hhh", dispMat);
		waitKey(30);
		
	}
	return 0;
}