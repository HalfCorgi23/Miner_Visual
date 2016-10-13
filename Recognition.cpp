#include "Recognition.h"
#include "stdafx.h"

#include <sstream>
#include <fstream>
#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <vector>
#include <windows.h> 

#include "include\json\json.h"

#pragma comment(lib,"jsoncppd.lib")

using namespace std;

vector<vector<cv::Point>> Contours; //连通域

cv::Mat Camera_Source;//源图像
cv::Mat Source;//源图像
cv::Mat Gray;//灰度图像
cv::Mat BitwiseNot;//反色图像
cv::Mat Threshold;//阈值图像
cv::Mat Dilate;//腐蚀图像
cv::Mat Hsv_Source;//HSV图像
cv::Mat Gass_Source;//高斯模糊图像
cv::Mat Ranged_Channel;//颜色限制图像
cv::Mat Output;//输出图像

cv::VideoCapture Capture_0;//0号摄像头实例
cv::VideoCapture Capture_1;//1号摄像头实例
cv::VideoCapture Capture_2;//2号摄像头实例

extern int Recognize_Result_X[3][4];//识别结果X坐标数组
extern int Recognize_Result_Y[3][4];//识别结果Y坐标数组
extern int Recognize_Result_Square[3][4];//识别结果面积数组

const int BALL = 0;//球
const int WHITE_BALL = 0;//白球
const int REDZONE = 1;//红色区域
const int BLUEZONE = 2;//红色区域
const int BARRIER = 3;//障碍物
const int BLACK_BALL = 4;//黑球
const int TARGET_FOUND = 0;//已找到目标
const int TARGET_NOT_FOUND = 1;//未找到目标

int Black_Threshold;//黑色阈值
int White_Threshold;//白色阈值
int Black_Max_Square;//黑色球最大面积
int White_Max_Square;//白色球最大面积
int Black_Min_Square;//黑色球最小面积
int White_Min_Square;//白色球最小面积
int H_Range_Min[3];//H最小阈值
int S_Range_Min[3];//S最小阈值
int V_Range_Min[3];//V最小阈值
int H_Range_Max[3];//H最小阈值
int S_Range_Max[3];//S最小阈值
int V_Range_Max[3];//V最小阈值

int Black_X;//黑色球X坐标
int Black_Y;//黑色球Y坐标
int Black_Square;//黑色球面积
int White_X;//黑色球X坐标
int White_Y;//黑色球Y坐标
int White_Square;//黑色球面积

int Json_Init()
{
	Json::Reader Config_Reader;
	Json::Value Config_Value;
	ifstream IFS;
	IFS.open("config.json", ios::binary);
	if (Config_Reader.parse(IFS, Config_Value, false))
	{
		printf_s("配置文件加载中……\n");

		Black_Threshold = Config_Value["Black_Threshold"].asInt();
		White_Threshold = Config_Value["White_Threshold"].asInt();
		Black_Max_Square = Config_Value["Black_Ball_Square_Max"].asInt();
		White_Max_Square = Config_Value["White_Ball_Square_Max"].asInt();
		Black_Min_Square = Config_Value["Black_Ball_Square_Min"].asInt();
		White_Min_Square = Config_Value["White_Ball_Square_Min"].asInt();

		H_Range_Min[BARRIER] = Config_Value["H_Min_Barrier"].asInt();
		S_Range_Min[BARRIER] = Config_Value["S_Min_Barrier"].asInt();
		V_Range_Min[BARRIER] = Config_Value["V_Min_Barrier"].asInt();
		H_Range_Max[BARRIER] = Config_Value["H_Max_Barrier"].asInt();
		S_Range_Max[BARRIER] = Config_Value["S_Max_Barrier"].asInt();
		V_Range_Max[BARRIER] = Config_Value["V_Max_Barrier"].asInt();
		H_Range_Min[BLUEZONE] = Config_Value["H_Min_Blue"].asInt();
		S_Range_Min[BLUEZONE] = Config_Value["S_Min_Blue"].asInt();
		V_Range_Min[BLUEZONE] = Config_Value["V_Min_Blue"].asInt();
		H_Range_Max[BLUEZONE] = Config_Value["H_Max_Blue"].asInt();
		S_Range_Max[BLUEZONE] = Config_Value["S_Max_Blue"].asInt();
		V_Range_Max[BLUEZONE] = Config_Value["V_Max_Blue"].asInt();
		H_Range_Min[REDZONE] = Config_Value["H_Min_Red"].asInt();
		S_Range_Min[REDZONE] = Config_Value["S_Min_Red"].asInt();
		V_Range_Min[REDZONE] = Config_Value["V_Min_Red"].asInt();
		H_Range_Max[REDZONE] = Config_Value["H_Max_Red"].asInt();
		S_Range_Max[REDZONE] = Config_Value["S_Max_Red"].asInt();
		V_Range_Max[REDZONE] = Config_Value["V_Max_Red"].asInt();

		printf_s("加载完毕！\n");
	}
	else
	{
		printf_s("未找到配置文件！\n");
		printf_s("按任意键退出……\n");
		int ch = 0; scanf_s("%d", ch);
		exit(0);
	}
}

