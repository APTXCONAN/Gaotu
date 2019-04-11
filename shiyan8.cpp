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
	//��ȡ�Զ����
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15)); //��һ������MORPH_RECT��ʾ���εľ���ˣ���Ȼ������ѡ����Բ�εġ������͵�
	//���Ͳ���
	dilate(img, out, element);
	imshow("���Ͳ���", out);
	waitKey(0);
	return;
}

void corrosion()
{
	Mat out;
	//��ȡ�Զ����
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15)); //��һ������MORPH_RECT��ʾ���εľ���ˣ���Ȼ������ѡ����Բ�εġ������͵�
	//��ʴ����
	erode(img, out, element);
	imshow("��ʴ����", out);
	waitKey(0);
	return;
}

void morphology(int i)
{
	//��̬ѧ�ݶȣ�Morphological Gradient��Ϊ����ͼ�븯ʴͼ֮��,��������̬ѧ�ݶ�����������ı�Ե����

	//%��ñ�任��ָԭʼͼ���ȥ�俪�����ͼ��
	//������������ڲ��������ȵı������ȣ�������һ����ĽṹԪ�����������
	//Ȼ����ԭͼ���ȥ��������㣬�͵õ��˱��������ͼ����Ҳ������ͼ��Ķ�ñ����
	//��ñ������������������ڽ�����һЩ�İ߿顣

	//��ñ�任��ԭʼͼ���ȥ���������ͼ��.��ñ��������������ڽ��㰵һЩ�İ߿顣
	vector<int> v = { MORPH_OPEN, MORPH_CLOSE,MORPH_GRADIENT,MORPH_TOPHAT,MORPH_BLACKHAT,MORPH_ERODE,MORPH_DILATE };
	vector<string> s = { "������","������","��̬ѧ�ݶ�","��ñ","��ñ","��ʴ","����" };
	Mat out;
	//��ȡ�Զ����
	//��һ������MORPH_RECT��ʾ���εľ���ˣ���Ȼ������ѡ����Բ�ε�MORPH_ELLIPSE�������͵�MORPH_CROSS
	//�ڶ���������ʾ�ں˵ĳߴ�
	//������������ʾê���λ�ã�Ĭ��Ϊ����
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15)); 

	//�߼���̬ѧ����������������Ϳ����ˣ�����Ҫѡ�����ֲ��������޸ĵ����������Ϳ����ˡ�������ʾ������̬ѧ�ݶȴ���
	morphologyEx(img, out, v[i], element);
	imshow(s[i]+"����", out);
	waitKey(0);
	return;
}
int main()
{
	imshow("ԭʼͼ", img);
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