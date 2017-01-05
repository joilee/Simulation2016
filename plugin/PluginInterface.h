#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QtPlugin>
#define QtPlugin_iid "com.Plugin.Computation"  
class ComputeInterface
{
public:
#include "para/modelPara.h"

private:

};

Q_DECLARE_INTERFACE(ComputeInterface,QtPlugin_iid);


#endif