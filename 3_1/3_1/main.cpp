#include<core.hpp>
#include<highgui.hpp>
using namespace cv;
int main()
{
	Mat top = imread("..\\..\\0.jpg");
	namedWindow("top");
	imshow("top", top); // 显示到窗口名一样的窗口

	Mat below = imread("..\\..\\1.jpg");
	namedWindow("below");
	imshow("below", below);

	Mat imageROI;
	imageROI = top(Rect(0, 0, below.cols, below.rows));
	addWeighted(imageROI, 0.5, below, 0.3, 0., imageROI);

	//imshow("maix", top);
	imwrite("..\\..\\3.jpg", top);
	waitKey();
	return 0;
}