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
		cv::Mat dx;
		cv::Mat dy;
		//±ßÔµÌáÈ¡
		Sobel(frame, dx, CV_8UC1, 1, 0, 3);
		Sobel(frame, dy, CV_8UC1, 0, 1, 3);
		if (!rSucess)
		{
			std::cout << "can not read the frame from the video" << std::endl;
			break;
		}
		else
		{
			imshow("Êú", dx);
			imshow("ºá", dy);
		}
		waitKey(30);
	}
	return 0;
}