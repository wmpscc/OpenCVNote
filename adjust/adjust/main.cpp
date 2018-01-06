#include<core.hpp>
#include<highgui.hpp>
#include<iostream>
using namespace std;
using namespace cv;

static void on_ContrastAndBright(int, void*);

int g_nContrastValue;	//对比度值
int g_nBrightValue;		//亮度值
Mat g_srcImage, g_dstImage;

int main()
{
	//1.读取输入图像
	g_srcImage = imread("F:\\Note\\OpenCV\\OpenCVNote\\5.jpg");
	if (!g_srcImage.data)
	{
		printf("读取图片错误，请确定目录下是否有该图片");
		return false;
	}
	g_dstImage = Mat::zeros(g_srcImage.size(), g_srcImage.type());
	//2.设定对比度和亮度的初值
	g_nContrastValue = 80;
	g_nBrightValue = 80;

	//3.创建效果图窗口
	namedWindow("【效果图窗口】", 1);

	//4.创建轨迹条
	createTrackbar("对比度：", "【效果图窗口】", &g_nContrastValue, 100, on_ContrastAndBright);
	createTrackbar("亮度：", "【效果图窗口】", &g_nBrightValue, 100, on_ContrastAndBright);

	//5.进行回调函数初始化
	on_ContrastAndBright(g_nContrastValue, 0);
	on_ContrastAndBright(g_nBrightValue, 0);

	//6.按下"q"键是，程序退出
	while (char(waitKey(1)) != 'q') {

	}
	return 0;
}

static void on_ContrastAndBright(int, void*)
{
	//创建窗口
	namedWindow("【原始图窗口】", 1);
	//三个for循环，执行运算 g_dstImage(i,j) = a*g_srcImage(i,j) + b
	for (int y = 0; y < g_srcImage.rows; y++)
	{
		for (int x = 0; x < g_srcImage.cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				g_dstImage.at<Vec3b>(y, x)[c] = saturate_cast<uchar>((g_nContrastValue*0.01)*(g_srcImage.at<Vec3b>(y, x)[c]) + g_nBrightValue);

			}
		}
	}
	//显示图像
	imshow("【原始图窗口】", g_srcImage);
	imshow("【效果图窗口】", g_dstImage);
}