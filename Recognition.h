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

const int DISPLAY_ON = 0;//显示处理结果开启
const int DISPLAY_OFF = 1;//显示处理结果关闭
const int BALL = 0;//球
const int BARRIER = 1;//障碍
const int BLUEZONE = 2;//蓝色区域
const int REDZONE = 3;//红色区域
const int BLACKBALL = 0;//黑色球
const int WHITEBALL = 4;//白色球
const int TARGET_NOT_FOUND = 0;//未找到目标
const int TARGET_FOUND = 1;//已找到目标
const int BALL_SQUARE_MIN = 400;//球的最小面积
const int BALL_SQUARE_MAX = 1000;//球的最大面积
const int CAMERA_0 = 0;//0#摄像头
const int CAMERA_1 = 1;//1#摄像头
const int CAMERA_2 = 2;//2#摄像头

/*目标识别(输入图像编号，图像显示开关)；摄像头 0：CAMERA_0，摄像头 1：CAMERA_1，摄像头 2：CAMERA_2；图像显示：DISPLAY_ON 开，DISPLAY_OFF 关
Recognition::Recognize(Mat input) - 识别函数（(Mat)输入图像）
Recognition::X[4] - 目标X坐标数组 {球，障碍，蓝色区域，红色区域}，-1为未发现目标
Recognition::Y[4] - 目标Y坐标数组{球，障碍，蓝色区域，红色区域}，-1为未发现目标
Recognition::Square[4] - 目标面积数组{球，障碍，蓝色区域，红色区域}，-1为未发现目标
BALL 球；BARRIER 障碍；BLUEZONE 蓝色区域；REDZONE 红色区域*/
class Recognition 
{
public:
	//目标识别(输入图像编号，图像显示开关)；摄像头 0：CAMERA_0，摄像头 1：CAMERA_1，摄像头 2：CAMERA_2；图像显示：DISPLAY_ON 开，DISPLAY_OFF 关
	Recognition(int camera_num, int display_sw);

	//目标识别
	Recognition();

	int X[4];//目标X坐标数组{球，障碍，蓝色区域，红色区域}，-1为未发现目标
	int Y[4];//目标Y坐标数组{球，障碍，蓝色区域，红色区域}，-1为未发现目标
	int Square[4];//目标面积数组{球，障碍，蓝色区域，红色区域}，-1为未发现目标

	//识别操作((Mat)输入图像)
	int Recognize();
private:
	char d;

	//配置文件获取
	void Json_Get();

	//通道分离
	void Channel_Separation();

	/*寻找黑球*/
	double Find_Black_Ball();

	/*寻找白球*/
	double Find_White_Ball();

	/*寻找红色或蓝色区域*/
	double Find_Zone(int channel);

	/*识别结果显示*/
	void Display_Result();

	/*寻找球
	-1 无目标
	0 发现目标*/
	int Find_Ball();
};

