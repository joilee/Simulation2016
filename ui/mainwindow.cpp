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
	//�������ݳ�ʼ��
	 MaxPoint=Vector3d(-INFINITY,-INFINITY,-INFINITY);
	 MinPoint=Vector3d(INFINITY,INFINITY,INFINITY);

	triangleModel=NULL;
	total_Buildings.clear();
	modelFlag=false;
	localFlag=false;
	material_ID=43;//Ĭ���ǻ������ļ�

	//���Ŀ¼
	ui.treeWidget_project->setHeaderLabels(QStringList()<<QStringLiteral("��Ŀ")<<QStringLiteral("����")); 
	modelTW = new QTreeWidgetItem(QStringList()<<QStringLiteral("ģ��"));
	computeTW = new QTreeWidgetItem(QStringList()<<QStringLiteral("����㷨"));
	visualTW = new QTreeWidgetItem(QStringList()<<QStringLiteral("���ӻ�"));
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
	QString path = QFileDialog::getOpenFileName(this,QStringLiteral("�򿪲����ļ�"),"./",QStringLiteral("txt �����ļ� (*.txt)"));
	if (path.isEmpty())
	{
		outputLog(QStringLiteral("����·������"));
		return;
	}
	material_path=path;
	materialdatabase.clear();  //��Ų������Ե�vector����
	setProgress(10);
	ifstream infile((path.toStdString()).c_str(),ios::in|ios::_Nocreate);
	if(!infile)
	{
		return;
	}
	string str;
	getline(infile,str);
	string unit;
	string sub_name; //����String���󣬵���Ĭ�Ϲ��캯����ʼ��Ϊ���ַ���
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
	outputLog(QStringLiteral("�ɹ����ز����ļ�!"));
}

void MainWindow::setMaterial()
{
	bool ok;
	int i = QInputDialog::getInt(this, QStringLiteral("������Ϣ"),
		QStringLiteral("���:"), 10, 0, 78, 1, &ok);
	if (ok)
		material_ID=i;
	outputLog(QString(QStringLiteral("���ò��ʱ��Ϊ��")+QString::number(material_ID,10)));
}

/************************************************************************/
/* ����·������ȡ�ļ�����ŵ���Ӧ�ı�����                                                                     */
/************************************************************************/
void MainWindow::loadAllFile(QString _name,QStringList _v,QStringList _h,QString _p){
	setProgress(0);
	buildingName=_name;
	Scene2DInfoFile_paths=_v;
	SceneHeightInfoFile_paths=_h;
	ScenePlaneHeightInfoFile_path=_p;
	if (ScenePlaneHeightInfoFile_path.isEmpty())
	{
		QMessageBox::warning(this, QStringLiteral("�ļ�����"), QStringLiteral("���ȵ��뺣����Ϣ�ļ�"));
		return;
	}
	if (Scene2DInfoFile_paths.isEmpty())
	{
		QMessageBox::warning(this, QStringLiteral("�ļ�����"),QStringLiteral("���ȵ��뽨�����ά��Ϣ�ļ�"));
		return;
	}
	if (SceneHeightInfoFile_paths.isEmpty())
	{
		QMessageBox::warning(this, QStringLiteral("�ļ�����"),QStringLiteral("���ȵ��뽨����߶���Ϣ�ļ�"));
		return;
	}
	setProgress(10);
	//�������溣���ļ���ȡ
	readHeightGrid(ScenePlaneHeightInfoFile_path.toStdString(),heightR,rowNum,colNum,stdLen,xmin,ymax);
	setProgress(50);
#ifdef PRINT_MODE
	cout<<"�������ļ����"<<endl;
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
	outputLog(QStringLiteral("�Ѿ�������������"));
	bip->setValue(total_Buildings.size(),-1,MinPoint,MaxPoint);

	setProgress(100);
}

void MainWindow::outputLog(QString source)
{
	ui.textBrowser->append(source);
}
//index==0Ϊ���г��� index==1Ϊobj
void MainWindow::setModelName(int index,QString name)
{
	 QTreeWidgetItem *child;  
	 QStringList columItemList;
	 if (index==0)
	 {
		 columItemList<<QStringLiteral("���г���")<<name;
	 }else if (index==1)
	 {
		 columItemList<<QStringLiteral("�ֲ�����")<<name;
	 }
	 
	 child=new QTreeWidgetItem(columItemList);
	 QTreeWidgetItem* temp=ui.treeWidget_project->itemAt(0,0);
	 temp->addChild(child);
}

