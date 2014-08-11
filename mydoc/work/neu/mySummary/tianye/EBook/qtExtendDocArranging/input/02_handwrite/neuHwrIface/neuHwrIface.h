#ifndef __NEUHWRIFACE_H
#define __NEUHWRIFACE_H
#include <string>
#include <vector>
extern "C"
{
#include "hwr_api2.h"
}

#define MY_DEBUG 1
//#define WINAPI  
//#define STATIC_LINK
//#define ENABLE_SEGMENTATION
//#define AI_ON
//#define ENABLE_CONTINUOUS_WRITING
#ifndef AI_ON
#define AI_ON
#endif
#define ENABLE_BOX_WRITING
typedef struct point_type point_type;
using std::vector;
using std::string;

//接口作用：给定一个点数组，处理之后返回备选的结果字符串，用于手写输入法
class NeuHwrIface
{
	public:
		//初始化接口,可以将输入的点序列传到这里
		explicit NeuHwrIface(const point_type *points = NULL);

		~NeuHwrIface();
		//设置用户输入的点序列
		void setInputPoints(const point_type *points);

		//对已经输入的点序列进行处理
		void process();

		//得到处理结果(备选结果列表)，返回到output中
		void getOutputStrList(vector<string> &output);
	private:
		vector<point_type> inputPoints;
		vector<string> outputStrList;
		point_type *PerStrokeData;
		point_type * RawCharData;
};
#endif
