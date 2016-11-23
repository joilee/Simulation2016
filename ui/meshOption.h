#ifndef  MESHOPTION_H
#define MESHOPTION_H
#include "util/vector.h"
#include <QDialog>
#include <QGroupBox>
#include <QLineEdit>

class meshOptionDialog:public QDialog
{
	Q_OBJECT
public:
	meshOptionDialog(QWidget *parent=0);
	~meshOptionDialog();
public:
	Vector3d center;
	int range;

//	
public:
	void setTheLayout();
	void getValue(Vector3d &_center,int &_range);
	QGroupBox * firstGroup;
	QLineEdit *centerXLE;
	QLineEdit *centerYLE;
	QLineEdit *centerZLE;
	QLineEdit *rangeLE;

};



#endif