void MainWindow::ReadScenePlanetFile(const char*filename_2D, const char*filename_Height, string filename_altitude, Vector3d& MaxPoint, Vector3d& MinPoint)  //filename_2DΪ��ά��Ϣ�ļ���filename_HeightΪ�߶���Ϣ�ļ�;filename_altitudeΪ������Ϣ�ļ���MaxPointΪ�������������꣬MinPointΪ��������С������
{
	//����vector��ʽ�ļ���ȡ
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

				double building_altitude = getPointAltitude(heightR[0],x,y,rowNum[0],colNum[0],stdLen[0],xmin[0],ymax[0]);; //����������㰴��ʵ�ʻ�ȡ��Ӧ����ֵ
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
/*    չʾȫ������                                                                  */
/************************************************************************/
void MainWindow::showAll()
{
	setProgress(0);
	if (!modelFlag)
	{
		QMessageBox::warning(this, QStringLiteral("����չʾ"),QStringLiteral("���ȵ����ļ�"));
		return;
	}
	outputLog(QStringLiteral("Ŭ����������������......"));
	ui.ModelView->setMaterial(materialdatabase);
	ui.ModelView->setBuilding(total_Buildings,MaxPoint,MinPoint);
	ui.ModelView->updateMesh();
	ui.ModelView->updateGL();
	setProgress(20);
	outputLog(QStringLiteral("�Ѿ���ʾ�����ﳡ��."));
	setProgress(100);
}

void MainWindow::showLocal()
{
	setProgress(0);
	if (materialdatabase.size()==0)
	{
		QMessageBox::warning(this,  QStringLiteral("����չʾ"), QStringLiteral("���ȵ��벢�༭�������ճ����������������"));
		return;
	}
	if (!localFlag)
	{
		QMessageBox::warning(this, QStringLiteral("�ֲ�����չʾ"),QStringLiteral("���ȵ����ļ�"));
		return;
	}
	outputLog(QStringLiteral("Ŭ�����ؾֲ�������......"));
	setProgress(0);
	Vector3d MaxPointLocal,MinPointLocal;
	triangleModel->GetBBox(MinPointLocal,MaxPointLocal);
	ui.simuArea->setMaterial(materialdatabase);
	ui.simuArea->setTriangleModel(triangleModel);
	ui.simuArea->updateMesh();
	ui.simuArea->drawTriangleScene=1;
	ui.simuArea->defaultMaterial=material_ID;
	ui.simuArea->updateGL();  //����updateGL��QT�Դ��ĺ���
	outputLog(QStringLiteral("�Ѿ���ʾ��������"));
}


/************************************************************************/
/* ����obj�ļ�                                                                     */
/************************************************************************/
void MainWindow::loadObj()
{
	setProgress(0);
	 OBJFile_path = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("��obj�ļ�"),"./",QString::fromLocal8Bit("obj �ļ� (*.obj)"));
	if (OBJFile_path.isEmpty())
		return;
	if (triangleModel)
	{
		delete triangleModel;
	}
	setProgress(10);
	triangleModel = new emxModel(OBJFile_path.toStdString().c_str());
	setProgress(90);
	outputLog(QStringLiteral("�ɹ���ȡobj�ļ�"));
	if (triangleModel->NumF()>triangleModel->NumMaterialF())
	{
		outputLog(QStringLiteral("������Ϣ�������������ʷ�ѡ����ָ��ͳһ���ϱ��"));
	}
	localFlag=true;

	//�Ҳ������ʾ����
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
/* �ʷ�ѡ�еĵ���ͽ�����                                                                     */
/************************************************************************/
void MainWindow::meshAll()
{
	setProgress(0);
	if (triangleModel!=NULL)
	{
		if (triangleModel->NumV())
		{
			outputLog(QStringLiteral("�ֲ��������е㼯"));
		}
		outputLog(QStringLiteral("�ֲ���������ģ�ͣ�����ɾ����"));
		return;
	}else if (total_Buildings.size()==0)
	{
		outputLog(QStringLiteral("û�е��뽨�����ļ������ȵ�������ļ���"));
		return;
	}
	Vector3d center;
	double range;
	//Ҫ��Ҫ��һ���жϣ���ֹ����
	if (mod->inputFlag)
	{
		mod->getValue(center,range);
	}else
	{
		outputLog(QStringLiteral("û�������ʷֲ���"));
		return;
	}
	setProgress(5);
	vector<building> Local_buildings;
	LocalBuilding(Local_buildings,center, range);
	setProgress(30);
	MESH meshCTX;
	MESH_PTR ground_pMesh = &meshCTX;
	LocalGround( ground_pMesh,center,range);
	setProgress(70);
	triangleModel = new emxModel(Local_buildings, ground_pMesh);
	setProgress(90);
	//�Ҳ������ʾ����
	Vector3d MaxPointLocal,MinPointLocal;
	triangleModel->GetBBox(MinPointLocal,MaxPointLocal);
	localFlag=true;
	lpg->setParametre(triangleModel->NumF(),MinPointLocal,MaxPointLocal);
	setProgress(100);
}
void MainWindow::LocalGround(MESH_PTR pMesh,Vector3d AP_position, double LocalRange)
{
	//�ֲ�����ķ�Χ MinPos��MaxPos
	Vector3d MinPos = AP_position - Vector3d(LocalRange/2, LocalRange/2, 0);
	Vector3d MaxPos = AP_position + Vector3d(LocalRange/2, LocalRange/2, 0);

	//step0 ���������û�ж� û��ȡ�򱨴��˳� 
	if(ScenePlaneHeightInfoFile_path.isEmpty())
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("����չʾ"),QString::fromLocal8Bit("���ȵ��볡���ĺ�����Ϣ�ļ�"));
		return;
	}

	//step1 �ҵ���Ӧ���к���
	int upRow=(ymax[0]-MaxPos[1])/stdLen[0];
	int downRow= (ymax[0]-MinPos[1])/stdLen[0]+1;
	int leftCol=(MinPos[0]-xmin[0])/stdLen[0];
	int rightCol=(MaxPos[0]-xmin[0])/stdLen[0]+1;
	int area[4]={upRow,downRow,leftCol,rightCol};

	//step2 ���оֲ����ļ���ȡ canny�㷨 �ʷ� 
	vector<vector<int> > cannyPoint;//�Ӿֲ��㿪ʼ�ĵ� ����ȫ�ֵ� 
	int nv=0;
	int localRow=downRow-upRow+1;
	int localCol=rightCol-leftCol+1;
	cannyPoint.resize(localRow,vector<int>(localCol));

	height2canny(heightR[0],cannyPoint,rowNum[0],colNum[0],stdLen[0],xmin[0],ymax[0],area);

	int  totalVer=getFeaturePoint3(stepLength,localRow,localCol,cannyPoint);

	InitMesh(pMesh, totalVer);

	int amount=setMeshPtr3( pMesh,stepLength,localRow,localCol,cannyPoint,heightR[0],xmin[0],ymax[0],stdLen[0],upRow,leftCol);

	outputLog(QStringLiteral("���ŵ�ͼ����")+QString::number(nv,10)+QStringLiteral("�����㡣"));
	outputLog(QStringLiteral("��������������")+QString::number(amount-3,10));
	double last_time, this_time;
	last_time = GetTickCount();
	IncrementalDelaunay(pMesh);
	this_time = GetTickCount();

	outputLog(QStringLiteral("�ֲ����潨ģ��������")+QString::number(pMesh->vertex_num,10));
	outputLog(QStringLiteral("�ʷֺ�ʱ")+QString::number((this_time - last_time)/1000)+QStringLiteral("s"));
}

