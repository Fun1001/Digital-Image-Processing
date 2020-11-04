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
		cv::Mat canny1;
		cv::Mat canny2;
		if (!rSucess)
		{
			std::cout << "can not read the frame from the video" << std::endl;
			break;
		}
		
		
		else
		{
			cvtColor(frame, frame, COLOR_BGR2GRAY);
			threshold(frame, frame,0,255,CV_THRESH_OTSU);

			//±ßÔµÌáÈ¡
			Sobel(frame, dx, CV_16SC1, 1, 0, 3);
			Sobel(frame, dy, CV_16SC1, 0, 1, 3);
			Canny(dx, dy, canny1, 20, 60);
			Canny(frame, canny2, 30, 70);
			imshow("1", canny1);
			imshow("2", canny2);
		}
		waitKey(30);
	}
	return 0;
}