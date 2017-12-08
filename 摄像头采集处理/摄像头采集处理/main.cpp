#include<opencv2\opencv.hpp>
using namespace cv;

int main()
{
	VideoCapture capture;
	capture.open(0);

	Mat edges;
	
	while (true)
	{
		// ����ͼ��
		Mat frame;
		capture >> frame;

		// ��ԭͼ��ת��Ϊ�Ҷ�ͼ
		cvtColor(frame, edges, CV_BGR2GRAY);

		// ʹ��3*3�ں������루2*3+1 = 7��
		blur(edges, edges, Size(7, 7));// ����ģ��

		// ����canny ��Ե��Ⲣ��ʾ
		Canny(frame, edges, 0, 30, 3);
		imshow("��canny�����Ƶ", edges);
		if (waitKey(30) >= 0)break;	// ��ʱ30ms
	}
	return 0;
}