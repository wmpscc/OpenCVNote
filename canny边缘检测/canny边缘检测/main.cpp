#include<opencv2\highgui\highgui.hpp>
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>
using namespace cv;

int main()
{
	Mat srcImage = imread("..\\..\\1.jpg");
	imshow("【原始图】Canny边缘检测", srcImage);
	Mat dstImage, edge, grayImage;

	// 创建于src同类型和大小的矩阵（dst）
	dstImage.create(srcImage.size(), srcImage.type());

	// 将原图像转换为灰度图
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);

	// 先使用 3*3内核来降噪
	blur(grayImage, edge, Size(3, 3));

	// 运行Canny 算子
	Canny(edge, edge, 3, 9, 3);

	// 显示效果图
	imshow("【效果图】Canny边缘检测", edge);

	waitKey(0); 


	return 0;
}