int Camera_Init()
{
	Capture_2.open(2);
	if (Capture_2.isOpened())
	{
		printf_s("2号摄像头开启成功!\n");
	}
	else
	{
		printf_s("2号摄像头开启失败!\n");
		printf_s("按任意键退出……\n");
		int df = 0; scanf_s("%d", df);
		exit(0);
	}
	Capture_1.open(1);
	if (Capture_1.isOpened())
	{
		printf_s("1号摄像头开启成功!\n");
	}
	else
	{
		printf_s("1号摄像头开启失败!\n");
		printf_s("按任意键退出……\n");
		int dh = 0; scanf_s("%d", dh);
		exit(0);
	}
	Capture_0.open(0);
	if (Capture_0.isOpened())
	{
		printf_s("0号摄像头开启成功!\n");
	}
	else
	{
		printf_s("0号摄像头开启失败!\n");
		printf_s("按任意键退出……\n");
		int dt = 0; scanf_s("%d", dt);
		exit(0);
	}
}

int Find_Ball(int CameraNum)
{
	//寻找白球
	Source = Camera_Source.clone();
	Output = Source.clone();
	string DisplayNum;
	stringstream SS;
	string Display_Title_White;
	string Display_Title_Black;
	SS << CameraNum;
	SS >> DisplayNum;
	Display_Title_White = DisplayNum + "号摄像头白";
	Display_Title_Black = DisplayNum + "号摄像头黑";

	int radius;
	cvtColor(Source, Gray, CV_BGR2GRAY);
	threshold(Gray, Threshold, White_Threshold, 255, CV_THRESH_BINARY);
	dilate(Threshold, Dilate, cv::Mat(5, 5, CV_8U), cv::Point(-1, -1), 2);
	cv::imshow(Display_Title_White, Dilate);
	findContours(Dilate, Contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE); //寻找连通域
	double Max_Area = 0;//最大连通域面积
	vector<cv::Point> Max_Contour;
	for (size_t i = 0; i < Contours.size(); i++)//寻找最大连通域
	{
		double area = contourArea(Contours[i]);
		if (area > Max_Area)
		{
			Max_Area = area;
			Max_Contour = Contours[i];
		}
	}
	cv::Rect Max_Rect = boundingRect(Max_Contour);//最大连通域矩形
	White_Square = Max_Rect.height*Max_Rect.width;
	if (White_Square<White_Max_Square&& White_Square>White_Min_Square)
	{
		radius = sqrt(White_Square) / 2 * 1.2;
		White_X = Max_Rect.x + radius;
		White_Y = Max_Rect.y + radius;
	}
	else
	{
		White_Square = -1;
		White_X = -1;
		White_Y = -1;
	}

	//寻找黑球
	Source = Camera_Source.clone();
	cvtColor(Source, Gray, CV_BGR2GRAY);
	bitwise_not(Gray, BitwiseNot);
	threshold(BitwiseNot, Threshold, Black_Threshold, 255, CV_THRESH_BINARY);
	//imshow("阈值图像", Threshold);
	dilate(Threshold, Dilate, cv::Mat(5, 5, CV_8U), cv::Point(-1, -1), 2);
	cv::imshow(Display_Title_Black, Dilate);
	//imshow("白球膨胀图像", Dilate);
	findContours(Dilate, Contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE); //寻找连通域
	Max_Area = 0;//最大连通域面积
	Max_Contour;
	for (size_t i = 0; i < Contours.size(); i++)//寻找最大连通域
	{
		double area = contourArea(Contours[i]);
		if (area > Max_Area)
		{
			Max_Area = area;
			Max_Contour = Contours[i];
		}
	}
	Max_Rect = boundingRect(Max_Contour);//最大连通域矩形
	Black_Square = Max_Rect.height*Max_Rect.width;
	if (Black_Square<Black_Max_Square&&Black_Square>White_Min_Square)
	{
		radius = sqrt(Black_Square) / 2 * 1.2;
		Black_X = Max_Rect.x + radius;
		Black_Y = Max_Rect.y + radius;
	}
	else
	{
		Black_Square = -1;
		Black_X = -1;
		Black_Y = -1;
	}
	//白黑球比较
	int square_temp1 = White_Square;
	int x_temp = White_X;
	int y_temp = White_Y;
	int square_temp2 = Black_Square;
	if (White_X == -1 || White_Y == -1)
	{
		Recognize_Result_X[CameraNum][BALL] = -1;
		Recognize_Result_Y[CameraNum][BALL] = -1;
		Recognize_Result_Square[CameraNum][BALL] = -1;
		return TARGET_NOT_FOUND;
	}
	else if (square_temp1 > square_temp2)
	{
		Recognize_Result_X[CameraNum][BALL] = White_X;
		Recognize_Result_Y[CameraNum][BALL] = White_Y;
		Recognize_Result_Square[CameraNum][BALL] = White_Square;
		return TARGET_FOUND;
	}
	else
	{
		Recognize_Result_X[CameraNum][BALL] = Black_X;
		Recognize_Result_Y[CameraNum][BALL] = Black_Y;
		Recognize_Result_Square[CameraNum][BALL] = Black_Square;
		return TARGET_FOUND;
	}
}

