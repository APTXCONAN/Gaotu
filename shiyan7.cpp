#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp> 
#include <opencv2/imgproc/types_c.h>
#include <iostream>
#include <stdlib.h>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	//Mat src = imread("D:\\importance2\\gaotu\\gaotushiyan\\picture\\building.jpg");
	//Mat src = imread("D:\\importance2\\gaotu\\gaotushiyan\\picture\\characters.tif");
	Mat src = imread("D:\\importance2\\gaotu\\gaotushiyan\\picture\\earth.jpg");
	/* the first command line parameter must be image file name */
	if (src.empty())
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	Mat dst = src.clone();
	int delta = 1;
	int angle = 0;
	int opt = 1;     // 1： 旋转加缩放 
								  // 0: 仅仅旋转 
	double factor;
	namedWindow("src", WINDOW_AUTOSIZE);
	imshow("src", src);

	for (;;)
	{
		//float m[6];
		//// matrix m looks like: 
		//// 
		//// [ m0 m1 m2 ] ===> [ a11 a12     b1 ] 
		//// [ m3 m4 m5 ] ===> [ a21 a22     b2 ] 
		////  
		//int w = src.cols;
		//int h = src.rows;
		//if (opt) // 旋转加缩放 
		//	factor = (cos(angle*CV_PI / 180.) + 1.05) * 2;
		//else // 仅仅旋转 
		//	factor = 1;
		//m[0] = (float)(factor*cos(-angle * 2 * CV_PI / 180.));
		//m[1] = (float)(factor*sin(-angle * 2 * CV_PI / 180.));
		//m[3] = -m[1];
		//m[4] = m[0];
		//// 将旋转中心移至图像中间 
		//m[2] = w * 0.5f;
		//m[5] = h * 0.5f;
		//Mat M = cv::Mat(2, 3, CV_32F, m);
		///*Point2f center(src.cols / 2, src.rows / 2);
		//Mat M = getRotationMatrix2D(center, angle, factor);*/

		////cvgetquadranglesubpix(src, dst, &m);//提取像素四边形，使用子像素精度 
		//warpAffine(src, dst, M, Size(src.cols, src.rows), INTER_LINEAR);

		if (opt) // 旋转加缩放 
			factor = (cos(angle*CV_PI / 180.) + 1.05);
		else // 仅仅旋转 
			factor = 1;
		Point2f center(src.cols / 2, src.rows / 2);//旋转中心  
		//double angle = 45;//逆时针旋转45度  
		//double scale = factor;//缩放比例  
		Mat M2 = getRotationMatrix2D(center, angle, factor);//计算旋转加缩放的变换矩阵  
		warpAffine(src, dst, M2, Size(src.cols, src.rows));//仿射变换
		
		

		namedWindow("dst", 1);
		imshow("dst", dst);
		/*if (waitKey(5) == 27)
			break;*/
		angle = (int)(angle + delta) % 360;
		if (waitKey(5) == 27) {
			destroyWindow("dst");
			destroyWindow("src");
			break;
		}
	} // for-loop 

	return 0;
}
