#include<opencv2\opencv.hpp>
using namespace cv;

void main()
{
	Mat srcImage = imread("..\\0.jpg");
	imshow("ԭʼͼ", srcImage);
	waitKey(6000);
}