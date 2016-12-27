﻿
#ifndef CONTEXT_H
#define CONTEXT_H
#include <iostream>
#include "Antenna/antenna.h"
#include "Antenna/receiver.h"
/************************************************************************/
/* 单例模式                                                                     */
/************************************************************************/
class globalContext
{
public:	



	//建筑物 模型 全局设置
	bool modelexist;//全局模型存在
	bool localexist;//局部模型存在
	bool no_simplane;


	//
	vector<Site> Sites;  //多个小区

	vector<no_simplaneReceiver> No_SimPlanePoint; //非仿真面设置的接收点信息


	~globalContext();
	static globalContext*GetInstance()
	{
		if (ctx==NULL)
		{
			ctx=new globalContext();
		}
		return ctx;
	}



private:
	//嵌套类,目的是回收
	class CGarbo     
	{    
	public:    
		~CGarbo()    
		{    
			if(globalContext::ctx)    
				delete globalContext::ctx;   
		}    
	};    
	static CGarbo Garbo;     

	globalContext();
	static globalContext* ctx;
};






#endif