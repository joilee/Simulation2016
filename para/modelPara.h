#ifndef MODELPARA_H
#define  MODELPARA_H
#include "geometry/emxModel.h"


class ModelPara
{
public:
	ModelPara();
	~ModelPara();


public:
	//建筑物 模型 全局设置
	bool modelexist;//全局模型存在
	bool localexist;//局部模型存在
	emxModel *  trianglePara;
private:

};





#endif