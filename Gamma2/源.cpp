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
		//saturate_cast����ֹ����ֵ��������ֵ<0,�򷵻�0���������255���򷵻�255
	}
	Mat dstMat = srcMat.clone();
	//��ͨ��
	if (srcMat.channels() == 1)
	{
		MatIterator_<uchar> iterator = dstMat.begin<uchar>();
		MatIterator_<uchar> iteratorend = dstMat.end<uchar>();
		for (; iterator != iteratorend; iterator++)
		{
			*iterator = lut[(*iterator)];
		}

	}
	//��ͨ��
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
	Mat srcMat = imread("E:\\7.jpg",0);

	float gamma = 0.46f;
	Mat dstMat = gammaTransform(srcMat, gamma);

	imshow("ԭͼ", srcMat);
	imshow("gamma����", dstMat);

	waitKey(0);
	return 0;

}

