#include<core.hpp>
#include<highgui.hpp>
#include<opencv.hpp>
using namespace cv;
#define WINDOW_NAME "�����򴰿ڡ�"

//ȫ�ֺ���������
void on_MouseHandle(int event, int x, int y, int flags, void* param);
void DrawRectangle(cv::Mat& img, cv::Rect box);

//ȫ�ֱ�������
Rect g_rectangle;
bool g_bDrawingBox = false;
RNG g_rng(12345);


int main()
{
	//1.׼������
	g_rectangle = Rect(-1, -1, 0, 0);
	Mat srcImage(600, 800, CV_8UC3), tempImage;
	srcImage.copyTo(tempImage);
	g_rectangle = Rect(-1, -1, 0, 0);
	srcImage = Scalar::all(0);

	//2.�����������ص�����
	namedWindow(WINDOW_NAME);
	setMouseCallback(WINDOW_NAME, on_MouseHandle, (void*)&srcImage);

	//3.������ѭ���������л��Ƶı�ʶΪ��ʱ�����л���
	while (true)
	{
		srcImage.copyTo(tempImage);
		if (g_bDrawingBox)
			DrawRectangle(tempImage, g_rectangle);//�����л��Ƶı�ʶ��Ϊ�棬����л���
		imshow(WINDOW_NAME, tempImage);
		if (waitKey(10) == 27)break;//����ESC���������˳�
	}


	return 0;
}

void on_MouseHandle(int event, int x, int y, int flags, void* param)
{
	//paramΪ����Ĳ���
	Mat& image = *(cv::Mat*)param;
	switch (event)
	{
		//����ƶ���Ϣ
	case CV_EVENT_MOUSEMOVE:
	{
		if (g_bDrawingBox)//����Ƿ���л��Ƶı�ʶ��Ϊ�棬���¼�³��Ϳ�RECT�ͱ�����
		{
			g_rectangle.width = x - g_rectangle.x;
			g_rectangle.height = y - g_rectangle.y;
		}
	}
	break;
	
	//���������Ϣ
	case CV_EVENT_LBUTTONDOWN:
	{
		g_bDrawingBox = true;
		g_rectangle = Rect(x, y, 0, 0);//��¼��ʼ��
	}
	break;

	//���̧����Ϣ
	case CV_EVENT_LBUTTONUP:
	{
		g_bDrawingBox = false;//�ñ�ʶ��Ϊfalse
		//�Կ�͸�С��0�Ĵ���
		if (g_rectangle.width < 0)
		{
			g_rectangle.x += g_rectangle.width;
			g_rectangle.width *= -1;
		}
		if (g_rectangle.height < 0)
		{
			g_rectangle.y += g_rectangle.height;
			g_rectangle.height *= -1;
		}
		//���ú������л���
		DrawRectangle(image, g_rectangle);

	}
	}
}

void DrawRectangle(cv::Mat& img, cv::Rect box)
{
	rectangle(img, box.tl(), box.br(), Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)));//�����ɫ
}