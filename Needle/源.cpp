#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main()
{
	cv::Mat labelsMat, statsMat, centrMat;
	cv::Mat erodeMat, dstMat;
	cv::Mat srcMat = imread("E:\\Needle.jpg", 0);
	//¶þÖµ»¯
	cv::threshold(srcMat, dstMat, 0, 255, THRESH_OTSU);
	cv::Mat binaryMat = 255 - dstMat;//×ªÖÃ
	
	//°Ñ°×±ßÖÃºÚ£¬×ªÎª±³¾°
	for (int i=0; i < 5; i++)
	{
		for (int j=0; j < binaryMat.rows; j++)
		{
			binaryMat.at<Vec3b>(j, i)[0] = 0;
			binaryMat.at<Vec3b>(j, i)[1] = 0;
			binaryMat.at<Vec3b>(j, i)[2] = 0;
		}
	}
	imshow("2", binaryMat);

	//¸¯Ê´
	Mat kernel = getStructuringElement(MORPH_RECT, Size(8,2 ));
	erode(binaryMat, erodeMat, kernel);
	int nComp = connectedComponentsWithStats(
		erodeMat,
		labelsMat,
		statsMat,
		centrMat,
		8,
		CV_32S
	);
	cout << "The number of needle£º" << nComp - 1 << endl;

	//»­¿òÍ¼
	for (int i = 0; i < nComp; i++)
	{
		cv::Rect boundingbox;
		boundingbox.x = statsMat.at<int>(i, 0);
		boundingbox.y = statsMat.at<int>(i, 1);
		boundingbox.width = statsMat.at<int>(i, 2);
		boundingbox.height = statsMat.at<int>(i, 3);
		rectangle(srcMat, boundingbox, CV_RGB(255, 255, 255), 1, 8, 0);
	}
	imshow("1", srcMat);
	waitKey(0);
	return 0;
}