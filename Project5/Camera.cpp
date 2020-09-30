#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
int main() 
{
	VideoCapture cap;
	cap.open(0);

	if (!cap.isOpened())
	{
		std::cout << "无法打开文件" << std::endl;
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
		std::cout << "无法从文件中读取帧" << std::endl;
			break;
		}
		else
		{
			cv::imshow("frame", frame);
		}
		waitKey(30);
	}

	return 0;
}