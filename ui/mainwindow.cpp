#include "mainwindow.h"
#include <QtWidgets/QFileDialog>
#include <QInputDialog>
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	init();
	createActions();
}

MainWindow::~MainWindow()
{

}

void MainWindow::init()
{
	M_outdoorFileDialog=new outdoorFileDialog(this);
	M_computeroptionDialog=new computerOptionDialog(this);
	bip=new BuildingInfoPage(this);
	lpg=new localPage(this);
	mod=new meshOptionDialog(this);
	//场景数据初始化
	 MaxPoint=Vector3d(-INFINITY,-INFINITY,-INFINITY);
	 MinPoint=Vector3d(INFINITY,INFINITY,INFINITY);

	triangleModel=NULL;
	total_Buildings.clear();
	modelFlag=false;
	localFlag=false;
	material_ID=10;//默认是混凝土文件

	//左侧目录
	ui.treeWidget_project->setHeaderLabels(QStringList()<<QStringLiteral("项目")<<QStringLiteral("属性")); 
	modelTW = new QTreeWidgetItem(QStringList()<<QStringLiteral("模型"));
	computeTW = new QTreeWidgetItem(QStringList()<<QStringLiteral("电磁算法"));
	visualTW = new QTreeWidgetItem(QStringList()<<QStringLiteral("可视化"));
	ui.treeWidget_project->addTopLevelItem(modelTW);
	ui.treeWidget_project->addTopLevelItem(computeTW);
	ui.treeWidget_project->addTopLevelItem(visualTW);

	ui.stackedWidget_Info->addWidget(bip);
	ui.stackedWidget_Info->addWidget(lpg);
	ui.progressBar->setRange(0,100);
}

void  MainWindow::openOutdoorFile()
{
	if (M_outdoorFileDialog==NULL)
	{
		M_outdoorFileDialog=new outdoorFileDialog(this);
	}
	M_outdoorFileDialog->exec();

}
void MainWindow::computerOption()
{
	if (M_computeroptionDialog==NULL)
	{
		M_computeroptionDialog=new computerOptionDialog(this);
	}
	M_computeroptionDialog->exec();
}

void MainWindow::setProgress(int value)
{
	ui.progressBar->setValue(value);
}
void MainWindow:: createActions()
{
		connect(ui.action_3, SIGNAL(triggered()), this, SLOT(openOutdoorFile()));
		connect(ui.computerOption,SIGNAL(triggered()),this,SLOT(computerOption()));
		connect(M_outdoorFileDialog,SIGNAL(fileIsOK(QString,QStringList,QStringList ,QString )),this,SLOT(loadAllFile(QString,QStringList ,QStringList ,QString )));
		connect(ui.action_ShowAll,SIGNAL(triggered()),this,SLOT(showAll()));
		connect(ui.action_localscene,SIGNAL(triggered()),this,SLOT(showLocal()));
		connect(ui.action_obj,SIGNAL(triggered()),this,SLOT(loadObj()));
		connect(ui.action_9,SIGNAL(triggered()),this,SLOT(setMaterial()));
		connect(ui.action_matFile,SIGNAL(triggered()),this,SLOT(open_material()));
		connect(ui.tabWidget_Dispaly,SIGNAL(currentChanged(int)),ui.stackedWidget_Info,SLOT(setCurrentIndex(int)));
		connect(ui.action_6,SIGNAL(triggered()),this,SLOT(setMeshOption()));
		connect(ui.action_startMesh,SIGNAL(triggered()),this,SLOT(meshAll()));
}

void MainWindow::open_material()
{
	setProgress(0);
	QString path = QFileDialog::getOpenFileName(this,QStringLiteral("打开材质文件"),"./",QStringLiteral("txt 材质文件 (*.txt)"));
	if (path.isEmpty())
	{
		outputLog(QStringLiteral("材料路径错误！"));
		return;
	}
	material_path=path;
	materialdatabase.clear();  //存放材质属性的vector容器
	setProgress(10);
	ifstream infile((path.toStdString()).c_str(),ios::in|ios::_Nocreate);
	if(!infile)
	{
		return;
	}
	string str;
	getline(infile,str);
	string unit;
	string sub_name; //创建String对象，调用默认构造函数初始化为空字符串
	while(getline(infile,str))
	{
		material new_material;
		istringstream linestream(str);
		linestream>>new_material.Id;
		linestream>>sub_name;
		while (sub_name != "thickness:")
		{
			sub_name = " "+ sub_name;
			new_material.name += sub_name;
			linestream>>sub_name;
		}
		linestream>>new_material.thickness>>unit>>new_material.color.r>>new_material.color.g>>new_material.color.b>>new_material.frequency>>new_material.dielectric>>new_material.permeability>>new_material.conductivity>>new_material.Transmission_Loss>>new_material.Reflection_Loss;
		if (unit == "m.\"")
		{
		}
		else if(unit == "cm.\"")
		{
			new_material.thickness/=100;
		}
		else if (unit == "mm.\"")
		{
			new_material.thickness/=1000;
		}
		materialdatabase.push_back(new_material);
		setProgress(70);
	}
	infile.close();
	setProgress(100);
	outputLog(QStringLiteral("成功加载材质文件!"));
}
void MainWindow::setMaterial()
{
	bool ok;
	int i = QInputDialog::getInt(this, QStringLiteral("材质信息"),
		QStringLiteral("编号:"), 10, 0, 78, 1, &ok);
	if (ok)
		material_ID=i;
	outputLog(QString(QStringLiteral("设置材质编号为：")+QString::number(material_ID,10)));
}

