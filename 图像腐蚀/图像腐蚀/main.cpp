#include<opencv2\highgui\highgui.hpp>	// OpenCV highguiģ��ͷ�ļ�
#include<opencv2\imgproc\imgproc.hpp>	// OpenCV ͼ����ͷ�ļ�
using namespace cv;

int main()
{
	// ����ԭͼ
	Mat srcImage = imread("..\\..\\0.jpg");
	// ��ʾԭͼ
	imshow("[ԭͼ]��ʴ����", srcImage);
	// ���и�ʴ����
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat dstImage;
	erode(srcImage, dstImage, element);
	// ��ʾЧ��ͼ
	imshow("[Ч��ͼ]��ʴ����", dstImage);
	waitKey(0);
	return 0;
}