#include<opencv2/opencv.hpp>
#include<iostream>
#include<cmath>

using namespace std;
using namespace cv;

Mat gammaTransform(Mat& srcMat, float gamma)
{
	unsigned char lut[256];
	for (int i = 0; i < 256; i++)
	{
		lut[i] = saturate_cast<uchar>(pow((float)(i / 255.0), gamma) * 255.0f);
	}
	Mat dstMat = srcMat.clone();
	if (srcMat.channels() == 1)
	{
		MatIterator_<uchar> iterator = dstMat.begin<uchar>();
		MatIterator_<uchar> iteratorend = dstMat.end<uchar>();
		for (; iterator != iteratorend; iterator++)
		{
			*iterator = lut[(*iterator)];
		}

	}
	else
	{
		MatIterator_<Vec3b> iterator = dstMat.begin<Vec3b>();
		MatIterator_<Vec3b> iteratorend = dstMat.end<Vec3b>();
		for (; iterator != iteratorend; iterator++)
		{
			(*iterator)[0] = lut[((*iterator)[0])];//b
			(*iterator)[1] = lut[((*iterator)[1])];//g
			(*iterator)[2] = lut[((*iterator)[2])];//r
		}
	}
	return dstMat;
}

int main()
{
	Mat srcMat=imread("E:\\6.jpg");
	
	float gamma1 = 2.2f;
	float gamma2 = 1 / gamma1;
	Mat dstMat1 = gammaTransform(srcMat, gamma1);
	Mat dstMat2 = gammaTransform(srcMat, gamma2);

	imshow("ԭͼ", srcMat);
	imshow("gamma=2.2", dstMat1);
	imshow("gamma=1/2.2", dstMat2);

	waitKey(0);
	return 0;
	
}