/************************************************************************/
/* 根据路径，读取文件，存放到对应的变量中                                                                     */
/************************************************************************/
void MainWindow::loadAllFile(QString _name,QStringList _v,QStringList _h,QString _p){
	setProgress(0);
	buildingName=_name;
	Scene2DInfoFile_paths=_v;
	SceneHeightInfoFile_paths=_h;
	ScenePlaneHeightInfoFile_path=_p;
	if (ScenePlaneHeightInfoFile_path.isEmpty())
	{
		QMessageBox::warning(this, QStringLiteral("文件导入"), QStringLiteral("请先导入海拔信息文件"));
		return;
	}
	if (Scene2DInfoFile_paths.isEmpty())
	{
		QMessageBox::warning(this, QStringLiteral("文件导入"),QStringLiteral("请先导入建筑物二维信息文件"));
		return;
	}
	if (SceneHeightInfoFile_paths.isEmpty())
	{
		QMessageBox::warning(this, QStringLiteral("文件导入"),QStringLiteral("请先导入建筑物高度信息文件"));
		return;
	}
	setProgress(10);
	//场景地面海拔文件读取
	readHeightGrid(ScenePlaneHeightInfoFile_path.toStdString(),heightR,rowNum,colNum,stdLen,xmin,ymax);
	setProgress(50);
#ifdef PRINT_MODE
	cout<<"读海拔文件完毕"<<endl;
#endif

	for (int i = 0; i < Scene2DInfoFile_paths.size();i++)
	{
		Scene2DInfoFile_path = Scene2DInfoFile_paths.at(i);
		SceneHeightInfoFile_path = SceneHeightInfoFile_paths.at(i);
		ReadScenePlanetFile(Scene2DInfoFile_path.toStdString().c_str(),SceneHeightInfoFile_path.toStdString().c_str(),ScenePlaneHeightInfoFile_path.toStdString(),MaxPoint,MinPoint);
	}
	setProgress(90);
	//cout<<"buildings num:"<<total_Buildings.size()<<endl;
	//cout<<"MinPoint:"<<MinPoint.x<<" "<<MinPoint.y<<" "<<MinPoint.z<<endl;
	//cout<<"MaxPoint:"<<MaxPoint.x<<" "<<MaxPoint.y<<" "<<MaxPoint.z<<endl;
	modelFlag=true;
	setModelName(0,_name);
	outputLog(QStringLiteral("已经导入整个场景"));
	bip->setValue(total_Buildings.size(),-1,MinPoint,MaxPoint);

	setProgress(100);
}

void MainWindow::outputLog(QString source)
{
	ui.textBrowser->append(source);
}
//index==0为城市场景 index==1为obj
void MainWindow::setModelName(int index,QString name)
{
	 QTreeWidgetItem *child;  
	 QStringList columItemList;
	 if (index==0)
	 {
		 columItemList<<QStringLiteral("城市场景")<<name;
	 }else if (index==1)
	 {
		 columItemList<<QStringLiteral("局部场景")<<name;
	 }
	 
	 child=new QTreeWidgetItem(columItemList);
	 QTreeWidgetItem* temp=ui.treeWidget_project->itemAt(0,0);
	 temp->addChild(child);
}

