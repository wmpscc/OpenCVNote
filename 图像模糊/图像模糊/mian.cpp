#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc.hpp>
using namespace cv;

int main()
{
	// ����ԭʼͼ
	Mat srcImage = imread("..\\..\\0.jpg");

	// ��ʾԭʼͼ
	imshow("��ֵ�˲���ԭʼͼ��", srcImage);
	
	// ���о�ֵ�˲�����
	Mat dstImage;
	blur(srcImage, dstImage, Size(7, 7));

	// ��ʾЧ��ͼ
	imshow("��ֵ�˲���Ч��ͼ��", dstImage);
	waitKey(0);
	return 0;
}