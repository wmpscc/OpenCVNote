#include<iostream>
#include<highgui.hpp>
#include<core.hpp>
using namespace cv;
using namespace std;

bool MultiChannelBlending();

int ____main()
{
	system("color 9F");
	if (MultiChannelBlending())
	{
		cout << endl << "\n运行成功，得出了需要的图像";
	}
	waitKey(0);
	return 0;
}

bool MultiChannelBlending()
{
	//0.定义相关变量
	Mat srcImage;
	Mat logoImage;
	vector<Mat> channels;
	Mat imageBlueChannel;

	//多通道混合蓝色通道部分
	//1.读入图片
	logoImage = imread("..//..//1.jpg", 0);
	srcImage = imread("..//..//3.jpg");
	if (!logoImage.data)
	{
		printf("读取logoImage错误\n");
		return false;
	}
	if (!srcImage.data)
	{
		printf("读取srcImage错误\n");
		return false;
	}
	imshow("srcImage【原图】", srcImage);
	//2.把一个3通道图像转换成3个单通道图像
	split(srcImage, channels);	//分离色彩通道
	
	//3.将原图的蓝色通道引用返回给imageBlueChannel，注意是引用，相当于两者等价，修改一个另一个跟着变
	imageBlueChannel = channels.at(0);
	//4.将原图的蓝色通道的(500,250)坐标处右下方的一块区域和logo图进行加权操作，将得到的混合结果存到imageBlueChannel中
	addWeighted(imageBlueChannel(Rect(100, 100, logoImage.cols, logoImage.rows)), 1.0, logoImage, 0.5, 0, imageBlueChannel(Rect(100, 100, logoImage.cols, logoImage.rows)));
	//5.将三个单通道重新合并成一个三通道
	merge(channels, srcImage);
	//6.显示效果图
	namedWindow("<1>游戏原画+logo蓝色通道");
	imshow("<1>游戏原画+logo蓝色通道", srcImage);


	//多通道混合绿色通道部分
	//0.定义相关变量
	Mat imageGreenChannel;

	//1.读入图片
	logoImage = imread("..//..//1.jpg", 0);
	srcImage = imread("..//..//3.jpg");
	if (!logoImage.data)
	{
		printf("读取logoImage错误\n");
		return false;
	}
	if (!srcImage.data)
	{
		printf("读取srcImage错误\n");
		return false;
	}
	//2.把一个3通道图像转换成3个单通道图像
	split(srcImage, channels);	//分离色彩通道

								//3.将原图的蓝色通道引用返回给imageGreenChannel，注意是引用，相当于两者等价，修改一个另一个跟着变
	imageGreenChannel = channels.at(1);
	//4.将原图的蓝色通道的(500,250)坐标处右下方的一块区域和logo图进行加权操作，将得到的混合结果存到imageGreenChannel中
	addWeighted(imageGreenChannel(Rect(100, 100, logoImage.cols, logoImage.rows)), 1.0, logoImage, 0.5, 0, imageGreenChannel(Rect(100, 100, logoImage.cols, logoImage.rows)));
	//5.将三个单通道重新合并成一个三通道
	merge(channels, srcImage);
	//6.显示效果图
	namedWindow("<2>游戏原画+logo绿色通道");
	imshow("<2>游戏原画+logo绿色通道", srcImage);


	//多通道混合红色通道部分
	//0.定义相关变量
	Mat imageRedChannel;

	//1.读入图片
	logoImage = imread("..//..//1.jpg", 0);
	srcImage = imread("..//..//3.jpg");
	if (!logoImage.data)
	{
		printf("读取logoImage错误\n");
		return false;
	}
	if (!srcImage.data)
	{
		printf("读取srcImage错误\n");
		return false;
	}
	//2.把一个3通道图像转换成3个单通道图像
	split(srcImage, channels);	//分离色彩通道

								//3.将原图的蓝色通道引用返回给imageRedChannel，注意是引用，相当于两者等价，修改一个另一个跟着变
	imageRedChannel = channels.at(2);
	//4.将原图的蓝色通道的(500,250)坐标处右下方的一块区域和logo图进行加权操作，将得到的混合结果存到imageRedChannel中
	addWeighted(imageRedChannel(Rect(100, 100, logoImage.cols, logoImage.rows)), 1.0, logoImage, 0.5, 0, imageRedChannel(Rect(100, 100, logoImage.cols, logoImage.rows)));
	//5.将三个单通道重新合并成一个三通道
	merge(channels, srcImage);
	//6.显示效果图
	namedWindow("<3>游戏原画+logo红色通道");
	imshow("<3>游戏原画+logo红色通道", srcImage);

	return true;

}