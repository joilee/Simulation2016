﻿
#ifndef CONTEXT_H
#define CONTEXT_H
#include <iostream>

#include "para/modelPara.h"
#include "para/computePara.h"
#include "para/visualPara.h"
/************************************************************************/
/* 单例模式                                                                     */
/************************************************************************/
class globalContext
{
public:	

	//
	ModelPara * modelPara;
	ComputePara* cptPara;
	visPara *visualPara;
	


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
