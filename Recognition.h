#pragma once

#ifndef RECOGNITION

int Recognize_Result_X[3][4];//ʶ����X��������
int Recognize_Result_Y[3][4];//ʶ����Y��������
int Recognize_Result_Square[3][4];//ʶ�����������

//���������ļ�
int Json_Init();

//����ͷ��ʼ��
int Camera_Init();

//Ѱ����
int Find_Ball(int Cameranum);

//Ѱ������
int Find_Zone(int color, int CameraNum);

//��ȡ����ͷ
int Read_Camera(int CameraNum);

//��ʱ����
int Delay(int microsecond);

//��ʾͼ��
int Display_Result(int Cameranum);

#endif // !RECOGNIZE

