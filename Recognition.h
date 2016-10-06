#pragma once

#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <vector>
#include <sstream>
#include <fstream>

#include "include\json\json.h"

#pragma comment(lib,"jsoncpp.lib")

const int DISPLAY_ON = 0;//��ʾ����������
const int DISPLAY_OFF = 1;//��ʾ�������ر�
const int BALL = 0;//��
const int BARRIER = 1;//�ϰ�
const int BLUEZONE = 2;//��ɫ����
const int REDZONE = 3;//��ɫ����
const int BLACKBALL = 0;//��ɫ��
const int WHITEBALL = 4;//��ɫ��
const int TARGET_NOT_FOUND = 0;//δ�ҵ�Ŀ��
const int TARGET_FOUND = 1;//���ҵ�Ŀ��
const int BALL_SQUARE_MIN = 400;//�����С���
const int BALL_SQUARE_MAX = 1000;//���������
const int CAMERA_0 = 0;//0#����ͷ
const int CAMERA_1 = 1;//1#����ͷ
const int CAMERA_2 = 2;//2#����ͷ

/*Ŀ��ʶ��(����ͼ���ţ�ͼ����ʾ����)������ͷ 0��CAMERA_0������ͷ 1��CAMERA_1������ͷ 2��CAMERA_2��ͼ����ʾ��DISPLAY_ON ����DISPLAY_OFF ��
Recognition::Recognize(Mat input) - ʶ������(Mat)����ͼ��
Recognition::X[4] - Ŀ��X�������� {���ϰ�����ɫ���򣬺�ɫ����}��-1Ϊδ����Ŀ��
Recognition::Y[4] - Ŀ��Y��������{���ϰ�����ɫ���򣬺�ɫ����}��-1Ϊδ����Ŀ��
Recognition::Square[4] - Ŀ���������{���ϰ�����ɫ���򣬺�ɫ����}��-1Ϊδ����Ŀ��
BALL ��BARRIER �ϰ���BLUEZONE ��ɫ����REDZONE ��ɫ����*/
class Recognition 
{
public:
	//Ŀ��ʶ��(����ͼ���ţ�ͼ����ʾ����)������ͷ 0��CAMERA_0������ͷ 1��CAMERA_1������ͷ 2��CAMERA_2��ͼ����ʾ��DISPLAY_ON ����DISPLAY_OFF ��
	Recognition(int camera_num, int display_sw);

	//Ŀ��ʶ��
	Recognition();

	int X[4];//Ŀ��X��������{���ϰ�����ɫ���򣬺�ɫ����}��-1Ϊδ����Ŀ��
	int Y[4];//Ŀ��Y��������{���ϰ�����ɫ���򣬺�ɫ����}��-1Ϊδ����Ŀ��
	int Square[4];//Ŀ���������{���ϰ�����ɫ���򣬺�ɫ����}��-1Ϊδ����Ŀ��

	//ʶ�����((Mat)����ͼ��)
	int Recognize();
private:
	char d;

	//�����ļ���ȡ
	void Json_Get();

	//ͨ������
	void Channel_Separation();

	/*Ѱ�Һ���*/
	double Find_Black_Ball();

	/*Ѱ�Ұ���*/
	double Find_White_Ball();

	/*Ѱ�Һ�ɫ����ɫ����*/
	double Find_Zone(int channel);

	/*ʶ������ʾ*/
	void Display_Result();

	/*Ѱ����
	-1 ��Ŀ��
	0 ����Ŀ��*/
	int Find_Ball();
};

