#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;


int main()
{
	double scale = 1;

	//��ɫ��ȡ
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

	cv::threshold(detectMat, binaryMat, 0, 255, THRESH_OTSU);//��ֵ��
	
	//������
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	morphologyEx(binaryMat, binaryMat, MORPH_CLOSE, kernel, Point(-1, -1), 1);

	//ͨ��findcontoursѰ����ͨ��
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binaryMat, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);


	for (int i = 0; i < contours.size(); i++)
	{
		//��ȡ��С����ı���
		RotatedRect rbox = minAreaRect(contours[i]);

		//������
		drawContours(binaryMat, contours, i, Scalar(0, 255, 255), 1, 8);
		cv::Point2f vtx[4];
		rbox.points(vtx);

		//���㳤����
		float Y = sqrt((vtx[0].y - vtx[1].y) * (vtx[0].y - vtx[1].y) + (vtx[0].x - vtx[1].x) * (vtx[0].x - vtx[1].x));
		float X = sqrt((vtx[1].y - vtx[2].y) * (vtx[1].y - vtx[2].y) + (vtx[1].x - vtx[2].x) * (vtx[1].x - vtx[2].x));
		//�ж�����
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