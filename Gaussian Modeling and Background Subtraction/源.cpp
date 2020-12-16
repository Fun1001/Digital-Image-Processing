#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;


int Gaussianmodeling(std::vector<cv::Mat> srcMat, Mat& meanMat, Mat& varMat)
{
	int row = srcMat[0].rows;
	int col = srcMat[0].cols;

	for (int h=0; h < row; h++)
	{
		for (int w=0; w < col; w++)
		{
			int sum = 0;
			float var = 0;
			for (int i = 0; i < srcMat.size(); i++)
			{
				sum += srcMat[i].at<uchar>(h, w);
			}
			meanMat.at<uchar>(h, w) = sum / srcMat.size();//均值
			for (int j=0; j < srcMat.size(); j++)
			{
				var += pow((srcMat[j].at<uchar>(h, w) - meanMat.at<uchar>(h, w)), 2);
			}
			varMat.at<float>(h, w) = var / srcMat.size();//方差
		}
	}
	return 0;
}

int Gaussiansubtraction(Mat srcMat, Mat meanMat, Mat varMat, float srcth, Mat& dstMat)
{
	int row = srcMat.rows;
	int col = srcMat.cols;

	for (int h = 0; h < row; h++)
	{
		for (int w = 0; w < col; w++)
		{
			int dif = abs(srcMat.at<uchar>(h, w) - meanMat.at<uchar>(h, w));//差分
			int newth = srcth * varMat.at<float>(h, w);//新阈值
			if (dif > newth)
			{
				dstMat.at<uchar>(h, w) = 255;
			}
			else
			{
				dstMat.at<uchar>(h, w) = 0;
			}
		}
	}
	return 0;
}


int main()
{
	VideoCapture capvideo(0);//打开摄像头
	if (!capvideo.isOpened())
	{
		std::cout << "can not open the camera" << std::endl;
		return -1;
	}

	std::vector<cv::Mat> srcMats;//用于创建高斯背景模型的图像帧
	int nbg = 150;//创建背景图像所用帧数
	float srcth = 1;//原阈值
	int cnt = 0;//计数
	Mat frame;
	Mat meanMat;
	Mat varMat;
	Mat dstMat;

	while (1)
	{
		capvideo >> frame;
		cvtColor(frame, frame, COLOR_BGR2GRAY);
		if (cnt < nbg)//背景计算
		{
			srcMats.push_back(frame);//浅复制
			if (cnt == 0)
			{
				cout << "reading frame" << endl;
			}
		}
		else if (cnt == nbg)//计算模型
		{
			meanMat.create(frame.size(), CV_8UC1);
			varMat.create(frame.size(), CV_32FC1);
			
			Gaussianmodeling(srcMats, meanMat, varMat);std::cout << "calculating background models" << std::endl;
		}
		else//背景差分
		{
			dstMat.create(frame.size(), CV_8UC1);
			Gaussiansubtraction(frame, meanMat, varMat, srcth, dstMat);
			imshow("dstMat", dstMat);
			imshow("frame", frame);
			waitKey(30);
		}
		cnt++;
	}
	return 0;
}