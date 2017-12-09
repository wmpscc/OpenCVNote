
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

//帧处理基类  
class FrameProcessor
{
public:
	virtual void process(Mat &input, Mat &ouput) = 0;
};

class FeatureTracker :public FrameProcessor
{
	Mat gray;//当前灰度图像
	Mat gray_prev;//之前灰度图像
				  //两幅图像间跟踪的特征点 0->1
	vector<Point2f>points[2];
	//跟踪的点的初始位置
	vector<Point2f>initial;
	vector<Point2f>features;//检测到的特征
	int max_count;//需要跟踪的最大特征数目
	double qlevel;//特征检测中的质量等级
	double minDist;//两点之间的最小距离
	vector<uchar>status;//检测到的特征的状态
	vector<float>err;//跟踪过程中的错误
public:
	FeatureTracker() :max_count(500), qlevel(0.01), minDist(10.) {}

	void process(Mat &frame, Mat &output)
	{
		//转换为灰度图像
		cvtColor(frame, gray, CV_BGR2GRAY);
		frame.copyTo(output);
		//1.如果需要添加新的特征点
		if (addNewPoints())
		{
			//进行检测
			detectFeaturePoints();
			//添加检测到的特征到当前跟踪的特征中
			points[0].insert(points[0].end(), features.begin(), features.end());
			initial.insert(initial.end(), features.begin(), features.end());
		}
		//对于序列中的第一幅图像
		if (gray_prev.empty())
		{
			gray.copyTo(gray_prev);
		}
		//2.跟踪特征点
		calcOpticalFlowPyrLK(
			gray_prev, gray,//两幅连续图
			points[0],//图1中的输入点坐标
			points[1],//图2中的输出点坐标
			status,//跟踪成果
			err);//跟踪错误
				 //2.遍历所有跟踪的点进行筛选
		int k = 0;
		for (int i = 0; i<points[1].size(); i++)
		{
			//是否需要保留该点？
			if (acceptTrackedPoint(i))
			{
				//进行保留
				initial[k] = initial[i];
				points[1][k++] = points[1][i];
			}
		}
		//去除不成功的点
		points[1].resize(k);
		initial.resize(k);
		//3.处理接收的跟踪点
		handleTrackedPoints(frame, output);
		//4.当前帧的点和图像变为前一帧的点和图像
		swap(points[1], points[0]);
		swap(gray_prev, gray);
	}

	//检测特征点
	void detectFeaturePoints()
	{
		//检测特征
		goodFeaturesToTrack(gray,//图像
			features,//检测到的特征
			max_count,//特征的最大数目
			qlevel,//质量等级
			minDist);//两个特征之间的最小距离
	}

	//是否需要添加新的点
	bool addNewPoints()
	{
		//如果点的数量太少
		return points[0].size() <= 10;
	}

	//决定哪些点应该跟踪
	bool acceptTrackedPoint(int i)
	{
		return status[i] &&
			//如果它移动了
			(abs(points[0][i].x - points[1][i].x)) +
			(abs(points[0][i].y - points[1][i].y))>2;
	}

	//处理当前跟踪的点
	void handleTrackedPoints(Mat &frame, Mat &output)
	{
		//遍历所有跟踪点
		for (int i = 0; i<points[1].size(); i++)
		{
			//绘制直线和圆
			line(output,
				initial[i],//初始位置
				points[1][i],//新位置
				Scalar(255, 255, 255));
			circle(output, points[1][i], 3, Scalar(255, 255, 255), -1);
		}
	}
};

class VideoProcessor
{
private:

	VideoCapture caputure;
	//输出文件名  
	string Outputfile;
	int currentIndex;
	int digits;
	string extension;
	FrameProcessor *frameprocessor;
	//图像处理函数指针  
	void(*process)(Mat &, Mat &);
	bool callIt;
	string WindowNameInput;
	string WindowNameOutput;
	//延时  
	int delay;
	long fnumber;
	//第frameToStop停止  
	long frameToStop;
	//暂停标志  
	bool stop;
	//图像序列作为输入视频流  
	vector<string> images;
	//迭代器  
public:
	VideoProcessor() :callIt(true), delay(0), fnumber(0), stop(false), digits(0), frameToStop(-1) {}


