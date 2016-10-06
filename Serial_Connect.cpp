#include "stdafx.h"
#include "Serial_Connect.h"

int Serial_Num;//���ڱ��

using namespace std;

/*��������*/
Serial_Connect::Serial_Connect(int serial_num)
{
	Serial_Num = serial_num;
	if (serial_num == 1)
	{
		Handle_Comm = CreateFile(_T("COM1:"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);//COM1����дȨ�ޣ���ռ��ʽ��ֱ�Ӵ򿪣�ͬ����ʽ
	}
	else if (serial_num == 2)
	{
		Handle_Comm = CreateFile(_T("COM2:"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);//COM2����дȨ�ޣ���ռ��ʽ��ֱ�Ӵ򿪣�ͬ����ʽ
	}
	else if (serial_num == 3)
	{
		Handle_Comm = CreateFile(_T("COM3:"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);//COM3����дȨ�ޣ���ռ��ʽ��ֱ�Ӵ򿪣�ͬ����ʽ
	}
	else if (serial_num == 4)
	{
		Handle_Comm = CreateFile(_T("COM4:"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);//COM4����дȨ�ޣ���ռ��ʽ��ֱ�Ӵ򿪣�ͬ����ʽ
	}
	else if (serial_num == 5)
	{
		Handle_Comm = CreateFile(_T("COM5:"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);//COM5����дȨ�ޣ���ռ��ʽ��ֱ�Ӵ򿪣�ͬ����ʽ
	}
	else if (serial_num == 6)
	{
		Handle_Comm = CreateFile(_T("COM6:"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);//COM6����дȨ�ޣ���ռ��ʽ��ֱ�Ӵ򿪣�ͬ����ʽ
	}
	else if (serial_num == 7)
	{
		Handle_Comm = CreateFile(_T("COM7:"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);//COM7����дȨ�ޣ���ռ��ʽ��ֱ�Ӵ򿪣�ͬ����ʽ
	}
}

/*���ڳ�ʼ��*/
int Serial_Connect::Serial_Init()
{
	if (Handle_Comm == (HANDLE)-1)
	{
		printf_s("SETUP: Serial COM");
		printf_s("%d", Serial_Num);
		printf_s(" disconnected!\nWARNING: Press any key to continue...");
		char s;
		scanf_s(&s);
		return 1;
	}
	else
	{
		printf_s("SETUP: Serial COM");
		printf_s("%d", Serial_Num);
		printf_s(" connected!\n");
		//ͬ��I/O��ʽ�򿪴���
		SetupComm(Handle_Comm, 1024, 1024);  //�������������1024
		COMMTIMEOUTS TimeOuts;

		//�趨����ʱʱ��
		TimeOuts.ReadIntervalTimeout = MAXDWORD;
		TimeOuts.ReadTotalTimeoutMultiplier = 0;
		TimeOuts.ReadTotalTimeoutConstant = 0;

		//�趨д��ʱʱ��
		TimeOuts.WriteTotalTimeoutMultiplier = 0;
		TimeOuts.WriteTotalTimeoutConstant = 50;

		SetCommTimeouts(Handle_Comm, &TimeOuts);  //���ó�ʱ

		DCB Handle_Dcb;
		GetCommState(Handle_Comm, &Handle_Dcb);  //��ȡ����������Ϣ
												 //�޸Ĵ��ڲ���
		Handle_Dcb.BaudRate = 115200;  //������
		Handle_Dcb.ByteSize = 8;  //����λ8λ
		Handle_Dcb.Parity = NOPARITY;  //����ż����λ
		Handle_Dcb.StopBits = TWOSTOPBITS;  //����ֹͣλ

											//���洮����Ϣ
		SetCommState(Handle_Comm, &Handle_Dcb);
		//��ջ���
		PurgeComm(Handle_Comm, PURGE_TXCLEAR | PURGE_RXCLEAR);
		return 0;
	}
}

/*д����*/
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
		printf("WARNING: Serial write failed! Statue:");
	}
	else
	{
		printf("CONNECTION: Serial write success! Statue:");
	}
	printf("%d\n", &lpOut);
	PurgeComm(Handle_Comm,
		PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
}

/*������*/
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

/*�رմ���*/
void Serial_Connect::Serial_Close()
{
	CloseHandle(Handle_Comm);
}


