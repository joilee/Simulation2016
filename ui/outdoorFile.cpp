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
			QMessageBox::warning(this, QString::fromLocal8Bit("��ò����ļ�·��"),QString::fromLocal8Bit("���ȵ��벢�༭�������ճ����������������"));
			return NULL;
		}
		return O_material_path;
}

QStringList   outdoorFileDialog::getScene2DPath()
{
	if(O_Scene2DInfoFile_paths.isEmpty())
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("��ý������ļ�·��"),QString::fromLocal8Bit("���ȵ��뽨�����ļ���"));
		return QStringList();
	}
	return O_Scene2DInfoFile_paths;
}

QStringList  outdoorFileDialog::getSceneHeightPath()
{
	if (O_SceneHeightInfoFile_paths.isEmpty())
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("��ý�����߶��ļ�·��"),QString::fromLocal8Bit("���ȵ��뽨�����ļ���"));
		return QStringList();
	}
	return O_SceneHeightInfoFile_paths;
}

QString outdoorFileDialog::getPlanePath()
{
	if(O_ScenePlaneHeightInfoFile_path.isEmpty())
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("��ú����ļ�·��"),QString::fromLocal8Bit("���ȵ��뺣�����ļ���"));
		return NULL;
	}
	return O_ScenePlaneHeightInfoFile_path;
}

void outdoorFileDialog::openMaterialFile()
{
	QString path = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("�򿪲����ļ�"),"./",QString::fromLocal8Bit("txt �����ļ� (*.txt)"));
	if (path.isEmpty())
		return;
	O_material_path  = path;  //���浱ǰ�����ļ�·�����Ա�����Բ����ļ��ĸ��²���

}


void outdoorFileDialog::openBuildingVector()
{
	QStringList paths = QFileDialog::getOpenFileNames(this,QString::fromLocal8Bit("���볡��vector�ļ�"),"./",QString::fromLocal8Bit(" ������ά��Ϣ�ļ� "));
	if (paths.isEmpty())
		return;
	O_Scene2DInfoFile_paths = paths;
}

void outdoorFileDialog:: openHeight()
{
	QStringList paths = QFileDialog::getOpenFileNames(this,QString::fromLocal8Bit("���볡��vector�ļ�"),"./",QString::fromLocal8Bit(" �����߶���Ϣ�ļ�"));
	if (paths.isEmpty())
		return;
	O_SceneHeightInfoFile_paths = paths;
}

void outdoorFileDialog::openPlane()
{
	QString path = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("������溣�� raster�ļ�"),"./",QString::fromLocal8Bit(" �������溣����Ϣ�ļ�"));
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