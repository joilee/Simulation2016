#ifndef MODELPARA_H
#define  MODELPARA_H
#include "geometry/emxModel.h"
#include "rasterHeight/readGrid.h"

class ModelPara
{
public:
	ModelPara();
	~ModelPara();


public:
	//建筑物 模型 全局设置
	bool modelexist;//全局模型存在
	bool localexist;//局部模型存在
	emxModel *  trianglePara;
	double LocalScene_range;
	vector<material> materialdatabase;

	//海拔数据处理
	//bool heightLoaded;  //海拔数据是否已经导入
	vector<GridHeight> heightR;

	vector<int> rowNum,colNum;//海拔文件的行列数
	vector<double> stdLen;//海拔文件的间隔
	vector<double> xmin;//海拔文件的左上角和右下角。
	vector<double> ymax;
private:

};





#endif