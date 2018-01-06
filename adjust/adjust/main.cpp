#include<core.hpp>
#include<highgui.hpp>
#include<iostream>
using namespace std;
using namespace cv;

static void on_ContrastAndBright(int, void*);

int g_nContrastValue;	//�Աȶ�ֵ
int g_nBrightValue;		//����ֵ
Mat g_srcImage, g_dstImage;

int main()
{
	//1.��ȡ����ͼ��
	g_srcImage = imread("F:\\Note\\OpenCV\\OpenCVNote\\5.jpg");
	if (!g_srcImage.data)
	{
		printf("��ȡͼƬ������ȷ��Ŀ¼���Ƿ��и�ͼƬ");
		return false;
	}
	g_dstImage = Mat::zeros(g_srcImage.size(), g_srcImage.type());
	//2.�趨�ԱȶȺ����ȵĳ�ֵ
	g_nContrastValue = 80;
	g_nBrightValue = 80;

	//3.����Ч��ͼ����
	namedWindow("��Ч��ͼ���ڡ�", 1);

	//4.�����켣��
	createTrackbar("�Աȶȣ�", "��Ч��ͼ���ڡ�", &g_nContrastValue, 100, on_ContrastAndBright);
	createTrackbar("���ȣ�", "��Ч��ͼ���ڡ�", &g_nBrightValue, 100, on_ContrastAndBright);

	//5.���лص�������ʼ��
	on_ContrastAndBright(g_nContrastValue, 0);
	on_ContrastAndBright(g_nBrightValue, 0);

	//6.����"q"���ǣ������˳�
	while (char(waitKey(1)) != 'q') {

	}
	return 0;
}

static void on_ContrastAndBright(int, void*)
{
	//��������
	namedWindow("��ԭʼͼ���ڡ�", 1);
	//����forѭ����ִ������ g_dstImage(i,j) = a*g_srcImage(i,j) + b
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
	//��ʾͼ��
	imshow("��ԭʼͼ���ڡ�", g_srcImage);
	imshow("��Ч��ͼ���ڡ�", g_dstImage);
}