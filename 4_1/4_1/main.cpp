#include<core.hpp>
#include<highgui.hpp>
#include<imgproc.hpp>
using namespace cv;

#define WINDOW_NAME1 "[����ͼ1]"	//Ϊ���ڱ��ⶨ��ĺ�
#define WINDOW_NAME2 "[����ͼ2]"	//Ϊ���ڱ��ⶨ��ĺ�
#define WINDOW_WIDTH 600			//���崰�ڴ�С�ĺ�

//���Ʋ�ͬ�Ƕȡ���ͬ�ߴ����Բ
void DrawEllipse(Mat img, double angle)
{
	int thickness = 2;
	int lineType = 8;
	ellipse(img, Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2), 
			Size(WINDOW_WIDTH / 4, WINDOW_WIDTH / 16), angle,
			0, 360, Scalar(255, 129, 0), thickness, lineType);
}

//����ʵ��Բ
void DrawFilledCircle(Mat img, Point center)
{
	int thickness = -1;	//�ߴ�
	int lineType = 8;
	circle(img, center, WINDOW_WIDTH / 32, Scalar(0, 0, 255), 
			thickness, lineType);
}

//ʵ�ְ�����λ���
void DrawPolygon(Mat img)
{
	int lineType = 8;

	//����һЩ��
	Point rootPoints[1][20];
	rootPoints[0][0] = Point(WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8);
	rootPoints[0][1] = Point(3 * WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8);
	rootPoints[0][2] = Point(3 * WINDOW_WIDTH / 4, 13 * WINDOW_WIDTH / 16);
	rootPoints[0][3] = Point(11 * WINDOW_WIDTH / 16, 13 * WINDOW_WIDTH / 16);
	rootPoints[0][4] = Point(19 * WINDOW_WIDTH / 32, 3 * WINDOW_WIDTH / 8);
	rootPoints[0][5] = Point(3 * WINDOW_WIDTH / 4, 3 * WINDOW_WIDTH / 8);
	rootPoints[0][6] = Point(3 * WINDOW_WIDTH / 4, WINDOW_WIDTH / 8);
	rootPoints[0][7] = Point(26 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
	rootPoints[0][8] = Point(26 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
	rootPoints[0][9] = Point(22 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
	rootPoints[0][10] = Point(22 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
	rootPoints[0][11] = Point(18 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
	rootPoints[0][12] = Point(18 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
	rootPoints[0][13] = Point(14 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
	rootPoints[0][14] = Point(14 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
	rootPoints[0][15] = Point(WINDOW_WIDTH / 4, WINDOW_WIDTH / 8);
	rootPoints[0][16] = Point(WINDOW_WIDTH / 4, 3 * WINDOW_WIDTH / 8);
	rootPoints[0][17] = Point(13 * WINDOW_WIDTH / 32, 3 * WINDOW_WIDTH / 8);
	rootPoints[0][18] = Point(5 * WINDOW_WIDTH / 16, 13 * WINDOW_WIDTH / 16);
	rootPoints[0][19] = Point(WINDOW_WIDTH / 4, 13 * WINDOW_WIDTH / 16);
	const Point* ppt[1] = { rootPoints[0] };
	int npt[] = { 20 };
	fillPoly(img, ppt, npt, 1, Scalar(255, 255, 255), lineType);
}

// ������
void DrawLine(Mat img, Point start, Point end)
{
	int thickness = 2;
	int lineType = 8;
	line(img, start, end, Scalar(0, 0, 0), thickness, lineType);
}


int main()
{
	//�����հ׵�Matͼ��
	Mat atomImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);
	Mat rookImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);
	
	//----------- ���ƻ�ѧ��ԭ�ӵ�ʾ��ͼ-----------
	//1.�Ȼ��Ƴ���Բ
	DrawEllipse(atomImage, 90);
	DrawEllipse(atomImage, 0);
	DrawEllipse(atomImage, 45);
	DrawEllipse(atomImage, -45);

	//2.�ٻ��Ƴ�Բ��
	DrawFilledCircle(atomImage, Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2));

	//----------- �������ͼ��----------------
	//1.�߻��Ƴ������
	DrawPolygon(rookImage);

	//2.���ƾ���
	rectangle(rookImage, Point(0, 7 * WINDOW_WIDTH),
			Point(WINDOW_WIDTH, WINDOW_WIDTH), Scalar(0, 255, 255), -1, 8);
	
	//2.����һЩ�߶�
	DrawLine(rookImage, Point(0, 15 * WINDOW_WIDTH / 16),
		Point(WINDOW_WIDTH, 15 * WINDOW_WIDTH / 16));
	DrawLine(rookImage, Point(WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8), 
			 Point(WINDOW_WIDTH / 4, WINDOW_WIDTH));
	DrawLine(rookImage, Point(WINDOW_WIDTH / 2, 7 * WINDOW_WIDTH / 8), 
			 Point(WINDOW_WIDTH / 2, WINDOW_WIDTH));
	DrawLine(rookImage, Point(3 * WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8), 
			 Point(3 * WINDOW_WIDTH / 4, WINDOW_WIDTH));

	//3.��ʾ���Ƴ���ͼ��
	imshow(WINDOW_NAME1, atomImage);
	moveWindow(WINDOW_NAME1, 0, 200);
	imshow(WINDOW_NAME2, rookImage);
	moveWindow(WINDOW_NAME2, WINDOW_WIDTH, 200);
	
	waitKey(0);
	return 0;
}