int Find_Zone(int color, int CameraNum)
{
	Source = Camera_Source.clone();
	GaussianBlur(Source, Gass_Source, cv::Size(15, 15), 4, 4);//高斯模糊
	cvtColor(Gass_Source, Hsv_Source, cv::COLOR_BGR2HSV);//RGB转HSV
	if (color == BLUEZONE)
	{
		cv::Scalar Blue_Range_Min(H_Range_Min[BLUEZONE], S_Range_Min[BLUEZONE], V_Range_Min[BLUEZONE]);
		cv::Scalar Blue_Range_Max(H_Range_Max[BLUEZONE], S_Range_Max[BLUEZONE], V_Range_Max[BLUEZONE]);
		inRange(Hsv_Source, Blue_Range_Min, Blue_Range_Max, Ranged_Channel);
	}
	else if (color == REDZONE)
	{
		cv::Scalar Red_Range_Min(H_Range_Min[REDZONE], S_Range_Min[REDZONE], V_Range_Min[REDZONE]);
		cv::Scalar Red_Range_Max(H_Range_Max[REDZONE], S_Range_Max[REDZONE], V_Range_Max[REDZONE]);
		inRange(Hsv_Source, Red_Range_Min, Red_Range_Max, Ranged_Channel);
	}
	else if (color == BARRIER)
	{
		cv::Scalar Barrier_Range_Min(H_Range_Min[BARRIER], S_Range_Min[BARRIER], V_Range_Min[BARRIER]);
		cv::Scalar Barrier_Range_Max(H_Range_Max[BARRIER], S_Range_Max[BARRIER], V_Range_Max[BARRIER]);
		inRange(Hsv_Source, Barrier_Range_Min, Barrier_Range_Max, Ranged_Channel);
	}
	findContours(Ranged_Channel, Contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE); //寻找连通域
	double Max_Area = 0;//最大连通域面积
	vector<cv::Point> Max_Contour;
	for (size_t i = 0; i < Contours.size(); i++)//寻找最大连通域
	{
		double area = contourArea(Contours[i]);
		if (area > Max_Area)
		{
			Max_Area = area;
			Max_Contour = Contours[i];
		}
	}
	cv::Rect Max_Rect = boundingRect(Max_Contour);//最大连通域矩形
	if (Max_Area < 625 || Max_Rect.x < 50 || Max_Rect.x>590 || Max_Rect.y < 50 || Max_Rect.y>430)
	{
		Recognize_Result_X[CameraNum][color] = -1;
		Recognize_Result_Y[CameraNum][color] = -1;
		Recognize_Result_Square[CameraNum][color] = -1;
		return TARGET_NOT_FOUND;
	}
	else
	{
		Recognize_Result_X[CameraNum][color] = Max_Rect.x;
		Recognize_Result_Y[CameraNum][color] = Max_Rect.y;
		Recognize_Result_Square[CameraNum][color] = Max_Area;
		return TARGET_FOUND;
	}

}

