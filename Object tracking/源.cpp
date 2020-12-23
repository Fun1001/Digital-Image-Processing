#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

void myharris(Mat& gray, int nX, int nY, float* ref_hist)
{
	Mat gx, gy;
	Mat mag, angle;
	cv::Sobel(gray, gx, CV_32F, 1, 0, 1);
	cv::Sobel(gray, gy, CV_32F, 0, 1, 1);
	cartToPolar(gx, gy, mag, angle, true);

	int c = 0;
	//遍历所有
	for (int i = 0; i < nY; i++) {
		for (int j = 0; j < nX; j++) {
			for (int m = 0; m < 16; m++) {
				for (int n = 0; n < 16; n++) {
					int k = (int)(angle.at<float>(i * 16 + m, j * 16 + n) / 45);//量化
					ref_hist[(i * nX + j) * 8 + k] += mag.at<float>(i * 16 + m, j * 16 + n);//累加梯度
				}
			}
		}
	}
}

int main() 
{
	Mat cell = imread("D:\\template.jpg", 0);
	Mat src = imread("D:\\src.jpg");
	Mat comp;
	Mat gray = imread("D:\\src.jpg", 0);
	int cellSize = 16;
	int nX = cell.cols / cellSize;
	int nY = cell.rows / cellSize;
	int bins = 8 * nX * nY;

	while (1)
	{
		float* template_hist = new float[bins];
		memset(template_hist, 0, sizeof(float) * bins);

		myharris(cell, nX, nY, template_hist);//模板HOG

		float distanceMin;
		Rect dstRect;

		for (int j = 0; j < src.rows - cell.rows; j++)
		{
			for (int i = 0; i < src.cols - cell.cols; i++)
			{
				Rect rect(i, j, cell.cols, cell.rows);
				comp = Mat(src, rect);	//切割

				float* compare_hist = new float[bins];
				memset(compare_hist, 0, sizeof(float) * bins);

				myharris(comp, nX, nY, compare_hist);//HOG

				float distance = 0;
				for (int k = 0; k < bins; k++)
				{
					distance += pow(template_hist[k] - compare_hist[k], 2);
				}
				distance = sqrt(distance);
				if (j == 0) {
					distanceMin = distance;
				}
				else if (distance < distanceMin) {
					distanceMin = distance;
					dstRect = rect;
				}

				delete[] compare_hist;

			}
		}

		rectangle(src, dstRect, Scalar(0, 0, 255));

		cv::imshow("template", cell);
		cv::imshow("src", src);

		delete[] template_hist;

		waitKey(0);
	}
	return 0;
}


void myharris(Mat& gray, int nX, int nY, float* ref_hist) 
{
	Mat gx, gy;
	Mat mag, angle;
	cv::Sobel(gray, gx, CV_32F, 1, 0, 1);
	cv::Sobel(gray, gy, CV_32F, 0, 1, 1);
	cartToPolar(gx, gy, mag, angle, true);

	int c = 0;
	//遍历所有
	for (int i = 0; i < nY; i++) {
		for (int j = 0; j < nX; j++) {
			for (int m = 0; m < 16; m++) {
				for (int n = 0; n < 16; n++) {
					int k = (int)(angle.at<float>(i * 16 + m, j * 16 + n) / 45);//量化
					ref_hist[(i * nX + j) * 8 + k] += mag.at<float>(i * 16 + m, j * 16 + n);//累加梯度
				}
			}
		}
	}
}