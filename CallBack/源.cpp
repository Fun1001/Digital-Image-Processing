#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

string window_name = "binaryMat";

void threshod_Mat(int th, void* data)
{
	Mat src = *(Mat*)(data);

	Mat dst;
	//��ֵ��
	threshold(src, dst, th, 255, 0);

	imshow(window_name, dst);

}

int main()
{
	int lowTh = 30;
	int maxTh = 255;

	Mat srcMat = imread("E:\\timg.jpg",0);
	if (!srcMat.data)//�ж�ͼ���Ƿ�����
	{
		cout << "ͼ������ʧ�ܣ�" << std::endl;
		return 0;
	}

	imshow(window_name, srcMat);
	createTrackbar("threshold",
					window_name,
					&lowTh,
					maxTh,
					threshod_Mat,
					&srcMat);

	waitKey(0);

	return 0;

}