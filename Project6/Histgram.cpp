#include<opencv2/opencv.hpp>
#include<ios>

using namespace cv;
using namespace std;

int main()
{
	cv::Mat src = imread("E:/timg.jpg", 0);
	int a = src.channels();
	std::cout << "a=" << a << std::endl;//Í¨µÀÊý

	int ele = src.rows * src.cols;

	float histgram[256] = { 0 };
	for (int j = 0; j < src.rows; j++)
	{
		uchar* data = src.ptr<uchar>(j);
		for (int i = 0; i < src.cols; i++)
		{
			histgram[data[i]] = histgram[data[i]] + 1;
		}
	}

	for (int i = 0; i < 256; i++)
	{
		histgram[i] = histgram[i] / ele;
		std::cout << "histgram" << histgram[i]<< std::endl;
	}

	int his_h = 256;
	int his_w = 200;
	cv::Mat his(his_w, his_h, CV_8UC3, Scalar(0, 0, 0));

	/*draw rectangle
	cv::Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.width = 1;
	for (int i = 0; i < 256; i++)
	{
		rect.x = rect.x + 1;
		rect.height = histgram[i]*3000;
		rectangle(his, rect, CV_RGB(255, 0, 0),1, 8, 0);
	}*/

	//draw line
	cv::Point pt1, pt2;
	pt1.x = 0;
	pt1.y = 199;
	pt2.x = 0;
	pt2.y = 0;
	for (int i = 0; i < 256; i++)
	{
		pt2.y = pt1.y - histgram[i] * 3000;
		pt2.x = pt1.x + 1;
		pt1.x = pt2.x;
		line(his, pt1, pt2, CV_RGB(255, 0, 0), 1, 8, 0);
	}

	imshow("his", his);

	waitKey(0);
	return 0;
}