void MainWindow::ReadScenePlanetFile(const char*filename_2D, const char*filename_Height, string filename_altitude, Vector3d& MaxPoint, Vector3d& MinPoint)  //filename_2D为二维信息文件，filename_Height为高度信息文件;filename_altitude为海拔信息文件，MaxPoint为场景中最大点坐标，MinPoint为场景中最小点坐标
{
	//场景vector格式文件读取
	ifstream infile1(filename_2D,ios::in|ios::_Nocreate);  
	if(!infile1)
	{
		cout << "can not open file1!" << endl;
		return ;
	}
	ifstream infile2(filename_Height,ios::in|ios::_Nocreate);  
	if(!infile2)
	{
		cout << "can not open file2!" << endl;
		return ;
	}
	string str1,str2;
	infile1.seekg(4,ios::beg);
	infile2.seekg(3,ios::beg);
	while(getline(infile1,str1))
	{
		int building_id1 = 0;
		string sign1 = " ";
		int point_num = 0;
		istringstream linestream1(str1);
		linestream1>>building_id1>>sign1>>point_num;

		int building_id2 = 0;
		string sign2= " ";
		double height = 0;
		getline(infile2,str2);
		istringstream linestream2(str2);
		linestream2>>building_id2>>sign2>>height;

		if (point_num > 0)
		{
			building building_info;
			building_info.height = height;
			
			for (int i = 0; i < point_num; i++)
			{
				double x,y;
				getline(infile1,str1);
				istringstream linestream4(str1);
				linestream4>>x>>y;

				double building_altitude = getPointAltitude(heightR[0],x,y,rowNum[0],colNum[0],stdLen[0],xmin[0],ymax[0]);; //建筑物各个点按照实际获取对应海拔值
				double upper_height = height+building_altitude;
				double under_height = building_altitude;
				building_info.upper_facePoint.push_back(Vector3d(x,y,upper_height));
				MaxPoint = Max(MaxPoint,Vector3d(x,y,upper_height));
				MinPoint = Min(MinPoint,Vector3d(x,y,under_height));
			} 
			total_Buildings.push_back(building_info);	
		}			
	}
	infile1.close();
	infile2.close();
}

/************************************************************************/
/*    展示全部场景                                                                  */
/************************************************************************/
void MainWindow::showAll()
{
	setProgress(0);
	if (!modelFlag)
	{
		QMessageBox::warning(this, QStringLiteral("场景展示"),QStringLiteral("请先导入文件"));
		return;
	}
	outputLog(QStringLiteral("努力加载整个场景中......"));
	ui.ModelView->setMaterial(materialdatabase);
	ui.ModelView->setBuilding(total_Buildings,MaxPoint,MinPoint);
	ui.ModelView->updateMesh();
	ui.ModelView->updateGL();
	setProgress(20);
	outputLog(QStringLiteral("已经显示建筑物场景."));
	setProgress(100);
}

void MainWindow::showLocal()
{
	setProgress(0);
	if (materialdatabase.size()==0)
	{
		QMessageBox::warning(this,  QStringLiteral("场景展示"), QStringLiteral("请先导入并编辑生成最终场景中所需材质属性"));
		return;
	}
	if (!localFlag)
	{
		QMessageBox::warning(this, QStringLiteral("局部场景展示"),QStringLiteral("请先导入文件"));
		return;
	}
	outputLog(QStringLiteral("努力加载局部场景中......"));
	setProgress(0);
	Vector3d MaxPointLocal,MinPointLocal;
	triangleModel->GetBBox(MinPointLocal,MaxPointLocal);
	ui.simuArea->setMaterial(materialdatabase);
	ui.simuArea->setTriangleModel(triangleModel);
	ui.simuArea->updateMesh();
	ui.simuArea->drawTriangleScene=1;
	ui.simuArea->defaultMaterial=material_ID;
	ui.simuArea->updateGL();  //函数updateGL是QT自带的函数
	outputLog(QStringLiteral("已经显示仿真区域"));
}


/************************************************************************/
/* 导入obj文件                                                                     */
/************************************************************************/
void MainWindow::loadObj()
{
	setProgress(0);
	 OBJFile_path = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("打开obj文件"),"./",QString::fromLocal8Bit("obj 文件 (*.obj)"));
	if (OBJFile_path.isEmpty())
		return;
	if (triangleModel)
	{
		delete triangleModel;
	}
	setProgress(10);
	triangleModel = new emxModel(OBJFile_path.toStdString().c_str());
	setProgress(90);
	outputLog(QStringLiteral("成功读取obj文件"));
	if (triangleModel->NumF()>triangleModel->NumMaterialF())
	{
		outputLog(QStringLiteral("材质信息不完整，请在剖分选项中指定统一材料编号"));
	}
	localFlag=true;

	//右侧边栏显示参数
	Vector3d MaxPointLocal,MinPointLocal;
	triangleModel->GetBBox(MinPointLocal,MaxPointLocal);
	lpg->setParametre(triangleModel->NumF(),MinPointLocal,MaxPointLocal);
	setModelName(1,OBJFile_path);
	setProgress(100);
	return;
}

void MainWindow::setMeshOption()
{
	if (mod==NULL)
	{
		mod=new meshOptionDialog(this);
	}
	mod->exec();
}
/************************************************************************/
/* 剖分选中的地面和建筑物                                                                     */
/************************************************************************/
void MainWindow::meshAll()
{
	if (triangleModel->NumF()>0||triangleModel->NumV()>0)
	{
		outputLog(QStringLiteral("局部场景已有模型，请先删除。"));
		return;
	}
	Vector3d center;
	double range;
	//要不要加一个判断，防止错误？
	if (mod->inputFlag)
	{
		mod->getValue(center,range);
	}
	

}