#include "context.h"


globalContext::globalContext()
{
	cptPara=new ComputePara;
	modelPara=new ModelPara;
}

globalContext::~globalContext()
{
	
	 if (modelPara!=NULL)
	 {
		 delete modelPara;
	 }
}