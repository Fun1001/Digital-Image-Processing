#include<opencv2/opencv.hpp>
#include<iostream>

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
	Mat bgMat;
	Mat subMat;
	Mat bny_subMat;

	while (1)
	{
		capvideo >> frame;
		cvtColor(frame, frame, COLOR_BGR2GRAY);

		if (cnt == 0)//�ڵ�һ֡��ȡ����ͼ��
		{
			frame.copyTo(bgMat);
		}
		else//�ӵڶ�֡��ʼ�������
		{
			absdiff(frame, bgMat, subMat);//��ǰ֡�뱳����֣��ó�����
			threshold(subMat, bny_subMat, 50, 255, CV_THRESH_BINARY);//��ֽ����ֵ��

			imshow("bny_subMat", bny_subMat);
			imshow("subMat", subMat);

			waitKey(30);
		}
		cnt++;
	}
	return 0;
}