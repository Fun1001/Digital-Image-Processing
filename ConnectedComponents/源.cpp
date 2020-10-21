#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main()
{
	cv::Mat labelsMat, statsMat, centrMat;
	cv::Mat binaryMat,dilateMat;
	cv::Mat srcMat = imread("E:\\coin.jpg",0);

	//膨胀后二值化
	Mat kernel = getStructuringElement(MORPH_RECT, Size(4, 2));
	dilate(srcMat, dilateMat, kernel);
	cv::threshold(dilateMat, binaryMat, 0, 255, THRESH_OTSU);

	int nComp = connectedComponentsWithStats(
		binaryMat,
		labelsMat,
		statsMat,
		centrMat,
		8,
		CV_32S
	);
	cout << "硬币个数：" << nComp - 1 << endl;


	for (int i = 0; i < nComp; i++)
	{
		cv::Rect boundingbox;
		boundingbox.x = statsMat.at<int>(i, 0);
		boundingbox.y = statsMat.at<int>(i, 1);
		boundingbox.width = statsMat.at<int>(i, 2);
		boundingbox.height = statsMat.at<int>(i, 3);
		rectangle(srcMat, boundingbox, CV_RGB(255, 0, 0), 1, 8, 0);
	}
	imshow("result", srcMat);
	waitKey(0);
	return 0;


}