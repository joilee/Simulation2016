#include "modelPara.h"
ModelPara::ModelPara()
{
	modelexist=false;
	localexist=false;
	trianglePara=NULL;
}

ModelPara::~ModelPara()
{
	if (trianglePara!=NULL)
	{
		delete trianglePara;
	}
}
