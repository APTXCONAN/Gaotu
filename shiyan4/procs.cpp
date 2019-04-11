#include "procs.h"

#define M_PI 3.14159265358979323846


Mat image;
//IplImage *pimage;
Mat gray;
//IplImage *pgray;
Mat hsv;

double FindMin(double *p, int n)
{
	double min = p[0];
	while (n)
	{
		min = p[n - 1] < min ? p[n - 1] : min;
		--n;
	}
	return min;
}

int ConvertBGR2HSI(Mat src, Mat dst)
{
	if (src.type() != CV_8UC3)
	{
		printf("src type error\n");
		return 1;
	}
	if (dst.type() != CV_8UC3 && dst.type() != CV_64FC3)
	{
		printf("dst type error\n");
		return 2;
	}
	Mat dst_temp;
	dst.convertTo(dst_temp, CV_64FC3);

	double b, g, r;
	double bgr[3];
	double theta;

	for (int y = 0; y < src.rows; y++)
	{
		for (int x = 0; x < src.cols; x++)
		{
			b = double(src.at<Vec3b>(y, x)[0]) / 255.;
			g = double(src.at<Vec3b>(y, x)[1]) / 255.;
			r = double(src.at<Vec3b>(y, x)[2]) / 255.;
			bgr[0] = b;
			bgr[1] = g;
			bgr[2] = r;
			theta = pow(r - g, 2) + (r - b)*(g - b) == 0 ?
				(acos(0.5*((r - g) + (r - b)) / sqrt(0.0000001))) * 180. / M_PI :
				(acos(0.5*((r - g) + (r - b)) / sqrt(pow(r - g, 2) + (r - b)*(g - b)))) * 180. / M_PI;
			dst_temp.at<Vec3d>(y, x)[0] = b > g ? (360. - theta) : theta;
			dst_temp.at<Vec3d>(y, x)[1] = 1. - (3. / (r + g + b))*FindMin(bgr, sizeof(bgr) / sizeof(bgr[0]));
			dst_temp.at<Vec3d>(y, x)[2] = (1. / 3.) * (r + g + b);

			dst_temp.at<Vec3d>(y, x)[0] *= 0.5;//[0-360]->[0,180]，保证能被uchar表示
			dst_temp.at<Vec3d>(y, x)[1] *= 255.;
			dst_temp.at<Vec3d>(y, x)[2] *= 255.;

			if (dst.type() == CV_8UC3)
			{
				dst.at<Vec3b>(y, x)[0] = cvRound(dst_temp.at<Vec3d>(y, x)[0]);
				dst.at<Vec3b>(y, x)[1] = cvRound(dst_temp.at<Vec3d>(y, x)[1]);
				dst.at<Vec3b>(y, x)[2] = cvRound(dst_temp.at<Vec3d>(y, x)[2]);
			}
			else
			{
				dst.at<Vec3d>(y, x)[0] = dst_temp.at<Vec3d>(y, x)[0];
				dst.at<Vec3d>(y, x)[1] = dst_temp.at<Vec3d>(y, x)[1];
				dst.at<Vec3d>(y, x)[2] = dst_temp.at<Vec3d>(y, x)[2];
			}
		}
	}

	return 0;
}

