#include<core.hpp>
#include<highgui.hpp>
#include<stdio.h>
using namespace cv;

int __main()
{
	//1.input image
	Mat srcImage1 = imread("..//..//3.jpg");
	Mat logoImage = imread("..//..//1.jpg");
	if (!srcImage1.data)
	{
		printf("读取srcImage1错误\n");
		return 0;
	}
	if (!logoImage.data)
	{
		printf("读取logoImage错误\n");
		return 0;
	}
	//2.define ROI
	Mat imageROI = srcImage1(Rect(100, 150, logoImage.cols, logoImage.rows));
	
	//3.make mask  (mast be grey value image)
	Mat mask = imread("..//..//4.img", 0);

	//4.mask to ROI
	logoImage.copyTo(imageROI, mask);

	//show dstimage
	namedWindow("<1>利用ROI实现图像叠加示例窗口");
	imshow("<1>利用ROI实现图像叠加示例窗口", srcImage1);
	waitKey(0);
	return 0;
}