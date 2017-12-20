#include<opencv2\core.hpp>
#include<highgui.hpp>
using namespace cv;

int main()
{
	Mat image = imread("..//..//0.jpg", -2);
	imshow("", image);
	waitKey(0);
	return 0;
}