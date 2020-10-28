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
		if (!rSucess)
		{
			std::cout << "can not read the frame from the video" << std::endl;
			break;
		}
		else
		{
			cv::Mat dstMat;
			//中值滤波
			medianBlur(frame, dstMat, 5);
			imshow("中值滤波", dstMat);
		}
		waitKey(30);
	}
	return 0;
}