int Read_Camera(int CameraNum)
{
	switch (CameraNum)
	{
	default:
		break;
	case 0:
		Capture_0 >> Camera_Source;
		break;
	case 1:
		Capture_1 >> Camera_Source;
		break;
	case 2:
		Capture_2 >> Camera_Source;
		break;
	}
	return 0;
}

int Delay(int microsecond)
{
	cv::waitKey(microsecond);
	return 0;
}

int Display_Result(int Cameranum)
{
	Output = Source.clone();
	string Display_Title;
	stringstream SS;
	SS << Cameranum;
	SS >> Display_Title;
	Display_Title += "号摄像头结果";
	if (Recognize_Result_Square[Cameranum][BALL] >0)
	{
		cv::circle
		(
			Output,
			cv::Point
			(
				Recognize_Result_X[Cameranum][BALL],
				Recognize_Result_Y[Cameranum][BALL]
			),
			sqrt(Recognize_Result_Square[Cameranum][BALL]) / 2,
			cv::Scalar(255, 255, 255),
			2,
			8, 
			0
		);
	}
	if (Recognize_Result_Square[Cameranum][REDZONE] > 0)
	{
		cv::Rect Rect_Red
		(
			Recognize_Result_X[Cameranum][REDZONE],
			Recognize_Result_Y[Cameranum][REDZONE],
			sqrt(Recognize_Result_Square[Cameranum][REDZONE])*0.8,
			sqrt(Recognize_Result_Square[Cameranum][REDZONE])*1.25
		);
		cv::rectangle
		(
			Output,
			Rect_Red,
			cv::Scalar(0, 0, 255),
			2,
			8,
			0
		);
	}
	if (Recognize_Result_Square[Cameranum][BLUEZONE] > 0)
	{
		cv::Rect Rect_Blue
		(
			Recognize_Result_X[Cameranum][BLUEZONE],
			Recognize_Result_Y[Cameranum][BLUEZONE],
			sqrt(Recognize_Result_Square[Cameranum][BLUEZONE])*0.8,
			sqrt(Recognize_Result_Square[Cameranum][BLUEZONE])*1.25
		);
		cv::rectangle
		(
			Output,
			Rect_Blue,
			cv::Scalar(255, 0, 0),
			2,
			8,
			0
		);
	}
	if (Recognize_Result_Square[Cameranum][BARRIER] > 0)
	{
		cv::Rect Rect_Barrier
		(
			Recognize_Result_X[Cameranum][BARRIER],
			Recognize_Result_Y[Cameranum][BARRIER],
			sqrt(Recognize_Result_Square[Cameranum][BARRIER])*0.8,
			sqrt(Recognize_Result_Square[Cameranum][BARRIER])*1.25
		);
		cv::rectangle
		(
			Output,
			Rect_Barrier,
			cv::Scalar(0, 100, 255),
			2,
			8,
			0
		);
	}
	cv::imshow(Display_Title, Output);
	int out_str;
	for (int i = 0; i < 4; i++)
	{
		out_str = Recognize_Result_Square[Cameranum][i];
		printf_s("%d", out_str);
		printf_s(";");
	}
	printf_s("\n");
	return 0;
}
