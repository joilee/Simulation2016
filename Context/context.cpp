#include "context.h"


globalContext::globalContext()
{
	Sites.clear();
	no_simplane = false;
	modelPara=new ModelPara;
}

globalContext::~globalContext()
{
	 vector<Site>().swap(Sites);
	 if (modelPara!=NULL)
	 {
		 delete modelPara;
	 }
}