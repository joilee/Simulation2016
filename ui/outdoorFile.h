#ifndef _OUTDOORFILE_H_
#define _OUTDOORFILE_H_

#include "ui_outdoorFile.h"
class outdoorFileDialog : public QDialog
{
	Q_OBJECT
public:
	outdoorFileDialog(QWidget *parent = 0);
	~outdoorFileDialog();
	QString getMaterialPath();
	QStringList  getScene2DPath();//建筑物
	QStringList  getSceneHeightPath();//高度
	QString getPlanePath(); //海拔 
	void createActions();
private slots:
		void openMaterialFile();
		void openBuildingVector();
		void openHeight();
		void openPlane();
private:
	Ui::outdoorFile ui;
	QString O_material_path;

	QString O_Scene2DInfoFile_path;//建筑物文件
	QStringList  O_Scene2DInfoFile_paths;
	
	QString O_SceneHeightInfoFile_path;//建筑物高度文件
	QStringList O_SceneHeightInfoFile_paths;

	QString O_ScenePlaneHeightInfoFile_path;//海拔文件
};

#endif // !_OUTDOORFILE_H_
