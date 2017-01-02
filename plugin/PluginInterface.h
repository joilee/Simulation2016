#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QtPlugin>
#define QtPlugin_iid "com.Plugin.Computation"  
class ComputeInterface
{
public:
	virtual void runAlgorithm()=0;

private:

};

Q_DECLARE_INTERFACE(ComputeInterface,QtPlugin_iid);


#endif