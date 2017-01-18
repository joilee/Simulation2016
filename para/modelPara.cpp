#include "modelPara.h"
ModelPara::ModelPara()
{
	modelexist=false;
	localexist=false;
	trianglePara=NULL;
	LocalScene_range=2000;
}

ModelPara::~ModelPara()
{
	if (trianglePara!=NULL)
	{
		delete trianglePara;
	}
}
