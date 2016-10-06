#include <Windows.h>
#include <iostream>

const int OPEN_SUCCESS = 0;//串口开启成功
const int OPEN_FAILURE = 1;//串口开启失败
const int COM1 = 1;//串口COM1
const int COM2 = 2;//串口COM2
const int COM3 = 3;//串口COM3
const int COM4 = 4;//串口COM4
const int COM5 = 5;//串口COM5
const int COM6 = 6;//串口COM6
const int COM7 = 7;//串口COM7
const int COM8 = 8;//串口COM8
const int COM9 = 9;//串口COM9

using namespace std;

#pragma once
/*半双工串口连接
声明串口：Serial_Connect(int)
（1~8）
COM1 串口1
COM2 串口2
COM3 串口3
以此类推
初始化串口：Serial_Init()
写一位串口：Serial_Write(char)
读一位串口：char Serial_Read();
关闭串口：Serial_Close()
*/
class Serial_Connect
{
public:
	Serial_Connect(int serial_num);

	//初始化串口
	int Serial_Init();

	//写一位串口(char[1])
	void Serial_Write(char lpOut[1]);

	/*读一位串口*/
	char Serial_Read();

	//关闭串口
	void Serial_Close();


private:
	HANDLE Handle_Comm; //创建串口实例
};
