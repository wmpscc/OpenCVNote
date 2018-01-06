#include<iostream>
#include<highgui.hpp>
#include<core.hpp>
using namespace cv;
using namespace std;

bool MultiChannelBlending();

int ____main()
{
	system("color 9F");
	if (MultiChannelBlending())
	{
		cout << endl << "\n���гɹ����ó�����Ҫ��ͼ��";
	}
	waitKey(0);
	return 0;
}

bool MultiChannelBlending()
{
	//0.������ر���
	Mat srcImage;
	Mat logoImage;
	vector<Mat> channels;
	Mat imageBlueChannel;

	//��ͨ�������ɫͨ������
	//1.����ͼƬ
	logoImage = imread("..//..//1.jpg", 0);
	srcImage = imread("..//..//3.jpg");
	if (!logoImage.data)
	{
		printf("��ȡlogoImage����\n");
		return false;
	}
	if (!srcImage.data)
	{
		printf("��ȡsrcImage����\n");
		return false;
	}
	imshow("srcImage��ԭͼ��", srcImage);
	//2.��һ��3ͨ��ͼ��ת����3����ͨ��ͼ��
	split(srcImage, channels);	//����ɫ��ͨ��
	
	//3.��ԭͼ����ɫͨ�����÷��ظ�imageBlueChannel��ע�������ã��൱�����ߵȼۣ��޸�һ����һ�����ű�
	imageBlueChannel = channels.at(0);
	//4.��ԭͼ����ɫͨ����(500,250)���괦���·���һ�������logoͼ���м�Ȩ���������õ��Ļ�Ͻ���浽imageBlueChannel��
	addWeighted(imageBlueChannel(Rect(100, 100, logoImage.cols, logoImage.rows)), 1.0, logoImage, 0.5, 0, imageBlueChannel(Rect(100, 100, logoImage.cols, logoImage.rows)));
	//5.��������ͨ�����ºϲ���һ����ͨ��
	merge(channels, srcImage);
	//6.��ʾЧ��ͼ
	namedWindow("<1>��Ϸԭ��+logo��ɫͨ��");
	imshow("<1>��Ϸԭ��+logo��ɫͨ��", srcImage);


	//��ͨ�������ɫͨ������
	//0.������ر���
	Mat imageGreenChannel;

	//1.����ͼƬ
	logoImage = imread("..//..//1.jpg", 0);
	srcImage = imread("..//..//3.jpg");
	if (!logoImage.data)
	{
		printf("��ȡlogoImage����\n");
		return false;
	}
	if (!srcImage.data)
	{
		printf("��ȡsrcImage����\n");
		return false;
	}
	//2.��һ��3ͨ��ͼ��ת����3����ͨ��ͼ��
	split(srcImage, channels);	//����ɫ��ͨ��

								//3.��ԭͼ����ɫͨ�����÷��ظ�imageGreenChannel��ע�������ã��൱�����ߵȼۣ��޸�һ����һ�����ű�
	imageGreenChannel = channels.at(1);
	//4.��ԭͼ����ɫͨ����(500,250)���괦���·���һ�������logoͼ���м�Ȩ���������õ��Ļ�Ͻ���浽imageGreenChannel��
	addWeighted(imageGreenChannel(Rect(100, 100, logoImage.cols, logoImage.rows)), 1.0, logoImage, 0.5, 0, imageGreenChannel(Rect(100, 100, logoImage.cols, logoImage.rows)));
	//5.��������ͨ�����ºϲ���һ����ͨ��
	merge(channels, srcImage);
	//6.��ʾЧ��ͼ
	namedWindow("<2>��Ϸԭ��+logo��ɫͨ��");
	imshow("<2>��Ϸԭ��+logo��ɫͨ��", srcImage);


	//��ͨ����Ϻ�ɫͨ������
	//0.������ر���
	Mat imageRedChannel;

	//1.����ͼƬ
	logoImage = imread("..//..//1.jpg", 0);
	srcImage = imread("..//..//3.jpg");
	if (!logoImage.data)
	{
		printf("��ȡlogoImage����\n");
		return false;
	}
	if (!srcImage.data)
	{
		printf("��ȡsrcImage����\n");
		return false;
	}
	//2.��һ��3ͨ��ͼ��ת����3����ͨ��ͼ��
	split(srcImage, channels);	//����ɫ��ͨ��

								//3.��ԭͼ����ɫͨ�����÷��ظ�imageRedChannel��ע�������ã��൱�����ߵȼۣ��޸�һ����һ�����ű�
	imageRedChannel = channels.at(2);
	//4.��ԭͼ����ɫͨ����(500,250)���괦���·���һ�������logoͼ���м�Ȩ���������õ��Ļ�Ͻ���浽imageRedChannel��
	addWeighted(imageRedChannel(Rect(100, 100, logoImage.cols, logoImage.rows)), 1.0, logoImage, 0.5, 0, imageRedChannel(Rect(100, 100, logoImage.cols, logoImage.rows)));
	//5.��������ͨ�����ºϲ���һ����ͨ��
	merge(channels, srcImage);
	//6.��ʾЧ��ͼ
	namedWindow("<3>��Ϸԭ��+logo��ɫͨ��");
	imshow("<3>��Ϸԭ��+logo��ɫͨ��", srcImage);

	return true;

}