#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp> 
#include <opencv2/imgproc/types_c.h>
#include <iostream>
#include <stdlib.h>

using namespace cv;
using namespace std;

#define M_SAVEFLAG 0

int Exp01Help();

int ShowImg();
int Binarization();
int LogTrans();
int GamaTrans();
int ComplementaryColorTrans();
void binaryfb(int, void *);
void gamafb(int, void*);
void logfb(int, void*);

int Exp01Help()
{
	cout <<
		"1 : 显示原始图像和灰度图像\n" <<
		"2 : 灰度图像二值化\n" <<
		"3 : 灰度图像对数变换\n" <<
		"4 : 灰度图像伽马变换\n" <<
		"5 : 彩色图像补色变换\n" << endl;
	return 0;
}

Mat image;
Mat gray;
Mat hsv;

int threshold_val = 128;
int log_linear = 255;
int max_log_linear = 255;
double cLog; 
double cGama;
double gama=1, gama_pre;
int gama_linear = 100;
int max_gama_linear = 200;

int main(int argc, char** argv)
{
	image = imread("D:\\importance2\\gaotu\\gaotushiyan\\picture\\lena_512.tif");
	//image = imread("D:\\importance2\\gaotu\\gaotushiyan\\picture\\conan.png");
	if (image.empty())
	{
		cout << "Could not open or find the image" << std::endl;
		return 13;
	}
	//gray = imread(imagePath, IMREAD_GRAYSCALE);
	cvtColor(image, gray, CV_BGR2GRAY);
	cvtColor(image, hsv, CV_BGR2HSV);
	//pimage = cvLoadImage("test.jpg");
	

	Exp01Help();
	char choice;
	while (1)
	{
		cout << "请选择要运行的程序，按h帮助，按q退出：";
		cin >> choice;
		cin.ignore(CHAR_MAX, '\n');
		if (choice == 'q')
		{
			exit(0);
		}
		else
		{
			switch (choice)
			{
			case '1':
				ShowImg();
				break;
			case '2':
				Binarization();
				break;
			case '3':
				LogTrans();
				break;
			case '4':
				GamaTrans();
				break;
			case '5':
				ComplementaryColorTrans();
				break;
			case 'h':
				Exp01Help();
				break;
			default:
				cout << "无效的输入" << endl;
				break;
			}
		}
	}
	return 0;
}

int ShowImg()
{
	namedWindow("Original - 原始图像", WINDOW_AUTOSIZE);//WINDOW_AUTOSIZE表示窗口的大小会根据载入图像的大小进行调整
	imshow("Original - 原始图像", image);
	namedWindow("Gray - 灰度图像", WINDOW_AUTOSIZE);
	imshow("Gray - 灰度图像", gray);

	waitKey(0);
	destroyAllWindows();
	return 0;
}

int Binarization()
{
	namedWindow("Gray - 灰度图像", WINDOW_AUTOSIZE);
	imshow("Gray - 灰度图像", gray);
	namedWindow("Binarization", WINDOW_AUTOSIZE);

	//trackbarname：滑动空间的名称；
	//winname：滑动空间用于依附的图像窗口的名称；
	//value：初始化阈值；
	//count：滑动控件的刻度范围
	createTrackbar("Threshold", "Binarization", &threshold_val, 255, binaryfb);
	binaryfb(0, 0);
	waitKey(0);
	destroyAllWindows();
	return 0;
}
void binaryfb(int, void *) {
	Mat binaImg = Mat::zeros(gray.size(), gray.type());
	for (int y = 0; y < gray.rows; y++)
	{
		for (int x = 0; x < gray.cols; x++)
		{
			//saturate_cast<uchar>();
			binaImg.at<uchar>(y, x) = gray.at<uchar>(y, x) >= threshold_val ? 255 : 0;
		}
	}
	imshow("Binarization", binaImg);
}



int LogTrans()
{

	namedWindow("Gray - 灰度图像", WINDOW_AUTOSIZE);
	imshow("Gray - 灰度图像", gray);
	namedWindow("LogTrans", WINDOW_AUTOSIZE);
	createTrackbar("系数调节", "LogTrans", &log_linear, max_log_linear, logfb);
	logfb(0, 0);
	waitKey(0);
	destroyAllWindows();

	return 0;
}
void logfb(int, void*) {
	Mat logImg = Mat::zeros(gray.size(), gray.type());
	cLog= log_linear/ (log(1 + log_linear));
	for (int y = 0; y < gray.rows; y++)
	{
		for (int x = 0; x < gray.cols; x++)
		{
			logImg.at<uchar>(y, x) = saturate_cast<uchar>(cLog*log(1 + gray.at<uchar>(y, x)));
		}
	}
	imshow("LogTrans", logImg);
}


int GamaTrans()
{
	namedWindow("Gray - 灰度图像", WINDOW_AUTOSIZE);
	imshow("Gray - 灰度图像", gray);
	namedWindow("GamaTrans", WINDOW_AUTOSIZE);

	createTrackbar("指数调节", "GamaTrans", &gama_linear, max_gama_linear,gamafb);
	gamafb(0, 0);
	waitKey(0);
	destroyAllWindows();
	return 0;
}
void gamafb(int, void*) {
	Mat gamaImg = Mat::zeros(gray.size(), gray.type());
	gama_pre = gama;
	gama = (double)pow(10, (double)((double)(gama_linear - max_gama_linear / 2) / (double)(max_gama_linear / 2)));
	cGama = (double)255 / (pow(255, (double)gama));
	/*if (fabs(gama - gama_pre) > 0.000001)
	{
		cout << "此时指数为：" << gama << endl;
	}
*/
	for (int y = 0; y < gray.rows; y++)
	{
		for (int x = 0; x < gray.cols; x++)
		{
			gamaImg.at<uchar>(y, x) = saturate_cast<uchar>(cGama*pow(gray.at<uchar>(y, x), (double)gama));
		}
	}
	imshow("GamaTrans", gamaImg);
}

int ComplementaryColorTrans()
{
	Mat complementaryColorImg = Mat::zeros(image.size(), image.type());
	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			complementaryColorImg.at<Vec3b>(y, x)[0] = 255 - image.at<Vec3b>(y, x)[0];
			complementaryColorImg.at<Vec3b>(y, x)[1] = 255 - image.at<Vec3b>(y, x)[1];
			complementaryColorImg.at<Vec3b>(y, x)[2] = 255 - image.at<Vec3b>(y, x)[2];
		}
	}
	namedWindow("Original - 原始图像", WINDOW_AUTOSIZE);
	imshow("Original - 原始图像", image);
	namedWindow("Complementary Color Trans", WINDOW_AUTOSIZE);
	imshow("Complementary Color Trans", complementaryColorImg);
	waitKey(0);
	destroyAllWindows();

	return 0;
}