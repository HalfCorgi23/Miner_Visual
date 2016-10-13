// Miner_Visual.cpp : 定义控制台应用程序的入口点。

#include "stdafx.h"
#include "Recognition.h"
#include "Serial_Connect.h"
//
//const int VERSION = 1;
//const int TEST = 5;
//const int ZONE_SQUARE_L = 4000;//盒子面积阈值
//const int SERIAL_DELAY_MS = 2; //串口发送间隔
//const int LOCATION_LEFT = 220;//左侧位置
//const int LOCATION_RIGHT = 420;//右侧位置
//const int LOCATION_LEFT_0 = 128;//正左侧位置
//const int LOCATION_LEFT_1 = 256;//偏左侧位置
//const int LOCATION_RIGHT_1 = 384;//偏右侧位置
//const int LOCATION_RIGHT_0 = 512;//正右侧位置
//

const int CAMERA_0 = 0;//0号摄像头
const int CAMERA_1 = 1;//1号摄像头
const int CAMERA_2 = 2;//2号摄像头
const int VERSION = 2;//主版本
const int TEST = 0;//测试版本
const int RED_ZONE = 1;//红色区域
const int BLUE_ZONE = 2;//红色区域
const int BARRIERS = 3;//障碍物
const int BALLS = 0;//球
const int LOCATION_LEFT = 210;//左阈值
const int LOCATION_RIGHT = 420;//右阈值
const int LOCATION_LEFT_LESS = 250;//偏左阈值
const int LOCATION_LEFT_MORE = 130;//过左阈值
const int LOCATION_RIGHT_LESS = 390;//偏右阈值
const int LOCATION_RIGHT_MORE = 510;//过右阈值
const int ZONE_SQUARE_LIMIT = 60000;//区域面积阈值

extern int Recognize_Result_X[3][4];//识别结果X坐标数组
extern int Recognize_Result_Y[3][4];//识别结果Y坐标数组
extern int Recognize_Result_Square[3][4];//识别结果面积数组

Serial_Connect Serial;//声明串口COM4

