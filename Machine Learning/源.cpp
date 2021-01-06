#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;
int createMaskByKmeans(cv::Mat src, cv::Mat& mask);
//VideoCapture createInput(bool useCamera, std::string videoPath)
//{
//	//ѡ������
//	VideoCapture capVideo;
//	if (useCamera) {
//		capVideo.open(0);
//	}
//	else {
//		capVideo.open(videoPath);
//	}
//	return capVideo;
//}
//�ڶ���
void segColor()
{
	Mat src = imread("E:\\movie.jpg");

	Mat mask = Mat::zeros(src.size(), CV_8UC1);
	createMaskByKmeans(src, mask);

	imshow("src", src);
	imshow("mask", mask);

	waitKey(0);

}
//��һ��
//int kMeansDemo()
//{
//	const int MAX_CLUSTERS = 5;
//	Scalar colorTab[] =
//	{
//		Scalar(0, 0, 255),
//		Scalar(0,255,0),
//		Scalar(255,100,100),
//		Scalar(255,0,255),
//		Scalar(0,255,255)
//	};
//
//	Mat img(500, 500, CV_8UC3);
//	RNG rng(12345);
//
//	for (;;)
//	{
//		int k, clusterCount = rng.uniform(2, MAX_CLUSTERS + 1);
//		int i, sampleCount = rng.uniform(1, 1001);
//		Mat points(sampleCount, 1, CV_32FC2), labels;
//
//		clusterCount = MIN(clusterCount, sampleCount);
//		std::vector<Point2f> centers;
//
//		/* generate random sample from multigaussian distribution */
//		for (k = 0; k < clusterCount; k++)
//		{
//			Point center;
//			center.x = rng.uniform(0, img.cols);
//			center.y = rng.uniform(0, img.rows);
//			Mat pointChunk = points.rowRange(k * sampleCount / clusterCount,
//				k == clusterCount - 1 ? sampleCount :
//				(k + 1) * sampleCount / clusterCount);
//			rng.fill(pointChunk, RNG::NORMAL, Scalar(center.x, center.y), Scalar(img.cols * 0.05, img.rows * 0.05));
//		}
//
//		randShuffle(points, 1, &rng);
//
//		double compactness = kmeans(points,MAX_CLUSTERS-1,labels ,
//			TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 1.0),
//			3, KMEANS_PP_CENTERS, centers);
//
//		img = Scalar::all(0);
//
//		for (i = 0; i < sampleCount; i++)
//		{
//			int clusterIdx = labels.at<int>(i);
//			Point ipt = points.at<Point2f>(i);
//			circle(img, ipt, 2, colorTab[clusterIdx], FILLED, LINE_AA);
//		}
//		for (i = 0; i < (int)centers.size(); ++i)
//		{
//			Point2f c = centers[i];
//			circle(img, c, 40, colorTab[i], 1, LINE_AA);
//		}
//		cout << "Compactness: " << compactness << endl;
//
//		imshow("clusters", img);
//
//		char key = (char)waitKey();
//		if (key == 27 || key == 'q' || key == 'Q') // 'ESC'
//			break;
//	}
//
//	return 0;
//}

int createMaskByKmeans(cv::Mat src, cv::Mat& mask)
{
	if ((mask.type() != CV_8UC1)
		|| (src.size() != mask.size())
		) {
		return 0;
	}

	int width = src.cols;
	int height = src.rows;

	int pixNum = width * height;
	int clusterCount=2;
	Mat labels;
	Mat centers;

	//����kmeans�õ�����
	Mat sampleData = src.reshape(3, pixNum);
	Mat km_data;
	sampleData.convertTo(km_data, CV_32F);

	//ִ��kmeans
	TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.1);
	kmeans(km_data, clusterCount, labels, criteria, clusterCount, KMEANS_PP_CENTERS, centers);

	//����mask
	uchar fg[2] = { 0,255 };
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			mask.at<uchar>(row, col) = fg[labels.at<int>(row * width + col)];
		}
	}

	return 0;
}

int main()
{
	//��ʼ��ʱ
	double start = static_cast<double>(cvGetTickCount());

	segColor();

	//kMeansDemo();

	//������ʱ
	double time = ((double)cvGetTickCount() - start) / cvGetTickFrequency();
	//��ʾʱ��
	cout << "processing time:" << time / 1000 << "ms" << endl;

	//�ȴ�������Ӧ�����������������
	system("pause");
	return 0;
}