	//设置图像处理函数  
	void setFrameProcessor(void(*process)(Mat &, Mat &)) {
		frameprocessor = 0;
		this->process = process;
		CallProcess();
	}
	//打开视频  
	bool setInput(string filename) {
		fnumber = 0;
		//若已打开，释放重新打开  
		caputure.release();
		return caputure.open(filename);
	}
	//打开摄像头
	//打开视频  
	bool setInput(int id) {
		fnumber = 0;
		//若已打开，释放重新打开  
		caputure.release();
		return caputure.open(id);
	}
	//设置输入视频播放窗口  
	void displayInput(string wn) {
		WindowNameInput = wn;
		namedWindow(WindowNameInput);
	}
	//设置输出视频播放窗口  
	void displayOutput(string wn) {
		WindowNameOutput = wn;
		namedWindow(WindowNameOutput);
	}
	//销毁窗口  
	void dontDisplay() {
		destroyWindow(WindowNameInput);
		destroyWindow(WindowNameOutput);
		WindowNameInput.clear();
		WindowNameOutput.clear();
	}

	//启动  
	void run() {
		Mat frame;
		Mat output;
		if (!isOpened())
			return;
		stop = false;
		while (!isStopped()) {
			//读取下一帧  
			if (!readNextFrame(frame))
				break;
			if (WindowNameInput.length() != 0)
				imshow(WindowNameInput, frame);
			//处理该帧  
			if (callIt) {
				if (process)
					process(frame, output);
				else if (frameprocessor)
					frameprocessor->process(frame, output);
			}
			else {
				output = frame;
			}

			if (WindowNameOutput.length() != 0)
				imshow(WindowNameOutput, output);
			//按键暂停，继续按键继续  
			if (delay >= 0 && waitKey(delay) >= 0)
				waitKey(0);
			//到达指定暂停键，退出  
			if (frameToStop >= 0 && getFrameNumber() == frameToStop)
				stopIt();
		}
	}
	//暂停键置位  
	void stopIt() {
		stop = true;
	}
	//查询暂停标志位  
	bool isStopped() {
		return stop;
	}
	//返回视频打开标志  
	bool isOpened() {
		return  caputure.isOpened() || !images.empty();
	}
	//设置延时  
	void setDelay(int d) {
		delay = d;
	}
	//读取下一帧  
	bool readNextFrame(Mat &frame) {
		if (images.size() == 0)
			return caputure.read(frame);
		else {
			if (itImg != images.end()) {
				frame = imread(*itImg);
				itImg++;
				return frame.data ? 1 : 0;
			}
			else
				return false;
		}
	}

	void CallProcess() {
		callIt = true;
	}
	void  dontCallProcess() {
		callIt = false;
	}
	//设置停止帧  
	void stopAtFrameNo(long frame) {
		frameToStop = frame;
	}
	// 获得当前帧的位置  
	long getFrameNumber() {
		long fnumber = static_cast<long>(caputure.get((CV_CAP_PROP_POS_FRAMES)));
		return fnumber;
	}

	//获取帧率  
	double getFrameRate() {
		return caputure.get(CV_CAP_PROP_FPS);
	}
	vector<string>::const_iterator itImg;
	bool setInput(const vector<string> &imgs) {
		fnumber = 0;
		caputure.release();
		images = imgs;
		itImg = images.begin();
		return true;
	}

	void  setFrameProcessor(FrameProcessor *frameprocessor) {
		process = 0;
		this->frameprocessor = frameprocessor;
		CallProcess();
	}
};


int main()
{
	//创建视频处理器实例
	VideoProcessor processor;
	//创建特征跟踪器实例
	FeatureTracker tracker;
	/*---------------- 视频输入 -------------*/
	//打开视频文件
	//processor.setInput("..\\..\\1.MP4");
	//设置帧处理器对象
	//processor.setFrameProcessor(&tracker);
	//声明显示窗口
	//processor.displayOutput("Tracked Features");
	//以原始帧率播放视频
	//processor.setDelay(1000. / processor.getFrameRate());
	//开始处理过程
	//processor.run();
	/*--------------- 摄像头输入 -------------*/
	//打开摄像头
	processor.setInput(0);
	//设置帧处理器对象
	processor.setFrameProcessor(&tracker);
	//声明显示窗口
	processor.displayOutput("Tracked Features");
	//延迟30ms
	processor.setDelay(30);
	//开始处理过程
	processor.run();
	return 0;
}