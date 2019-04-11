#include<iostream>
#include<string>
#include<vector>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include<opencv2\opencv.hpp>   
#include<opencv2\highgui\highgui.hpp>
using namespace std;
using namespace cv;

//Mat img = imread("D:\\importance2\\gaotu\\gaotushiyan\\picture\\mandril_color.tif");
Mat img = imread("D:\\importance2\\gaotu\\gaotushiyan\\picture\\cat.jpg");

void swell()
{
	Mat out;
	//获取自定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15)); //第一个参数MORPH_RECT表示矩形的卷积核，当然还可以选择椭圆形的、交叉型的
	//膨胀操作
	dilate(img, out, element);
	imshow("膨胀操作", out);
	waitKey(0);
	return;
}

void corrosion()
{
	Mat out;
	//获取自定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15)); //第一个参数MORPH_RECT表示矩形的卷积核，当然还可以选择椭圆形的、交叉型的
	//腐蚀操作
	erode(img, out, element);
	imshow("腐蚀操作", out);
	waitKey(0);
	return;
}

void morphology(int i)
{
	//形态学梯度（Morphological Gradient）为膨胀图与腐蚀图之差,可以用形态学梯度来保留物体的边缘轮廓

	//%顶帽变换是指原始图像减去其开运算的图像
	//而开运算可用于补偿不均匀的背景亮度，所以用一个大的结构元素做开运算后
	//然后用原图像减去这个开运算，就得到了背景均衡的图像，这也叫做是图像的顶帽运算
	//顶帽运算往往用来分离比邻近点亮一些的斑块。

	//黑帽变换是原始图像减去其闭运算后的图像.黑帽运算用来分离比邻近点暗一些的斑块。
	vector<int> v = { MORPH_OPEN, MORPH_CLOSE,MORPH_GRADIENT,MORPH_TOPHAT,MORPH_BLACKHAT,MORPH_ERODE,MORPH_DILATE };
	vector<string> s = { "开运算","闭运算","形态学梯度","顶帽","黑帽","腐蚀","膨胀" };
	Mat out;
	//获取自定义核
	//第一个参数MORPH_RECT表示矩形的卷积核，当然还可以选择椭圆形的MORPH_ELLIPSE、交叉型的MORPH_CROSS
	//第二个参数表示内核的尺寸
	//第三个参数表示锚点的位置，默认为中心
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15)); 

	//高级形态学处理，调用这个函数就可以了，具体要选择哪种操作，就修改第三个参数就可以了。这里演示的是形态学梯度处理
	morphologyEx(img, out, v[i], element);
	imshow(s[i]+"处理", out);
	waitKey(0);
	return;
}
int main()
{
	imshow("原始图", img);
	swell();
	corrosion();
	morphology(0);
	morphology(1);
	morphology(2);
	morphology(3);
	morphology(4);
	destroyAllWindows();
	return 0;
}