#include <Windows.h>
#include <iostream>

const int OPEN_SUCCESS = 0;//���ڿ����ɹ�
const int OPEN_FAILURE = 1;//���ڿ���ʧ��
const int COM1 = 1;//����COM1
const int COM2 = 2;//����COM2
const int COM3 = 3;//����COM3
const int COM4 = 4;//����COM4
const int COM5 = 5;//����COM5
const int COM6 = 6;//����COM6
const int COM7 = 7;//����COM7
const int COM8 = 8;//����COM8
const int COM9 = 9;//����COM9

using namespace std;

#pragma once
/*��˫����������
�������ڣ�Serial_Connect(int)
��1~8��
COM1 ����1
COM2 ����2
COM3 ����3
�Դ�����
��ʼ�����ڣ�Serial_Init()
дһλ���ڣ�Serial_Write(char)
��һλ���ڣ�char Serial_Read();
�رմ��ڣ�Serial_Close()
*/
class Serial_Connect
{
public:
	Serial_Connect(int serial_num);

	//��ʼ������
	int Serial_Init();

	//дһλ����(char[1])
	void Serial_Write(char lpOut[1]);

	/*��һλ����*/
	char Serial_Read();

	//�رմ���
	void Serial_Close();


private:
	HANDLE Handle_Comm; //��������ʵ��
};
