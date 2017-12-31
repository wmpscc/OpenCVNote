#include<core.hpp>
#include<highgui.hpp>
#include<iostream>
using namespace std;
using namespace cv;

void colorReduce1(Mat& inputImage, Mat& outputImage, int div);//用指针访问像素（这种方法最快）
void colorReduce2(Mat& inputimage, Mat& outputImage, int div);//用迭代器操作像素
void colorReduce3(Mat& inputImage, Mat& outputImage, int div);//动态地址计算

int main()
{
	//1.创建原始图并显示
	Mat srcImage = imread("..//..//3.jpg");
	imshow("原始图像", srcImage);

	//2.按原始图的参数规格来创建效果图
	Mat dstImage;
	dstImage.create(srcImage.rows, srcImage.cols, srcImage.type());	//效果图的大小、类型与原始图片相同

	//3.记录起始时间
	double time0 = static_cast<double>(getTickCount());

	//4.调用颜色空间缩减函数
	colorReduce2(srcImage, dstImage, 32);

	//5.计算运行时间并输出
	time0 = ((double)getTickCount() - time0) / getTickFrequency();
	cout << "此方法运行时间为：" << time0 << "秒" << endl;	//输出运行时间

	//6.显示效果图
	imshow("效果图", dstImage);
	waitKey(0);
	return 0;
}

//用指针访问像素（这种方法最快）
void colorReduce1(Mat& inputImage, Mat& outputImage, int div)
{
	//参数准备
	outputImage = inputImage.clone();	//复制实参到临时变量
	int rowNumber = outputImage.rows;	//行数
	int colNumber = outputImage.cols * outputImage.channels();	//列数x通道数=每个元素的个数

	//双重循环，遍历所有的像素值
	for (int i = 0; i < rowNumber; i++)	//行循环
	{
		uchar* data = outputImage.ptr<uchar>(i);	//获取第i行的首地址
		for (int j = 0; j < colNumber; j++)	//列循环
		{
			//-----开始处理每个像素------
			data[j] = data[j] / div* div + div / 2;
			//-----处理结束-----
		}	//行处理结束
	}
}

//用迭代器操作像素
void colorReduce2(Mat& inputimage, Mat& outputImage, int div)
{
	//参数准备
	outputImage = inputimage.clone();	//复制实参到临时变量
	//获取迭代器
	Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>();	//初始位置的迭代器
	Mat_<Vec3b>::iterator itend = outputImage.end<Vec3b>();	//终止位置的迭代器

	//存取彩色图像像素
	for (; it != itend; ++it)
	{
		//----开始处理每个像素----
		(*it)[0] = (*it)[0] / div * div + div / 2;
		(*it)[1] = (*it)[1] / div * div + div / 2;
		(*it)[2] = (*it)[2] / div * div + div / 2;

		//----处理结束----
	}
}


//动态地址计算
void colorReduce3(Mat& inputImage, Mat& outputImage, int div)
{
	//参数准备
	outputImage = inputImage.clone(); //复制实参到临时变量
	int rowNumber = outputImage.rows; //行数
	int colNumber = outputImage.cols; //列数

	//存取彩色图像像素
	for (int i = 0; i < rowNumber; i++)
	{
		for (int j = 0; j < colNumber; j++)
		{
			//----开始处理每个像素----
			outputImage.at<Vec3b>(i, j)[0] = outputImage.at<Vec3b>(i, j)[0] / div*div + div / 2; //蓝色通道
			outputImage.at<Vec3b>(i, j)[1] = outputImage.at<Vec3b>(i, j)[1] / div*div + div / 2; //绿色通道
			outputImage.at<Vec3b>(i, j)[2] = outputImage.at<Vec3b>(i, j)[2] / div*div + div / 2; //红色通道
		}
	}
}

