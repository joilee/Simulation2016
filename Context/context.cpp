#include "context.h"


globalContext::globalContext()
{
	Sites.clear();
	modelexist=false;
	localexist=false;
	no_simplane = false;
}

globalContext::~globalContext()
{
	 vector<Site>().swap(Sites);
}