#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat Erode, Dilate, Open, Close;
	cv::Mat Binary;
	cv::Mat src = imread("E:\\coin.jpg", 0);							//�Ҷ�ͼ

	cv::threshold(src, Binary, 0, 255, THRESH_OTSU);					//��ֵ��
	
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));			//3*3����

	erode(Binary, Erode, kernel);										//��ʴ
	dilate(Binary, Dilate, kernel);										//����
	morphologyEx(Binary, Open, MORPH_OPEN, kernel);						//������
	morphologyEx(Binary, Close, MORPH_CLOSE, kernel);					//������

	imshow("Binary", Binary);
	imshow("Erode", Erode);
	imshow("Dilate", Dilate);
	imshow("Open", Open);
	imshow("Close", Close);

	waitKey(0);
	return 0;
}