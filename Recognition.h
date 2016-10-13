#pragma once

#ifndef RECOGNITION

int Recognize_Result_X[3][4];//识别结果X坐标数组
int Recognize_Result_Y[3][4];//识别结果Y坐标数组
int Recognize_Result_Square[3][4];//识别结果面积数组

//加载配置文件
int Json_Init();

//摄像头初始化
int Camera_Init();

//寻找球
int Find_Ball(int Cameranum);

//寻找区域
int Find_Zone(int color, int CameraNum);

//读取摄像头
int Read_Camera(int CameraNum);

//延时函数
int Delay(int microsecond);

//显示图像
int Display_Result(int Cameranum);

#endif // !RECOGNIZE

