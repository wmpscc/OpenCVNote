#include<opencv2\opencv.hpp>
using namespace cv;

int main()
{
	// 从摄像头读入视频
	VideoCapture capture(0);

	// 循环显示每一帧
	while (true)
	{
		Mat frame;
		capture >> frame;
		imshow("", frame);
		waitKey(30);
	}

	return 0;
}