#include<core.hpp>
#include<highgui.hpp>
#include<stdio.h>
using namespace cv;

int ___main()
{
	//0.����һЩ�ֲ�����
	double alphaValue = 0.5;
	double betaValue;
	Mat srcImage2, srcImage3, dstImage;

	//1.��ȡͼ������ͼ����Ϊͬ�������ͺͳߴ�)
	srcImage2 = imread("..//..//3.jpg");
	srcImage3 = imread("..//..//4.jpg");
	if (!srcImage2.data)
	{
		printf("��ȡsrcImage2����");
	}
	if (!srcImage3.data)
	{
		printf("��ȡsrcImage3����");
	}

	//2.��ͼ���ϼ�Ȩ����
	betaValue = (1.0 - alphaValue);
	addWeighted(srcImage2, alphaValue, srcImage3, betaValue, 0.0, dstImage);

	//3.��������ʾԭͼ����
	namedWindow("<2>���Ի��ʾ�����ڡ�ԭͼ��", 1);
	imshow("<2>���Ի��ʾ�����ڡ�ԭͼ��", srcImage2);

	namedWindow("<3>���Ի��ʾ�����ڡ�Ч��ͼ��");
	imshow("<3>���Ի��ʾ�����ڡ�Ч��ͼ��", dstImage);
	waitKey(0);

	return 0;
}