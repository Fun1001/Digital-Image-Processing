#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main()
{
	cv::Mat labelsMat, statsMat, centrMat;
	cv::Mat erodeMat, dstMat;
	cv::Mat srcMat = imread("E:\\PCB.jpg", 0);
	
	//二值化并转置
	cv::threshold(srcMat, dstMat, 0, 255, THRESH_OTSU);
	cv::Mat binaryMat = 255 - dstMat;
	//腐蚀
	Mat kernel = getStructuringElement(MORPH_RECT, Size(20, 20));
	erode(binaryMat, erodeMat, kernel);
	//连通域标记
	int nComp = connectedComponentsWithStats(
		erodeMat,
		labelsMat,
		statsMat,
		centrMat,
		8,
		CV_32S
	);
	cout << "原点个数：" << nComp - 1 << endl;
	imshow("1", erodeMat);
	waitKey(0);
	return 0;
}