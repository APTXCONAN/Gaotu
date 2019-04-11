#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp> 
#include <opencv2/imgproc/types_c.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>


using namespace cv;
using namespace std;

//int ProcsHelp();
//int ProcsMain(string imagePath);
//
//double FindMax(double *p, int n);
double FindMin(double *p, int n);

int ConvertBGR2HSI(Mat src, Mat dst);
int ConvertHSI2BGR(Mat src, Mat dst);
//int test01();
//int ShowDifference();
int CalcNormalizedHistogram(Mat img, Mat histImg, int histHeight, int *pmax, int *hist, Scalar color);
int FilterProcessing(
	Mat src, Mat dst, Mat filter,
	double ProcessingMethod(Mat filterArea, Mat filter));