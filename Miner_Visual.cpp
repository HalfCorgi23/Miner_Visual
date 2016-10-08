// Miner_Visual.cpp : �������̨Ӧ�ó������ڵ㡣



#include "stdafx.h"
#include "Recognition.h"
#include "Serial_Connect.h"

const int VERSION = 1;
const int TEST = 5;
const int ZONE_SQUARE_L = 4000;//���������ֵ
const int SERIAL_DELAY_MS = 2; //���ڷ��ͼ��
const int LOCATION_LEFT = 220;//���λ��
const int LOCATION_RIGHT = 420;//�Ҳ�λ��
const int LOCATION_LEFT_0 = 128;//�����λ��
const int LOCATION_LEFT_1 = 256;//ƫ���λ��
const int LOCATION_RIGHT_1 = 384;//ƫ�Ҳ�λ��
const int LOCATION_RIGHT_0 = 512;//���Ҳ�λ��

using namespace cv;
using namespace std;

Serial_Connect Serial(COM4);//��������COM4

Recognition REC_0(CAMERA_0, DISPLAY_ON);//0#ǰ����ͷʶ��ʵ��
Recognition REC_1(CAMERA_1, DISPLAY_ON);//1#������ͷʶ��ʵ��
Recognition REC_2(CAMERA_2, DISPLAY_ON);//2#������ͷʶ��ʵ��

int Serial_Statue;//����״̬

//����ͨѶ
void Serial_Print()
{
	//0�ź�λ
	Serial.Serial_Write("0");
	waitKey(SERIAL_DELAY_MS);

	//1ǰ����ͷ��
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

	//2ǰ����ͷ�ϰ�
	if (REC_0.Square[BARRIER] != -1)
	{
		Serial.Serial_Write("2");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	waitKey(SERIAL_DELAY_MS);

	//3������ͷ��
	if (REC_1.Square[BALL] != -1)
	{
		Serial.Serial_Write("2");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	waitKey(SERIAL_DELAY_MS);

	//4������ͷ��
	if (REC_2.Square[BALL] != -1)
	{
		Serial.Serial_Write("2");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	waitKey(SERIAL_DELAY_MS);

	//5ǰ����ͷ���д�С
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

	//6ǰ����ͷ��д�С
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

	//7ǰ����ͷ���λ��
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

	//8ǰ����ͷ����λ��
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

	//9������ͷ���д�С
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

	//10������ͷ��д�С
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

	//11������ͷ���λ��
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

	//12������ͷ����λ��
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

	//13������ͷ���д�С
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

	//14������ͷ��д�С
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

	//15������ͷ���λ��
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

	//16������ͷ����λ��
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

	//17������ͷ�ϰ�
	if (REC_1.Square[BARRIER] != -1)
	{
		Serial.Serial_Write("2");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	waitKey(SERIAL_DELAY_MS);

	//18������ͷ�ϰ�
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

void Imformation_Print()//������Ϣ��ʾ
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