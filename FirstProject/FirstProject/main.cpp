#include<opencv2\opencv.hpp>
using namespace cv;

void main()
{
	Mat srcImage = imread("C:\\Users\\wmpscc\\Desktop\\0.jpg");
	imshow("ԭʼͼ", srcImage);
	waitKey(6000);
}