#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc.hpp>
using namespace cv;

int main()
{
	// 载入原始图
	Mat srcImage = imread("..\\..\\0.jpg");

	// 显示原始图
	imshow("均值滤波【原始图】", srcImage);
	
	// 进行均值滤波操作
	Mat dstImage;
	blur(srcImage, dstImage, Size(7, 7));

	// 显示效果图
	imshow("均值滤波【效果图】", dstImage);
	waitKey(0);
	return 0;
}