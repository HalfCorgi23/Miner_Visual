#include "stdafx.h"
#include "Serial_Connect.h"
#include "include\json\json.h"
#include <fstream>

#pragma comment(lib,"jsoncppd.lib")

int Serial_Num;//串口编号

using namespace std;

/*声明串口*/
Serial_Connect::Serial_Connect()
{
	Json::Reader Config_Reader;
	Json::Value Config_Value;
	ifstream IFS;
	IFS.open("config.json", ios::binary);
	if (Config_Reader.parse(IFS, Config_Value, false))
	{
		Serial_Num= Config_Value["Serial_Port"].asInt();
		printf_s("串口配置文件加载成功！\n");
	}
	else
	{
		printf_s("串口配置文件加载失败！\n");
		printf_s("按任意键退出……\n");
		int oo = 0; scanf_s("%d", oo);
	}
	IFS.close();
	if (Serial_Num == 1)
	{
		Handle_Comm = CreateFile(_T("COM1:"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);//COM1，读写权限，独占方式，直接打开，同步方式
	}
	else if (Serial_Num == 2)
	{
		Handle_Comm = CreateFile(_T("COM2:"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);//COM2，读写权限，独占方式，直接打开，同步方式
	}
	else if (Serial_Num == 3)
	{
		Handle_Comm = CreateFile(_T("COM3:"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);//COM3，读写权限，独占方式，直接打开，同步方式
	}
	else if (Serial_Num == 4)
	{
		Handle_Comm = CreateFile(_T("COM4:"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);//COM4，读写权限，独占方式，直接打开，同步方式
	}
	else if (Serial_Num == 5)
	{
		Handle_Comm = CreateFile(_T("COM5:"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);//COM5，读写权限，独占方式，直接打开，同步方式
	}
	else if (Serial_Num == 6)
	{
		Handle_Comm = CreateFile(_T("COM6:"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);//COM6，读写权限，独占方式，直接打开，同步方式
	}
	else if (Serial_Num == 7)
	{
		Handle_Comm = CreateFile(_T("COM7:"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);//COM7，读写权限，独占方式，直接打开，同步方式
	}
}

/*串口初始化*/
int Serial_Connect::Serial_Init()
{
	if (Handle_Comm == (HANDLE)-1)
	{
		printf_s("串口COM");
		printf_s("%d", Serial_Num);
		printf_s("连接失败！\n按任意键继续……");
		char s;
		scanf_s(&s);
		return 1;
	}
	else
	{
		printf_s("串口COM");
		printf_s("%d", Serial_Num);
		printf_s("已连接\n");
		//同步I/O方式打开串口
		SetupComm(Handle_Comm, 1024, 1024);  //输入输出缓冲区1024
		COMMTIMEOUTS TimeOuts;

		//设定读超时时间
		TimeOuts.ReadIntervalTimeout = MAXDWORD;
		TimeOuts.ReadTotalTimeoutMultiplier = 0;
		TimeOuts.ReadTotalTimeoutConstant = 0;

		//设定写超时时间
		TimeOuts.WriteTotalTimeoutMultiplier = 0;
		TimeOuts.WriteTotalTimeoutConstant = 50;

		SetCommTimeouts(Handle_Comm, &TimeOuts);  //设置超时

		DCB Handle_Dcb;
		GetCommState(Handle_Comm, &Handle_Dcb);  //获取串口配置信息
												 //修改串口参数
		Handle_Dcb.BaudRate = 115200;  //波特率
		Handle_Dcb.ByteSize = 8;  //数据位8位
		Handle_Dcb.Parity = NOPARITY;  //无奇偶检验位
		Handle_Dcb.StopBits = TWOSTOPBITS;  //两个停止位

											//保存串口信息
		SetCommState(Handle_Comm, &Handle_Dcb);
		//清空缓存
		PurgeComm(Handle_Comm, PURGE_TXCLEAR | PURGE_RXCLEAR);
		return 0;
	}
}

/*写串口*/
void Serial_Connect::Serial_Write(char lpOut[1])
{
	DWORD dwBytesWrite = 1;
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	BOOL bWriteStat;
	ClearCommError(Handle_Comm, &dwErrorFlags, &ComStat);
	bWriteStat = WriteFile(Handle_Comm, lpOut, dwBytesWrite, &dwBytesWrite, NULL);
	if (!bWriteStat)
	{
		printf("写串口失败！状态：\n");
	}
	else
	{
		printf("写串口成功，状态：");
	}
	printf("%d\n", &lpOut);
	PurgeComm(Handle_Comm,
		PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
}

/*读串口*/
char Serial_Connect::Serial_Read()
{
	char str[1];
	DWORD wCount;
	BOOL bReadStat;
	bReadStat = ReadFile(Handle_Comm, str, 1, &wCount, NULL);
	if (!bReadStat)
	{
		printf_s("WARNING: Serial read failed! ");
	}
	else
	{
		printf_s("CONNECTION: Serial read success! Statue:");
		printf_s("%d", &str[0]);
	}
	return str[0];
}

/*关闭串口*/
void Serial_Connect::Serial_Close()
{
	CloseHandle(Handle_Comm);
}


