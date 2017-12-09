
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

//֡�������  
class FrameProcessor
{
public:
	virtual void process(Mat &input, Mat &ouput) = 0;
};

class FeatureTracker :public FrameProcessor
{
	Mat gray;//��ǰ�Ҷ�ͼ��
	Mat gray_prev;//֮ǰ�Ҷ�ͼ��
				  //����ͼ�����ٵ������� 0->1
	vector<Point2f>points[2];
	//���ٵĵ�ĳ�ʼλ��
	vector<Point2f>initial;
	vector<Point2f>features;//��⵽������
	int max_count;//��Ҫ���ٵ����������Ŀ
	double qlevel;//��������е������ȼ�
	double minDist;//����֮�����С����
	vector<uchar>status;//��⵽��������״̬
	vector<float>err;//���ٹ����еĴ���
public:
	FeatureTracker() :max_count(500), qlevel(0.01), minDist(10.) {}

	void process(Mat &frame, Mat &output)
	{
		//ת��Ϊ�Ҷ�ͼ��
		cvtColor(frame, gray, CV_BGR2GRAY);
		frame.copyTo(output);
		//1.�����Ҫ����µ�������
		if (addNewPoints())
		{
			//���м��
			detectFeaturePoints();
			//��Ӽ�⵽����������ǰ���ٵ�������
			points[0].insert(points[0].end(), features.begin(), features.end());
			initial.insert(initial.end(), features.begin(), features.end());
		}
		//���������еĵ�һ��ͼ��
		if (gray_prev.empty())
		{
			gray.copyTo(gray_prev);
		}
		//2.����������
		calcOpticalFlowPyrLK(
			gray_prev, gray,//��������ͼ
			points[0],//ͼ1�е����������
			points[1],//ͼ2�е����������
			status,//���ٳɹ�
			err);//���ٴ���
				 //2.�������и��ٵĵ����ɸѡ
		int k = 0;
		for (int i = 0; i<points[1].size(); i++)
		{
			//�Ƿ���Ҫ�����õ㣿
			if (acceptTrackedPoint(i))
			{
				//���б���
				initial[k] = initial[i];
				points[1][k++] = points[1][i];
			}
		}
		//ȥ�����ɹ��ĵ�
		points[1].resize(k);
		initial.resize(k);
		//3.������յĸ��ٵ�
		handleTrackedPoints(frame, output);
		//4.��ǰ֡�ĵ��ͼ���Ϊǰһ֡�ĵ��ͼ��
		swap(points[1], points[0]);
		swap(gray_prev, gray);
	}

	//���������
	void detectFeaturePoints()
	{
		//�������
		goodFeaturesToTrack(gray,//ͼ��
			features,//��⵽������
			max_count,//�����������Ŀ
			qlevel,//�����ȼ�
			minDist);//��������֮�����С����
	}

	//�Ƿ���Ҫ����µĵ�
	bool addNewPoints()
	{
		//����������̫��
		return points[0].size() <= 10;
	}

	//������Щ��Ӧ�ø���
	bool acceptTrackedPoint(int i)
	{
		return status[i] &&
			//������ƶ���
			(abs(points[0][i].x - points[1][i].x)) +
			(abs(points[0][i].y - points[1][i].y))>2;
	}

	//����ǰ���ٵĵ�
	void handleTrackedPoints(Mat &frame, Mat &output)
	{
		//�������и��ٵ�
		for (int i = 0; i<points[1].size(); i++)
		{
			//����ֱ�ߺ�Բ
			line(output,
				initial[i],//��ʼλ��
				points[1][i],//��λ��
				Scalar(255, 255, 255));
			circle(output, points[1][i], 3, Scalar(255, 255, 255), -1);
		}
	}
};

class VideoProcessor
{
private:

