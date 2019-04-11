#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp> 
#include <opencv2/imgproc/types_c.h>
#include <iostream>
#include <stdlib.h>

using namespace std;
using namespace cv;

void on_GoodFeaturesToTrack(int, void*);

Mat srcImage, grayImage, result;
int cornerCount = 30;
int max_corners = 500;

int main(int argc, char** argv)
{
	//Load the image to be processed 
	srcImage = imread("D:\\importance2\\gaotu\\gaotushiyan\\picture\\building.jpg");
	if (srcImage.empty())
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	result = srcImage.clone();
	cvtColor(srcImage, grayImage, CV_BGR2GRAY);

	//vector<Point2f> corners;//Point2f类型的向量：存储每个角点的坐标

	namedWindow("result", WINDOW_AUTOSIZE); 
	createTrackbar("最大角点数", "result", &cornerCount, max_corners, on_GoodFeaturesToTrack);
	//输入图，向量，最大角点数量，角点的最小特征值，角点间最小距离，掩码（Mat（）表示掩码为空），blocksize，是否使用Harris角点检测，权重系数
	//block size 3
	// not use harris
	/*goodFeaturesToTrack(grayImage,corners,
		500,0.01,5.0,Mat(),
		3,false,0.04);

	cout << "角点数量" << corners.size() << endl;*/

	// draw circles at each corner location in the gray image and 
	//print out a list the corners  
	/*for (int i = 0; i < corners.size(); i++)
		circle(result, corners[i], 5, Scalar(0, 0, 255), 2, 8);

	imshow("result", result);*/
	on_GoodFeaturesToTrack(0,0);
	waitKey(0); 
	destroyWindow("result");
	return 0;
}

void on_GoodFeaturesToTrack(int, void*)
{
	//【1】对变量小于等于1时的处理
	if (cornerCount <= 1) { cornerCount = 1; }

	//【2】Shi-Tomasi算法（goodFeaturesToTrack函数）的参数准备
	vector<Point2f> corners;
	double qualityLevel = 0.05;//角点检测可接受的最小特征值
	double minDistance = 10;//角点之间的最小距离
	int blockSize = 3;//计算导数自相关矩阵时指定的邻域范围
	double k = 0.4;//权重系数
	result = srcImage.clone();    //复制源图像到一个临时变量中，作为感兴趣区域

	//【3】进行Shi-Tomasi角点检测
	goodFeaturesToTrack(grayImage,//输入图像
		corners,//检测到的角点的输出向量
		cornerCount,//角点的最大数量
		qualityLevel,//角点检测可接受的最小特征值
		minDistance,//角点之间的最小距离
		Mat(),//感兴趣区域
		blockSize,//计算导数自相关矩阵时指定的邻域范围
		false,//不使用Harris角点检测
		k);//权重系数


	//【4】输出文字信息
	cout << "\t>此次检测到的角点数量为：" << corners.size() << endl;

	//【5】绘制检测到的角点
	int r = 4;
	for (int i = 0; i < corners.size(); i++)
	{
		circle(result, corners[i], r, 
			Scalar(0,0,255), 
			2, 8, 0);
	}

	//【6】显示（更新）窗口
	imshow("result", result);
}
