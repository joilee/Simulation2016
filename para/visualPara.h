﻿#ifndef VISPARA_H
#define VISPARA_H
#include "util/EField.h"


class visPara
{
public:
	visPara();
	~visPara();
	vector<vector<EField>> vis_AP_EFieldArrays;   //存储多个站点接收点计算信号强度
	vector<int> horizonNum;
	vector<int> veticalNum;
protected:

private:
};



#endif