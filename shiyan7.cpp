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
	int opt = 1;     // 1�� ��ת������ 
								  // 0: ������ת 
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
		//if (opt) // ��ת������ 
		//	factor = (cos(angle*CV_PI / 180.) + 1.05) * 2;
		//else // ������ת 
		//	factor = 1;
		//m[0] = (float)(factor*cos(-angle * 2 * CV_PI / 180.));
		//m[1] = (float)(factor*sin(-angle * 2 * CV_PI / 180.));
		//m[3] = -m[1];
		//m[4] = m[0];
		//// ����ת��������ͼ���м� 
		//m[2] = w * 0.5f;
		//m[5] = h * 0.5f;
		//Mat M = cv::Mat(2, 3, CV_32F, m);
		///*Point2f center(src.cols / 2, src.rows / 2);
		//Mat M = getRotationMatrix2D(center, angle, factor);*/

		////cvgetquadranglesubpix(src, dst, &m);//��ȡ�����ı��Σ�ʹ�������ؾ��� 
		//warpAffine(src, dst, M, Size(src.cols, src.rows), INTER_LINEAR);

		if (opt) // ��ת������ 
			factor = (cos(angle*CV_PI / 180.) + 1.05);
		else // ������ת 
			factor = 1;
		Point2f center(src.cols / 2, src.rows / 2);//��ת����  
		//double angle = 45;//��ʱ����ת45��  
		//double scale = factor;//���ű���  
		Mat M2 = getRotationMatrix2D(center, angle, factor);//������ת�����ŵı任����  
		warpAffine(src, dst, M2, Size(src.cols, src.rows));//����任
		
		

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
