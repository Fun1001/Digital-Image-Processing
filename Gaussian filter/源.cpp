#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap;
	cap.open(0);
	if (!cap.isOpened())
	{
		std::cout << "can not open the video" << std::endl;
		return -1;
	}
	double fps = cap.get(CAP_PROP_FPS);
	std::cout << "fps" << fps << std::endl;
	while (1)
	{
		cv::Mat frame;
		bool rSucess = cap.read(frame);
		cv::Mat dstMat;
		//��˹�˲�
		GaussianBlur(frame, dstMat,Size(11,11),0,0);
		if (!rSucess)
		{
			std::cout << "can not read the frame from the video" << std::endl;
			break;
		}
		else
		{
			imshow("��˹�˲�", dstMat);
		}
		waitKey(30);
	}
	return 0;
}