#include "meshOption.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QRegExpValidator>
void meshOptionDialog::getValue(Vector3d &_center,double &_range)
{
	_center=center;
	_range=range;
}
void meshOptionDialog::onOkbutton()
{
	if (centerXLE->text().isEmpty()||centerYLE->text().isEmpty()||centerZLE->text().isEmpty()||rangeLE->text().isEmpty())
	{
		return;
	}
	double x=centerXLE->text().toDouble();
	double y=centerYLE->text().toDouble();
	double z=centerZLE->text().toDouble();
	range=rangeLE->text().toDouble();
	center=Vector3d(x,y,z);
	this->close();
}

meshOptionDialog::meshOptionDialog(QWidget *parent): QDialog(parent) 
{

	QRegExp rx("^[-+]?[0-9]+(\.[0-9]+)?$");  
	QRegExpValidator *pReg = new QRegExpValidator(rx, this);  
	center=Vector3d(0,0,0);
	range=0;
	inputFlag=false;
	centerXLE=new QLineEdit;
	centerXLE->setValidator(pReg);
	centerYLE=new QLineEdit;
	centerYLE->setValidator(pReg);
	centerZLE=new QLineEdit;
	centerZLE->setValidator(pReg);
	rangeLE=new QLineEdit;
	rangeLE->setValidator(new QIntValidator(0,9999999,this));
	this->setWindowTitle(QStringLiteral("剖分选项"));
	okbutton=new QPushButton(QStringLiteral("确定"));
	
	exitbutton=new QPushButton(QStringLiteral("取消"));
	this->setTheLayout();


	createActions();
}
void meshOptionDialog::createActions()
{
	connect(this->okbutton,SIGNAL(clicked()),this,SLOT(onOkbutton()));
	connect(this->exitbutton,SIGNAL(clicked()),this,SLOT(reject()));
}
meshOptionDialog::~meshOptionDialog()
{

}
 void meshOptionDialog::setTheLayout()
{
    firstGroup=new QGroupBox(QStringLiteral("剖分范围"));
	QHBoxLayout *firstLayout=new QHBoxLayout;
	QLabel * label1=new QLabel(QStringLiteral("中心点"));
	QLabel * label2=new QLabel(QStringLiteral("X:"));
	QLabel * label3=new QLabel(QStringLiteral("Y:"));
	QLabel * label4=new QLabel(QStringLiteral("Z:"));
	firstLayout->addWidget(label1);
	firstLayout->addWidget(label2);
	firstLayout->addWidget(centerXLE);
	firstLayout->addWidget(label3);
	firstLayout->addWidget(centerYLE);
	firstLayout->addWidget(label4);
	firstLayout->addWidget(centerZLE);
	
	QLabel * label5=new QLabel(QStringLiteral("剖分范围"));
	QHBoxLayout *secondLayout=new QHBoxLayout;
	secondLayout->addWidget(label5);
	secondLayout->addWidget(rangeLE);
	QVBoxLayout *v1=new QVBoxLayout;
	v1->addLayout(firstLayout);
	v1->addLayout(secondLayout);
	firstGroup->setLayout(v1);

	QHBoxLayout *thirdlayout=new QHBoxLayout;
	thirdlayout->addWidget(okbutton);
	thirdlayout->addWidget(exitbutton);
	thirdlayout->setAlignment(Qt::AlignRight);



	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(firstGroup);
	mainLayout->addLayout(thirdlayout);
	setLayout(mainLayout);
}