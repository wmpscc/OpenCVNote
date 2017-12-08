#include<opencv2\opencv.hpp>
using namespace cv;

int main()
{
	VideoCapture capture;
	capture.open(0);

	Mat edges;
	
	while (true)
	{
		// 读入图像
		Mat frame;
		capture >> frame;

		// 将原图像转换为灰度图
		cvtColor(frame, edges, CV_BGR2GRAY);

		// 使用3*3内核来降噪（2*3+1 = 7）
		blur(edges, edges, Size(7, 7));// 进行模糊

		// 进行canny 边缘检测并显示
		Canny(frame, edges, 0, 30, 3);
		imshow("被canny后的视频", edges);
		if (waitKey(30) >= 0)break;	// 延时30ms
	}
	return 0;
}