#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat src = imread("test.jpg", 0);
	Mat dist;
	Mat proc;
	Mat proc1;
	Mat labelmat;
	Mat statsmat;
	Mat centermat;
	threshold(src, dist, 0, 255, THRESH_BINARY_INV);
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(9, 9));
	Mat element1 = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
	morphologyEx(dist, proc, MORPH_OPEN, element);
	morphologyEx(proc, proc1, MORPH_CLOSE, element1);
	int nComp = connectedComponentsWithStats(proc1, labelmat, statsmat, centermat, 8, CV_32S);
	cout << "圆的个数为:" << nComp - 1 << endl;
	for (int i = 1; i < nComp; i++)
	{
		Rect bndbox;
		bndbox.x = statsmat.at<int>(i, 0);
		bndbox.y = statsmat.at<int>(i, 1);
		bndbox.width = statsmat.at<int>(i, 2);
		bndbox.height = statsmat.at<int>(i, 3);
		rectangle(proc1, bndbox, CV_RGB(255, 255, 255), 1, 8, 0);
	}
	imshow("ss", proc1);
	waitKey(0);
}