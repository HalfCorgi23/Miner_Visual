// Miner_Visual.cpp : 定义控制台应用程序的入口点。



#include "stdafx.h"
#include "Recognition.h"
#include "Serial_Connect.h"

const int VERSION = 1;
const int TEST = 5;
const int ZONE_SQUARE_L = 4000;//盒子面积阈值
const int SERIAL_DELAY_MS = 2; //串口发送间隔
const int LOCATION_LEFT = 220;//左侧位置
const int LOCATION_RIGHT = 420;//右侧位置
const int LOCATION_LEFT_0 = 128;//正左侧位置
const int LOCATION_LEFT_1 = 256;//偏左侧位置
const int LOCATION_RIGHT_1 = 384;//偏右侧位置
const int LOCATION_RIGHT_0 = 512;//正右侧位置

using namespace cv;
using namespace std;

Serial_Connect Serial(COM4);//声明串口COM4

Recognition REC_0(CAMERA_0, DISPLAY_ON);//0#前摄像头识别实例
Recognition REC_1(CAMERA_1, DISPLAY_ON);//1#左摄像头识别实例
Recognition REC_2(CAMERA_2, DISPLAY_ON);//2#右摄像头识别实例

int Serial_Statue;//串口状态

//串口通讯
void Serial_Print()
{
	//0信号位
	Serial.Serial_Write("0");
	waitKey(SERIAL_DELAY_MS);

	//1前摄像头球
	if (REC_0.Square[BALL] == -1)
	{
		Serial.Serial_Write("1");
	}
	else if (REC_0.X[BALL] >= 0 && REC_0.X[BALL] < LOCATION_LEFT)
	{
		Serial.Serial_Write("2");
	}
	else if (REC_0.X[BALL] >= LOCATION_LEFT && REC_0.X[BALL] <= LOCATION_RIGHT)
	{
		Serial.Serial_Write("3");
	}
	else if (REC_0.X[BALL] > LOCATION_RIGHT && REC_0.X[BALL] <= 640)
	{
		Serial.Serial_Write("4");
	}
	waitKey(SERIAL_DELAY_MS);

	//2前摄像头障碍
	if (REC_0.Square[BARRIER] != -1)
	{
		Serial.Serial_Write("2");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	waitKey(SERIAL_DELAY_MS);

	//3左摄像头球
	if (REC_1.Square[BALL] != -1)
	{
		Serial.Serial_Write("2");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	waitKey(SERIAL_DELAY_MS);

	//4右摄像头球
	if (REC_2.Square[BALL] != -1)
	{
		Serial.Serial_Write("2");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	waitKey(SERIAL_DELAY_MS);

	//5前摄像头蓝盒大小
	if(REC_0.Square[BLUEZONE]>ZONE_SQUARE_L)
	{
		Serial.Serial_Write("3");
	}
	else if(REC_0.Square[REDZONE]>0)
	{
		Serial.Serial_Write("2");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	waitKey(SERIAL_DELAY_MS);

	//6前摄像头红盒大小
	if (REC_0.Square[REDZONE]>ZONE_SQUARE_L)
	{
		Serial.Serial_Write("3");
	}
	else if (REC_0.Square[REDZONE]>0)
	{
		Serial.Serial_Write("2");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	waitKey(SERIAL_DELAY_MS);

	//7前摄像头红盒位置
	if (REC_0.X[REDZONE]>=0&& REC_0.X[REDZONE]<LOCATION_LEFT_0)
	{
		Serial.Serial_Write("2");
	}
	else if (REC_0.X[REDZONE] >= LOCATION_LEFT_0 && REC_0.X[REDZONE]<LOCATION_LEFT_1)
	{
		Serial.Serial_Write("3");
	}
	else if (REC_0.X[REDZONE] >= LOCATION_LEFT_1 && REC_0.X[REDZONE]<LOCATION_RIGHT_1)
	{
		Serial.Serial_Write("4");
	}
	else if (REC_0.X[REDZONE] >= LOCATION_RIGHT_1 && REC_0.X[REDZONE]<LOCATION_RIGHT_0)
	{
		Serial.Serial_Write("5");
	}
	else if (REC_0.X[REDZONE] >= LOCATION_RIGHT_0 && REC_0.X[REDZONE] <= 640)
	{
		Serial.Serial_Write("6");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	waitKey(SERIAL_DELAY_MS);

	//8前摄像头蓝盒位置
	if (REC_0.X[BLUEZONE] >= 0 && REC_0.X[BLUEZONE]<LOCATION_LEFT_0)
	{
		Serial.Serial_Write("2");
	}
	else if (REC_0.X[BLUEZONE] >= LOCATION_LEFT_0 && REC_0.X[BLUEZONE]<LOCATION_LEFT_1)
	{
		Serial.Serial_Write("3");
	}
	else if (REC_0.X[BLUEZONE] >= LOCATION_LEFT_1 && REC_0.X[BLUEZONE]<LOCATION_RIGHT_1)
	{
		Serial.Serial_Write("4");
	}
	else if (REC_0.X[BLUEZONE] >= LOCATION_RIGHT_1 && REC_0.X[BLUEZONE]<LOCATION_RIGHT_0)
	{
		Serial.Serial_Write("5");
	}
	else if (REC_0.X[BLUEZONE] >= LOCATION_RIGHT_0 && REC_0.X[BLUEZONE] <= 640)
	{
		Serial.Serial_Write("6");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	waitKey(SERIAL_DELAY_MS);

	//9左摄像头蓝盒大小
	if (REC_1.Square[BLUEZONE]>ZONE_SQUARE_L)
	{
		Serial.Serial_Write("3");
	}
	else if (REC_1.Square[REDZONE]>0)
	{
		Serial.Serial_Write("2");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	waitKey(SERIAL_DELAY_MS);

	//10左摄像头红盒大小
	if (REC_1.Square[REDZONE]>ZONE_SQUARE_L)
	{
		Serial.Serial_Write("3");
	}
	else if (REC_1.Square[REDZONE]>0)
	{
		Serial.Serial_Write("2");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	waitKey(SERIAL_DELAY_MS);

	//11左摄像头红盒位置
	if (REC_1.X[REDZONE] >= 0 && REC_1.X[REDZONE]<LOCATION_LEFT_0)
	{
		Serial.Serial_Write("2");
	}
	else if (REC_1.X[REDZONE] >= LOCATION_LEFT_0 && REC_1.X[REDZONE]<LOCATION_LEFT_1)
	{
		Serial.Serial_Write("3");
	}
	else if (REC_1.X[REDZONE] >= LOCATION_LEFT_1 && REC_1.X[REDZONE]<LOCATION_RIGHT_1)
	{
		Serial.Serial_Write("4");
	}
	else if (REC_1.X[REDZONE] >= LOCATION_RIGHT_1 && REC_1.X[REDZONE]<LOCATION_RIGHT_0)
	{
		Serial.Serial_Write("5");
	}
	else if (REC_1.X[REDZONE] >= LOCATION_RIGHT_0 && REC_1.X[REDZONE] <= 640)
	{
		Serial.Serial_Write("6");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	waitKey(SERIAL_DELAY_MS);

	//12左摄像头蓝盒位置
	if (REC_1.X[BLUEZONE] >= 0 && REC_1.X[BLUEZONE]<LOCATION_LEFT_0)
	{
		Serial.Serial_Write("2");
	}
	else if (REC_1.X[BLUEZONE] >= LOCATION_LEFT_0 && REC_1.X[BLUEZONE]<LOCATION_LEFT_1)
	{
		Serial.Serial_Write("3");
	}
	else if (REC_1.X[BLUEZONE] >= LOCATION_LEFT_1 && REC_1.X[BLUEZONE]<LOCATION_RIGHT_1)
	{
		Serial.Serial_Write("4");
	}
	else if (REC_1.X[BLUEZONE] >= LOCATION_RIGHT_1 && REC_1.X[BLUEZONE]<LOCATION_RIGHT_0)
	{
		Serial.Serial_Write("5");
	}
	else if (REC_1.X[BLUEZONE] >= LOCATION_RIGHT_0 && REC_1.X[BLUEZONE] <= 640)
	{
		Serial.Serial_Write("6");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	waitKey(SERIAL_DELAY_MS);

	//13右摄像头蓝盒大小
	if (REC_2.Square[BLUEZONE]>ZONE_SQUARE_L)
	{
		Serial.Serial_Write("3");
	}
	else if (REC_2.Square[REDZONE]>0)
	{
		Serial.Serial_Write("2");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	waitKey(SERIAL_DELAY_MS);

	//14右摄像头红盒大小
	if (REC_2.Square[REDZONE]>ZONE_SQUARE_L)
	{
		Serial.Serial_Write("3");
	}
	else if (REC_2.Square[REDZONE]>0)
	{
		Serial.Serial_Write("2");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	waitKey(SERIAL_DELAY_MS);

	//15右摄像头红盒位置
	if (REC_2.X[REDZONE] >= 0 && REC_2.X[REDZONE]<LOCATION_LEFT_0)
	{
		Serial.Serial_Write("2");
	}
	else if (REC_2.X[REDZONE] >= LOCATION_LEFT_0 && REC_2.X[REDZONE]<LOCATION_LEFT_1)
	{
		Serial.Serial_Write("3");
	}
	else if (REC_2.X[REDZONE] >= LOCATION_LEFT_1 && REC_2.X[REDZONE]<LOCATION_RIGHT_1)
	{
		Serial.Serial_Write("4");
	}
	else if (REC_2.X[REDZONE] >= LOCATION_RIGHT_1 && REC_2.X[REDZONE]<LOCATION_RIGHT_0)
	{
		Serial.Serial_Write("5");
	}
	else if (REC_2.X[REDZONE] >= LOCATION_RIGHT_0 && REC_2.X[REDZONE] <= 640)
	{
		Serial.Serial_Write("6");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	waitKey(SERIAL_DELAY_MS);

	//16右摄像头蓝盒位置
	if (REC_2.X[BLUEZONE] >= 0 && REC_2.X[BLUEZONE]<LOCATION_LEFT_0)
	{
		Serial.Serial_Write("2");
	}
	else if (REC_2.X[BLUEZONE] >= LOCATION_LEFT_0 && REC_2.X[BLUEZONE]<LOCATION_LEFT_1)
	{
		Serial.Serial_Write("3");
	}
	else if (REC_2.X[BLUEZONE] >= LOCATION_LEFT_1 && REC_2.X[BLUEZONE]<LOCATION_RIGHT_1)
	{
		Serial.Serial_Write("4");
	}
	else if (REC_2.X[BLUEZONE] >= LOCATION_RIGHT_1 && REC_2.X[BLUEZONE]<LOCATION_RIGHT_0)
	{
		Serial.Serial_Write("5");
	}
	else if (REC_2.X[BLUEZONE] >= LOCATION_RIGHT_0 && REC_2.X[BLUEZONE] <= 640)
	{
		Serial.Serial_Write("6");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	waitKey(SERIAL_DELAY_MS);

	//17左摄像头障碍
	if (REC_1.Square[BARRIER] != -1)
	{
		Serial.Serial_Write("2");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	waitKey(SERIAL_DELAY_MS);

	//18右摄像头障碍
	if (REC_2.Square[BARRIER] != -1)
	{
		Serial.Serial_Write("2");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	waitKey(SERIAL_DELAY_MS);
}

void Imformation_Print()//启动信息显示
{
	printf_s("\n|************Visual System for Miner************|\n\n");
	printf_s("|*****************Version V");
	printf_s("%d.", VERSION);
	printf_s("%d******************|\n\n", TEST);
}

int main()
{
	Imformation_Print();
	Serial_Statue = Serial.Serial_Init();
	while (1)
	{
		REC_0.Recognize();
		REC_1.Recognize();
		REC_2.Recognize();
		Serial_Print();
		waitKey(33);
	}
	return 0;
}