	VideoCapture caputure;
	//����ļ���  
	string Outputfile;
	int currentIndex;
	int digits;
	string extension;
	FrameProcessor *frameprocessor;
	//ͼ������ָ��  
	void(*process)(Mat &, Mat &);
	bool callIt;
	string WindowNameInput;
	string WindowNameOutput;
	//��ʱ  
	int delay;
	long fnumber;
	//��frameToStopֹͣ  
	long frameToStop;
	//��ͣ��־  
	bool stop;
	//ͼ��������Ϊ������Ƶ��  
	vector<string> images;
	//������  
public:
	VideoProcessor() :callIt(true), delay(0), fnumber(0), stop(false), digits(0), frameToStop(-1) {}


	//����ͼ������  
	void setFrameProcessor(void(*process)(Mat &, Mat &)) {
		frameprocessor = 0;
		this->process = process;
		CallProcess();
	}
	//����Ƶ  
	bool setInput(string filename) {
		fnumber = 0;
		//���Ѵ򿪣��ͷ����´�  
		caputure.release();
		return caputure.open(filename);
	}
	//������ͷ
	//����Ƶ  
	bool setInput(int id) {
		fnumber = 0;
		//���Ѵ򿪣��ͷ����´�  
		caputure.release();
		return caputure.open(id);
	}
	//����������Ƶ���Ŵ���  
	void displayInput(string wn) {
		WindowNameInput = wn;
		namedWindow(WindowNameInput);
	}
	//���������Ƶ���Ŵ���  
	void displayOutput(string wn) {
		WindowNameOutput = wn;
		namedWindow(WindowNameOutput);
	}
	//���ٴ���  
	void dontDisplay() {
		destroyWindow(WindowNameInput);
		destroyWindow(WindowNameOutput);
		WindowNameInput.clear();
		WindowNameOutput.clear();
	}

	//����  
	void run() {
		Mat frame;
		Mat output;
		if (!isOpened())
			return;
		stop = false;
		while (!isStopped()) {
			//��ȡ��һ֡  
			if (!readNextFrame(frame))
				break;
			if (WindowNameInput.length() != 0)
				imshow(WindowNameInput, frame);
			//�����֡  
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
			//������ͣ��������������  
			if (delay >= 0 && waitKey(delay) >= 0)
				waitKey(0);
			//����ָ����ͣ�����˳�  
			if (frameToStop >= 0 && getFrameNumber() == frameToStop)
				stopIt();
		}
	}
	//��ͣ����λ  
	void stopIt() {
		stop = true;
	}
	//��ѯ��ͣ��־λ  
	bool isStopped() {
		return stop;
	}
	//������Ƶ�򿪱�־  
	bool isOpened() {
		return  caputure.isOpened() || !images.empty();
	}
	//������ʱ  
	void setDelay(int d) {
		delay = d;
	}
	//��ȡ��һ֡  
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
	//����ֹͣ֡  
	void stopAtFrameNo(long frame) {
		frameToStop = frame;
	}
	// ��õ�ǰ֡��λ��  
	long getFrameNumber() {
		long fnumber = static_cast<long>(caputure.get((CV_CAP_PROP_POS_FRAMES)));
		return fnumber;
	}

	//��ȡ֡��  
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
	//������Ƶ������ʵ��
	VideoProcessor processor;
	//��������������ʵ��
	FeatureTracker tracker;
	/*---------------- ��Ƶ���� -------------*/
	//����Ƶ�ļ�
	//processor.setInput("..\\..\\1.MP4");
	//����֡����������
	//processor.setFrameProcessor(&tracker);
	//������ʾ����
	//processor.displayOutput("Tracked Features");
	//��ԭʼ֡�ʲ�����Ƶ
	//processor.setDelay(1000. / processor.getFrameRate());
	//��ʼ�������
	//processor.run();
	/*--------------- ����ͷ���� -------------*/
	//������ͷ
	processor.setInput(0);
	//����֡����������
	processor.setFrameProcessor(&tracker);
	//������ʾ����
	processor.displayOutput("Tracked Features");
	//�ӳ�30ms
	processor.setDelay(30);
	//��ʼ�������
	processor.run();
	return 0;
}