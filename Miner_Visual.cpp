// Miner_Visual.cpp : �������̨Ӧ�ó������ڵ㡣

#include "stdafx.h"
#include "Recognition.h"
#include "Serial_Connect.h"
//
//const int VERSION = 1;
//const int TEST = 5;
//const int ZONE_SQUARE_L = 4000;//���������ֵ
//const int SERIAL_DELAY_MS = 2; //���ڷ��ͼ��
//const int LOCATION_LEFT = 220;//���λ��
//const int LOCATION_RIGHT = 420;//�Ҳ�λ��
//const int LOCATION_LEFT_0 = 128;//�����λ��
//const int LOCATION_LEFT_1 = 256;//ƫ���λ��
//const int LOCATION_RIGHT_1 = 384;//ƫ�Ҳ�λ��
//const int LOCATION_RIGHT_0 = 512;//���Ҳ�λ��
//

const int CAMERA_0 = 0;//0������ͷ
const int CAMERA_1 = 1;//1������ͷ
const int CAMERA_2 = 2;//2������ͷ
const int VERSION = 2;//���汾
const int TEST = 0;//���԰汾
const int RED_ZONE = 1;//��ɫ����
const int BLUE_ZONE = 2;//��ɫ����
const int BARRIERS = 3;//�ϰ���
const int BALLS = 0;//��
const int LOCATION_LEFT = 210;//����ֵ
const int LOCATION_RIGHT = 420;//����ֵ
const int LOCATION_LEFT_LESS = 250;//ƫ����ֵ
const int LOCATION_LEFT_MORE = 130;//������ֵ
const int LOCATION_RIGHT_LESS = 390;//ƫ����ֵ
const int LOCATION_RIGHT_MORE = 510;//������ֵ
const int ZONE_SQUARE_LIMIT = 60000;//���������ֵ

extern int Recognize_Result_X[3][4];//ʶ����X��������
extern int Recognize_Result_Y[3][4];//ʶ����Y��������
extern int Recognize_Result_Square[3][4];//ʶ�����������

Serial_Connect Serial;//��������COM4

//����ͨѶ
void Serial_Print()
{
	//0�ź�λ
	Serial.Serial_Write("0");
	Delay(2);

	//1ǰ����ͷ��
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

	//2ǰ����ͷ�ϰ�
	if (Recognize_Result_Square[CAMERA_0][BARRIERS] != -1)
	{
		Serial.Serial_Write("2");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	Delay(2);

	//3������ͷ��
	if (Recognize_Result_Square[CAMERA_1][BALLS] != -1)
	{
		Serial.Serial_Write("2");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	Delay(2);

	//4������ͷ��
	if (Recognize_Result_Square[CAMERA_2][BALLS] != -1)
	{
		Serial.Serial_Write("2");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	Delay(2);

	//5ǰ����ͷ���д�С
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

	//6ǰ����ͷ��д�С
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

	//7ǰ����ͷ���λ��
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

	//8ǰ����ͷ����λ��
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

	//9������ͷ���д�С
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

	//10������ͷ��д�С
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

	//11������ͷ���λ��
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

	//12������ͷ����λ��
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

	//13������ͷ���д�С
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

	//14������ͷ��д�С
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

	//15������ͷ���λ��
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

	//16������ͷ����λ��
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

	//17������ͷ�ϰ�
	if (Recognize_Result_Square[CAMERA_1][BARRIERS] != -1)
	{
		Serial.Serial_Write("2");
	}
	else
	{
		Serial.Serial_Write("1");
	}
	Delay(2);

	//18������ͷ�ϰ�
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

void Imformation_Print()//������Ϣ��ʾ
{
	printf_s("\n|************�򺽲ɿ�������Ӿ�ʶ��ϵͳ************|\n\n");
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