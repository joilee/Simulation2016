#ifndef PAGES_H
#define PAGES_H
#include<QtGui>
#include <QWidget>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTreeWidget>
#include <QListWidget>
#include <string>
#include <QComboBox>
using namespace std;
/************************************************************************/
/* 
   发射源参数窗口     
	发射源包含天线、基站、雷达。
    参数通过文本的形式导入
	参数列表支持动态添加和删除，每个参数列表支持编辑。
*/
/************************************************************************/
class emitSource:public QWidget
{
	Q_OBJECT
	public:
		emitSource(QWidget* parent =0);		
		double getAngle();
		
	protected:

	private:
		double angleOfNorth;//正北方向在场景坐标系中的phi角度
		QGroupBox *firstGroup;
		QLineEdit * angleEdit;
		QPushButton *loadSitesButton; 
		QTreeWidget *sitesTreewidget;
		QPushButton *loadTransAntennaButton;
		QListWidget * AntennaList;
};

class fieldpoint:public QWidget
{
	Q_OBJECT
public:
	fieldpoint(QWidget* parent=0);

private:
	//数据
	//场景的范围，单位为m
	double fieldXmin,fieldXmax,fieldYmin,fieldYmax,fieldZmin,fieldZmax;

	string RecePoint;

	//左上角x，左上角y
	double leftupX,leftupY;
	//右上角x,右上角y
	double rightbottomX,rightbottomY;
	//预测精度,预测高度。
	double predictPrecision,predictAltitude;

	//布局
	//
	QLineEdit *Xmin,*Xmax,*Ymin,*Ymax,*Zmin,*Zmax;
	QLineEdit *filePath;
	QPushButton * loadReceieverPointFile;
	QLineEdit* leftupXinput,*leftupYinput;
	QLineEdit* rightbottomXinput,*rightbottomYinput;
	QLineEdit* Precisioninput,*Altitudeinput;
};

class simuArgument:public QWidget
{
	Q_OBJECT
public:
	simuArgument(QWidget* parent=0);



private:

	double  reflectNum;
	double  refractNum;
	double  diffractionNum;
	bool isDiffraction;

	QLineEdit* lineEdit_RT_ReflectCount;
	QLineEdit* lineEdit_RT_RefractCount;
	QComboBox * comboBox_diffraction;
	QLineEdit* lineEdit_RT_Diffraction;

};

#endif