//串口通讯
void Serial_Print()
{
	//0信号位
	Serial.Serial_Write("0");
	Delay(2);

	//1前摄像头球
	if (Recognize_Result_Square[CAMERA_0][BALLS] == -1)
	{
		Serial.Serial_Write("1");
	}
	else if (Recognize_Result_X[CAMERA_0][BALLS] >= 0 && Recognize_Result_X[CAMERA_0][BALLS]< LOCATION_LEFT)
	{
		Serial.Serial_Write("2");
	}
	else if (Recognize_Result_X[CAMERA_0][BALLS] >= LOCATION_LEFT && Recognize_Result_X[CAMERA_0][BALLS] <= LOCATION_RIGHT)
	{
		Serial.Serial_Write("3");
	}
	else if (Recognize_Result_X[CAMERA_0][BALLS] > LOCATION_RIGHT && Recognize_Result_X[CAMERA_0][BALLS] <= 640)
	{
		Serial.Serial_Write("4");
	}
	Delay(2);

	//2前摄像头障碍
	if (Recognize_Result_Square[CAMERA_0][BARRIERS] != -1)
	{
		Serial.Serial_Write("2");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	Delay(2);

	//3左摄像头球
	if (Recognize_Result_Square[CAMERA_1][BALLS] != -1)
	{
		Serial.Serial_Write("2");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	Delay(2);

	//4右摄像头球
	if (Recognize_Result_Square[CAMERA_2][BALLS] != -1)
	{
		Serial.Serial_Write("2");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	Delay(2);

	//5前摄像头蓝盒大小
	if(Recognize_Result_Square[CAMERA_0][BLUE_ZONE]>ZONE_SQUARE_LIMIT)
	{
		Serial.Serial_Write("3");
	}
	else if(Recognize_Result_Square[CAMERA_0][BLUE_ZONE]>0)
	{
		Serial.Serial_Write("2");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	Delay(2);

	//6前摄像头红盒大小
	if (Recognize_Result_Square[CAMERA_0][RED_ZONE]>ZONE_SQUARE_LIMIT)
	{
		Serial.Serial_Write("3");
	}
	else if (Recognize_Result_Square[CAMERA_0][RED_ZONE]>0)
	{
		Serial.Serial_Write("2");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	Delay(2);

	//7前摄像头红盒位置
	if (Recognize_Result_X[CAMERA_0][RED_ZONE] >0&& Recognize_Result_X[CAMERA_0][RED_ZONE]<LOCATION_LEFT_MORE)
	{
		Serial.Serial_Write("2");
	}
	else if (Recognize_Result_X[CAMERA_0][RED_ZONE] >= LOCATION_LEFT_MORE && Recognize_Result_X[CAMERA_0][RED_ZONE]<LOCATION_LEFT_LESS)
	{
		Serial.Serial_Write("3");
	}
	else if (Recognize_Result_X[CAMERA_0][RED_ZONE] >= LOCATION_LEFT_LESS && Recognize_Result_X[CAMERA_0][RED_ZONE]<LOCATION_RIGHT_LESS)
	{
		Serial.Serial_Write("4");
	}
	else if (Recognize_Result_X[CAMERA_0][RED_ZONE] >= LOCATION_RIGHT_LESS && Recognize_Result_X[CAMERA_0][RED_ZONE]<LOCATION_RIGHT_MORE)
	{
		Serial.Serial_Write("5");
	}
	else if (Recognize_Result_X[CAMERA_0][RED_ZONE] >= LOCATION_RIGHT_MORE && Recognize_Result_X[CAMERA_0][RED_ZONE] < 640)
	{
		Serial.Serial_Write("6");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	Delay(2);

	//8前摄像头蓝盒位置
	if (Recognize_Result_X[CAMERA_0][BLUE_ZONE] >0 && Recognize_Result_X[CAMERA_0][BLUE_ZONE]<LOCATION_LEFT_MORE)
	{
		Serial.Serial_Write("2");
	}
	else if (Recognize_Result_X[CAMERA_0][BLUE_ZONE] >= LOCATION_LEFT_MORE && Recognize_Result_X[CAMERA_0][BLUE_ZONE]<LOCATION_LEFT_LESS)
	{
		Serial.Serial_Write("3");
	}
	else if (Recognize_Result_X[CAMERA_0][BLUE_ZONE] >= LOCATION_LEFT_LESS && Recognize_Result_X[CAMERA_0][BLUE_ZONE]<LOCATION_RIGHT_LESS)
	{
		Serial.Serial_Write("4");
	}
	else if (Recognize_Result_X[CAMERA_0][BLUE_ZONE] >= LOCATION_RIGHT_LESS && Recognize_Result_X[CAMERA_0][BLUE_ZONE]<LOCATION_RIGHT_MORE)
	{
		Serial.Serial_Write("5");
	}
	else if (Recognize_Result_X[CAMERA_0][BLUE_ZONE] >= LOCATION_RIGHT_MORE && Recognize_Result_X[CAMERA_0][BLUE_ZONE] < 640)
	{
		Serial.Serial_Write("6");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	Delay(2);

	//9左摄像头蓝盒大小
	if (Recognize_Result_Square[CAMERA_1][BLUE_ZONE]>ZONE_SQUARE_LIMIT)
	{
		Serial.Serial_Write("3");
	}
	else if (Recognize_Result_Square[CAMERA_1][BLUE_ZONE]>0)
	{
		Serial.Serial_Write("2");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	Delay(2);

	//10左摄像头红盒大小
	if (Recognize_Result_Square[CAMERA_1][RED_ZONE]>ZONE_SQUARE_LIMIT)
	{
		Serial.Serial_Write("3");
	}
	else if (Recognize_Result_Square[CAMERA_1][RED_ZONE]>0)
	{
		Serial.Serial_Write("2");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	Delay(2);

	//11左摄像头红盒位置
	if (Recognize_Result_X[CAMERA_1][RED_ZONE] >0 && Recognize_Result_X[CAMERA_1][RED_ZONE]<LOCATION_LEFT_MORE)
	{
		Serial.Serial_Write("2");
	}
	else if (Recognize_Result_X[CAMERA_1][RED_ZONE] >= LOCATION_LEFT_MORE && Recognize_Result_X[CAMERA_1][RED_ZONE]<LOCATION_LEFT_LESS)
	{
		Serial.Serial_Write("3");
	}
	else if (Recognize_Result_X[CAMERA_1][RED_ZONE] >= LOCATION_LEFT_LESS && Recognize_Result_X[CAMERA_1][RED_ZONE]<LOCATION_RIGHT_LESS)
	{
		Serial.Serial_Write("4");
	}
	else if (Recognize_Result_X[CAMERA_1][RED_ZONE] >= LOCATION_RIGHT_LESS && Recognize_Result_X[CAMERA_1][RED_ZONE]<LOCATION_RIGHT_MORE)
	{
		Serial.Serial_Write("5");
	}
	else if (Recognize_Result_X[CAMERA_1][RED_ZONE] >= LOCATION_RIGHT_MORE && Recognize_Result_X[CAMERA_1][RED_ZONE] < 640)
	{
		Serial.Serial_Write("6");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	Delay(2);

	//12左摄像头蓝盒位置
	if (Recognize_Result_X[CAMERA_1][BLUE_ZONE] >0 && Recognize_Result_X[CAMERA_1][BLUE_ZONE]<LOCATION_LEFT_MORE)
	{
		Serial.Serial_Write("2");
	}
	else if (Recognize_Result_X[CAMERA_1][BLUE_ZONE] >= LOCATION_LEFT_MORE && Recognize_Result_X[CAMERA_1][BLUE_ZONE]<LOCATION_LEFT_LESS)
	{
		Serial.Serial_Write("3");
	}
	else if (Recognize_Result_X[CAMERA_1][BLUE_ZONE] >= LOCATION_LEFT_LESS && Recognize_Result_X[CAMERA_1][BLUE_ZONE]<LOCATION_RIGHT_LESS)
	{
		Serial.Serial_Write("4");
	}
	else if (Recognize_Result_X[CAMERA_1][BLUE_ZONE] >= LOCATION_RIGHT_LESS && Recognize_Result_X[CAMERA_1][BLUE_ZONE]<LOCATION_RIGHT_MORE)
	{
		Serial.Serial_Write("5");
	}
	else if (Recognize_Result_X[CAMERA_1][BLUE_ZONE] >= LOCATION_RIGHT_MORE && Recognize_Result_X[CAMERA_1][BLUE_ZONE] < 640)
	{
		Serial.Serial_Write("6");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	Delay(2);

	//13右摄像头蓝盒大小
	if (Recognize_Result_Square[CAMERA_2][BLUE_ZONE]>ZONE_SQUARE_LIMIT)
	{
		Serial.Serial_Write("3");
	}
	else if (Recognize_Result_Square[CAMERA_2][BLUE_ZONE]>0)
	{
		Serial.Serial_Write("2");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	Delay(2);

	//14右摄像头红盒大小
	if (Recognize_Result_Square[CAMERA_2][RED_ZONE]>ZONE_SQUARE_LIMIT)
	{
		Serial.Serial_Write("3");
	}
	else if (Recognize_Result_Square[CAMERA_2][RED_ZONE]>0)
	{
		Serial.Serial_Write("2");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	Delay(2);

	//15右摄像头红盒位置
	if (Recognize_Result_X[CAMERA_2][RED_ZONE] >0 && Recognize_Result_X[CAMERA_2][RED_ZONE]<LOCATION_LEFT_MORE)
	{
		Serial.Serial_Write("2");
	}
	else if (Recognize_Result_X[CAMERA_2][RED_ZONE] >= LOCATION_LEFT_MORE && Recognize_Result_X[CAMERA_2][RED_ZONE]<LOCATION_LEFT_LESS)
	{
		Serial.Serial_Write("3");
	}
	else if (Recognize_Result_X[CAMERA_2][RED_ZONE] >= LOCATION_LEFT_LESS && Recognize_Result_X[CAMERA_2][RED_ZONE]<LOCATION_RIGHT_LESS)
	{
		Serial.Serial_Write("4");
	}
	else if (Recognize_Result_X[CAMERA_2][RED_ZONE] >= LOCATION_RIGHT_LESS && Recognize_Result_X[CAMERA_2][RED_ZONE]<LOCATION_RIGHT_MORE)
	{
		Serial.Serial_Write("5");
	}
	else if (Recognize_Result_X[CAMERA_2][RED_ZONE] >= LOCATION_RIGHT_MORE && Recognize_Result_X[CAMERA_2][RED_ZONE] < 640)
	{
		Serial.Serial_Write("6");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	Delay(2);

	//16右摄像头蓝盒位置
	if (Recognize_Result_X[CAMERA_2][BLUE_ZONE] >0 && Recognize_Result_X[CAMERA_2][BLUE_ZONE]<LOCATION_LEFT_MORE)
	{
		Serial.Serial_Write("2");
	}
	else if (Recognize_Result_X[CAMERA_2][BLUE_ZONE] >= LOCATION_LEFT_MORE && Recognize_Result_X[CAMERA_2][BLUE_ZONE]<LOCATION_LEFT_LESS)
	{
		Serial.Serial_Write("3");
	}
	else if (Recognize_Result_X[CAMERA_2][BLUE_ZONE] >= LOCATION_LEFT_LESS && Recognize_Result_X[CAMERA_2][BLUE_ZONE]<LOCATION_RIGHT_LESS)
	{
		Serial.Serial_Write("4");
	}
	else if (Recognize_Result_X[CAMERA_2][BLUE_ZONE] >= LOCATION_RIGHT_LESS && Recognize_Result_X[CAMERA_2][BLUE_ZONE]<LOCATION_RIGHT_MORE)
	{
		Serial.Serial_Write("5");
	}
	else if (Recognize_Result_X[CAMERA_2][BLUE_ZONE] >= LOCATION_RIGHT_MORE && Recognize_Result_X[CAMERA_2][BLUE_ZONE] < 640)
	{
		Serial.Serial_Write("6");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	Delay(2);

	//17左摄像头障碍
	if (Recognize_Result_Square[CAMERA_1][BARRIERS] != -1)
	{
		Serial.Serial_Write("2");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	Delay(2);

	//18右摄像头障碍
	if (Recognize_Result_Square[CAMERA_2][BARRIERS] != -1)
	{
		Serial.Serial_Write("2");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	Delay(2);
}

void Imformation_Print()//启动信息显示
{
	printf_s("\n|************沈航采矿机器人视觉识别系统************|\n\n");
	printf_s("|*****************Version V");
	printf_s("%d.", VERSION);
	printf_s("%d******************|\n\n", TEST);
}

int main()
{
	Imformation_Print();
	Serial.Serial_Init();
	Json_Init();
	Camera_Init();
	while (1)
	{
		
		Read_Camera(CAMERA_0);
		Find_Ball(CAMERA_0);
		Find_Zone(RED_ZONE,CAMERA_0);
		Find_Zone(BLUE_ZONE, CAMERA_0);
		Find_Zone(BARRIERS, CAMERA_0);
		Display_Result(CAMERA_0);
		
		Read_Camera(CAMERA_1);
		Find_Ball(CAMERA_1);
		Find_Zone(RED_ZONE,CAMERA_1);
		Find_Zone(BLUE_ZONE, CAMERA_1);
		Find_Zone(BARRIERS, CAMERA_1);
		Display_Result(CAMERA_1);
		
		Read_Camera(CAMERA_2);
		Find_Ball(CAMERA_2);
		Find_Zone(RED_ZONE,CAMERA_2);
		Find_Zone(BLUE_ZONE, CAMERA_1);
		Find_Zone(BARRIERS, CAMERA_1);
		Display_Result(CAMERA_2);

		Serial_Print();
	}
	return 0;
}