#include<opencv2\opencv.hpp>
using namespace cv;

int main()
{
	// ������ͷ������Ƶ
	VideoCapture capture(0);

	// ѭ����ʾÿһ֡
	while (true)
	{
		Mat frame;
		capture >> frame;
		imshow("", frame);
		waitKey(30);
	}

	return 0;
}