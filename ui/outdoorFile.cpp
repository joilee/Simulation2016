#include "outdoorFile.h"
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>
outdoorFileDialog::outdoorFileDialog(QWidget *parent ){
	ui.setupUi(this);
	createActions();
}

outdoorFileDialog::~outdoorFileDialog()
{

}

QString outdoorFileDialog::getMaterialPath()
{
		if(O_material_path.isEmpty())
		{
			QMessageBox::warning(this, QString::fromLocal8Bit("获得材质文件路径"),QString::fromLocal8Bit("请先导入并编辑生成最终场景中所需材质属性"));
			return NULL;
		}
		return O_material_path;
}

QStringList   outdoorFileDialog::getScene2DPath()
{
	if(O_Scene2DInfoFile_paths.isEmpty())
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("获得建筑物文件路径"),QString::fromLocal8Bit("请先导入建筑物文件！"));
		return QStringList();
	}
	return O_Scene2DInfoFile_paths;
}

QStringList  outdoorFileDialog::getSceneHeightPath()
{
	if (O_SceneHeightInfoFile_paths.isEmpty())
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("获得建筑物高度文件路径"),QString::fromLocal8Bit("请先导入建筑物文件！"));
		return QStringList();
	}
	return O_SceneHeightInfoFile_paths;
}

QString outdoorFileDialog::getPlanePath()
{
	if(O_ScenePlaneHeightInfoFile_path.isEmpty())
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("获得海拔文件路径"),QString::fromLocal8Bit("请先导入海拔物文件！"));
		return NULL;
	}
	return O_ScenePlaneHeightInfoFile_path;
}

void outdoorFileDialog::openMaterialFile()
{
	QString path = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("打开材质文件"),"./",QString::fromLocal8Bit("txt 材质文件 (*.txt)"));
	if (path.isEmpty())
		return;
	O_material_path  = path;  //保存当前材质文件路径，以便后续对材质文件的更新操作

}


void outdoorFileDialog::openBuildingVector()
{
	QStringList paths = QFileDialog::getOpenFileNames(this,QString::fromLocal8Bit("导入场景vector文件"),"./",QString::fromLocal8Bit(" 场景二维信息文件 "));
	if (paths.isEmpty())
		return;
	O_Scene2DInfoFile_paths = paths;
}

void outdoorFileDialog:: openHeight()
{
	QStringList paths = QFileDialog::getOpenFileNames(this,QString::fromLocal8Bit("导入场景vector文件"),"./",QString::fromLocal8Bit(" 场景高度信息文件"));
	if (paths.isEmpty())
		return;
	O_SceneHeightInfoFile_paths = paths;
}

void outdoorFileDialog::openPlane()
{
	QString path = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("导入地面海拔 raster文件"),"./",QString::fromLocal8Bit(" 场景地面海拔信息文件"));
	if (path.isEmpty())
		return;
	O_ScenePlaneHeightInfoFile_path = path;
}
void outdoorFileDialog::createActions()
{
	connect(ui.materialButton,SIGNAL(clicked()),this,SLOT(openMaterialFile()));
	connect(ui.buildingButton,SIGNAL(clicked()),this,SLOT(openBuildingVector()));
	connect(ui.heightButton,SIGNAL(clicked()),this,SLOT(openHeight()));
	connect(ui.altitudeButton,SIGNAL(clicked()),this,SLOT(openPlane()));
}