void MainWindow::LocalBuilding(vector< building> &Local_buildings, Vector3d AP_position, double LocalRange)
{
	//�ֲ�����ķ�Χ MinPos��MaxPos
	Vector3d MinPos = AP_position - Vector3d(LocalRange/2, LocalRange/2, 0);
	Vector3d MaxPos = AP_position + Vector3d(LocalRange/2, LocalRange/2, 0);
	for (int buildings_id = 0; buildings_id < total_Buildings.size(); buildings_id++)
	{
		bool in_range = true;
		for (int id = 0; id < total_Buildings[buildings_id].upper_facePoint.size()-1; id++) //��¼building���������ʱ����ĩ���غϣ���¼���Σ�����   .size����-1
		{
			double x1 = total_Buildings[buildings_id].upper_facePoint[id].x - MinPos.x;
			double x2 = total_Buildings[buildings_id].upper_facePoint[id].x - MaxPos.x;
			double y1 = total_Buildings[buildings_id].upper_facePoint[id].y - MinPos.y;
			double y2 = total_Buildings[buildings_id].upper_facePoint[id].y - MaxPos.y;
			if ( !(x1*x2 < 0 && y1*y2 < 0)) //�жϽ������Ƿ����趨��Χ��,��ʹ��һ���㲻�ڷ�Χ�ڣ�Ҳ�ж�Ϊ�����ڲ�
			{
				in_range = false;
				break;
			}
		}
		if (in_range)
		{
			Local_buildings.push_back(total_Buildings[buildings_id]);
		}		
	}
	outputLog(QStringLiteral("����������Ϊ")+QString::number(Local_buildings.size()));
}