#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QtPlugin>
#include "para/modelPara.h"
#define QtPlugin_iid "com.Plugin.Computation"  
class ComputeInterface
{
public:
	virtual void runAlgorithm(ModelPara *modelParameter=0)=0;

private:

};

Q_DECLARE_INTERFACE(ComputeInterface,QtPlugin_iid);


#endif