int ConvertHSI2BGR(Mat src, Mat dst)
{
	if (dst.type() != CV_8UC3)
	{
		printf("dst type error");
		return 1;
	}
	if (src.type() != CV_8UC3 && src.type() != CV_64FC3)
	{
		printf("src type error");
		return 2;
	}
	Mat src_temp;
	src.convertTo(src_temp, CV_64FC3);

	double h, s, i;
	double b, g, r;
	for (int y = 0; y < src.rows; y++)
	{
		for (int x = 0; x < src.cols; x++)
		{
			h = (src_temp.at<Vec3d>(y, x)[0] * 2. / 180.) * M_PI;
			s = src_temp.at<Vec3d>(y, x)[1] / 255.;
			i = src_temp.at<Vec3d>(y, x)[2] / 255.;

			if (i > (2. / 3.))
			{
				s = s > (2. / i - 2) ? 2. / i - 2 : s;
			}

			if (h >= 0 && h < 2. / 3. * M_PI)
			{
				b = i * (1 - s);
				r = i * (1 + (s * cos(h) / cos(1. / 3. * M_PI - h)));
				g = 3 * i - (r + b);
			}
			else if (h >= 2. / 3. * M_PI&&h < 4. / 3. * M_PI)
			{
				h = h - 2. / 3. * M_PI;
				r = i * (1 - s);
				g = i * (1 + (s * cos(h) / cos(1. / 3. * M_PI - h)));
				b = 3 * i - (r + g);
			}
			else if (h >= 4. / 3. * M_PI&&h <= 2. * M_PI)
			{
				h = h - 4. / 3. * M_PI;
				g = i * (1 - s);
				b = i * (1 + (s * cos(h) / cos(1. / 3. * M_PI - h)));
				r = 3 * i - (g + b);
			}
			else
			{
				cout << "h error : " << h << endl;
				//return -1;
			}

			dst.at<Vec3b>(y, x)[0] = saturate_cast<uchar>(cvRound(b * 255.));
			dst.at<Vec3b>(y, x)[1] = saturate_cast<uchar>(cvRound(g * 255.));
			dst.at<Vec3b>(y, x)[2] = saturate_cast<uchar>(cvRound(r * 255.));
		}
	}
	return 0;
}


int CalcNormalizedHistogram(Mat img, Mat histImg, int histHeight, int *pmax, int *hist, Scalar color)
{
	//Mat lutTable = Mat::zeros(1, 256, CV_8U);
	//LUT(histImg, lutTable, histImg);
	memset(hist, 0, 256 * sizeof(int));
	histImg = 0;
	int max = 0;
	int max_i = 0;
	for (int y = 0; y < img.rows; y++)
	{
		for (int x = 0; x < img.cols; x++)
		{
			hist[(int)img.at<uchar>(y, x)]++;
			if (hist[(int)img.at<uchar>(y, x)] > max)
			{
				max = hist[(int)img.at<uchar>(y, x)];
				max_i = img.at<uchar>(y, x);
			}
		}
	}
	*pmax = max_i;
	//minMaxLoc(img, &min, &max, 0, 0);
	int binValue;
	for (int i = 0; i < 256; ++i)
	{
		binValue = hist[i] * histHeight / max;
		rectangle(histImg, Point(i, histHeight), Point(i + 1, histHeight - binValue), color);
	}

	return *hist;
}

int FilterProcessing(
	Mat src, Mat dst, Mat filter,
	double ProcessingMethod(Mat filterArea, Mat filter))
{
	Mat src_padding = src.clone();
	Mat filterArea;
	int padding = (filter.rows - 1) / 2;
	//padding the border
	//BORDER_REPLICATE表示复制法扩充边缘
	copyMakeBorder(src, src_padding, padding, padding, padding, padding, BORDER_REPLICATE);

	if (dst.type() == CV_8U)
	{
		for (int y = padding; y < src_padding.rows - padding; y++)
		{
			for (int x = padding; x < src_padding.cols - padding; x++)
			{
				filterArea = src_padding(Range(y - padding, y + padding + 1), Range(x - padding, x + padding + 1));
				dst.at<uchar>(y - padding, x - padding) = cvRound(ProcessingMethod(filterArea, filter));//cvRound返回跟参数最接近的整数
			}
		}
	}
	else if (dst.type() == CV_64F)
	{
		for (int y = padding; y < src_padding.rows - padding; y++)
		{
			for (int x = padding; x < src_padding.cols - padding; x++)
			{
				filterArea = src_padding(Range(y - padding, y + padding + 1), Range(x - padding, x + padding + 1));
				dst.at<double>(y - padding, x - padding) = ProcessingMethod(filterArea, filter);
			}
		}
	}
	else
	{
		cout << "type error" << endl;
	}

	return 0;
}