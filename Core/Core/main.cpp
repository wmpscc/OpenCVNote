#include<core.hpp>
#include<highgui.hpp>
#include<iostream>
using namespace std;
using namespace cv;

void colorReduce1(Mat& inputImage, Mat& outputImage, int div);//��ָ��������أ����ַ�����죩
void colorReduce2(Mat& inputimage, Mat& outputImage, int div);//�õ�������������
void colorReduce3(Mat& inputImage, Mat& outputImage, int div);//��̬��ַ����

int main()
{
	//1.����ԭʼͼ����ʾ
	Mat srcImage = imread("..//..//3.jpg");
	imshow("ԭʼͼ��", srcImage);

	//2.��ԭʼͼ�Ĳ������������Ч��ͼ
	Mat dstImage;
	dstImage.create(srcImage.rows, srcImage.cols, srcImage.type());	//Ч��ͼ�Ĵ�С��������ԭʼͼƬ��ͬ

	//3.��¼��ʼʱ��
	double time0 = static_cast<double>(getTickCount());

	//4.������ɫ�ռ���������
	colorReduce2(srcImage, dstImage, 32);

	//5.��������ʱ�䲢���
	time0 = ((double)getTickCount() - time0) / getTickFrequency();
	cout << "�˷�������ʱ��Ϊ��" << time0 << "��" << endl;	//�������ʱ��

	//6.��ʾЧ��ͼ
	imshow("Ч��ͼ", dstImage);
	waitKey(0);
	return 0;
}

//��ָ��������أ����ַ�����죩
void colorReduce1(Mat& inputImage, Mat& outputImage, int div)
{
	//����׼��
	outputImage = inputImage.clone();	//����ʵ�ε���ʱ����
	int rowNumber = outputImage.rows;	//����
	int colNumber = outputImage.cols * outputImage.channels();	//����xͨ����=ÿ��Ԫ�صĸ���

	//˫��ѭ�����������е�����ֵ
	for (int i = 0; i < rowNumber; i++)	//��ѭ��
	{
		uchar* data = outputImage.ptr<uchar>(i);	//��ȡ��i�е��׵�ַ
		for (int j = 0; j < colNumber; j++)	//��ѭ��
		{
			//-----��ʼ����ÿ������------
			data[j] = data[j] / div* div + div / 2;
			//-----�������-----
		}	//�д������
	}
}

//�õ�������������
void colorReduce2(Mat& inputimage, Mat& outputImage, int div)
{
	//����׼��
	outputImage = inputimage.clone();	//����ʵ�ε���ʱ����
	//��ȡ������
	Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>();	//��ʼλ�õĵ�����
	Mat_<Vec3b>::iterator itend = outputImage.end<Vec3b>();	//��ֹλ�õĵ�����

	//��ȡ��ɫͼ������
	for (; it != itend; ++it)
	{
		//----��ʼ����ÿ������----
		(*it)[0] = (*it)[0] / div * div + div / 2;
		(*it)[1] = (*it)[1] / div * div + div / 2;
		(*it)[2] = (*it)[2] / div * div + div / 2;

		//----�������----
	}
}


//��̬��ַ����
void colorReduce3(Mat& inputImage, Mat& outputImage, int div)
{
	//����׼��
	outputImage = inputImage.clone(); //����ʵ�ε���ʱ����
	int rowNumber = outputImage.rows; //����
	int colNumber = outputImage.cols; //����

	//��ȡ��ɫͼ������
	for (int i = 0; i < rowNumber; i++)
	{
		for (int j = 0; j < colNumber; j++)
		{
			//----��ʼ����ÿ������----
			outputImage.at<Vec3b>(i, j)[0] = outputImage.at<Vec3b>(i, j)[0] / div*div + div / 2; //��ɫͨ��
			outputImage.at<Vec3b>(i, j)[1] = outputImage.at<Vec3b>(i, j)[1] / div*div + div / 2; //��ɫͨ��
			outputImage.at<Vec3b>(i, j)[2] = outputImage.at<Vec3b>(i, j)[2] / div*div + div / 2; //��ɫͨ��
		}
	}
}

