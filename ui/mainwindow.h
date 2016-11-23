﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include "outdoorFile.h"
#include "InfoPage.h"
#include "computerOptionDialog.h"
#include "geometry/emxModel.h"
#include "meshOption.h"
#include <QtWidgets/QMessageBox>
class QAction; 
struct building;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();


public:
	emxModel* getEmxModel();
	void setModelName(QString name);//设置treewidget中的名字
	void outputLog(QString source);
	void setProgress(int value);

private slots:
	void openOutdoorFile();
	void computerOption();
	void loadAllFile(QString _name,QStringList _v,QStringList _h,QString _p);
	void showAll();
	void showLocal();
	void loadObj();
	void setMaterial();
	void open_material();
	void setMeshOption();
	//内部界面控件
private:
	Ui::MainWindowClass ui;
	QTreeWidgetItem* modelTW;
	QTreeWidgetItem* computeTW;
	QTreeWidgetItem* visualTW;

	outdoorFileDialog*  M_outdoorFileDialog;
	computerOptionDialog* M_computeroptionDialog;
	BuildingInfoPage * bip;
	localPage *lpg;
	meshOptionDialog *mod;
	//内部变量
 private:
	 QString material_path;
	 vector<material> materialdatabase;
	 int material_ID;

	 /************************************************************************/
	 /* 整个场景 建筑物                                                                     */
	 /************************************************************************/
	 QString buildingName;
	 vector<building> total_Buildings;  //整体模型
	 Vector3d MaxPoint,MinPoint;
	 bool modelFlag;//是否导入建筑物
	 QStringList Scene2DInfoFile_paths;//建筑物地面
	 QStringList SceneHeightInfoFile_paths;//建筑物高度
	 QString ScenePlaneHeightInfoFile_path;//地面海拔

	 /************************************************************************/
	 /* 局部场景 三角面片                                                                     */
	 /************************************************************************/
	 QString objName;
	 QString OBJFile_path;
	 emxModel * triangleModel;//局部模型，存储obj模型或者建筑物加地面的三角面片,局部模型
	 bool localFlag;//是否导入局部场景或者生成局部场景


	 QString Scene2DInfoFile_path;//临时变量
	 QString SceneHeightInfoFile_path;//临时变量

	 //海拔数据处理
	 //bool heightLoaded;  //海拔数据是否已经导入
	 vector<GridHeight> heightR;

	 vector<int> rowNum,colNum;//海拔文件的行列数
	 vector<double> stdLen;//海拔文件的间隔
	 vector<double> xmin;//海拔文件的左上角和右下角。
	 vector<double> ymax;

private:

	void init();
	void createActions();


	//读建筑物以及高度
	void ReadScenePlanetFile(const char*filename_2D, const char*filename_Height, string filename_altitude, Vector3d& MaxPoint, Vector3d& MinPoint);



};

#endif // MAINWINDOW_H