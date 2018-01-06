#include<core.hpp>
#include<highgui.hpp>
#include<stdio.h>
using namespace cv;

int ___main()
{
	//0.定义一些局部变量
	double alphaValue = 0.5;
	double betaValue;
	Mat srcImage2, srcImage3, dstImage;

	//1.读取图像（两幅图像需为同样的类型和尺寸)
	srcImage2 = imread("..//..//3.jpg");
	srcImage3 = imread("..//..//4.jpg");
	if (!srcImage2.data)
	{
		printf("读取srcImage2错误");
	}
	if (!srcImage3.data)
	{
		printf("读取srcImage3错误");
	}

	//2.做图像混合加权操作
	betaValue = (1.0 - alphaValue);
	addWeighted(srcImage2, alphaValue, srcImage3, betaValue, 0.0, dstImage);

	//3.创建并显示原图窗口
	namedWindow("<2>线性混合示例窗口【原图】", 1);
	imshow("<2>线性混合示例窗口【原图】", srcImage2);

	namedWindow("<3>线性混合示例窗口【效果图】");
	imshow("<3>线性混合示例窗口【效果图】", dstImage);
	waitKey(0);

	return 0;
}