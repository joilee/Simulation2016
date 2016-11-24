﻿#ifndef  MESHOPTION_H
#define MESHOPTION_H
#include "util/vector.h"
#include <QDialog>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
class meshOptionDialog:public QDialog
{
	Q_OBJECT
public:
	meshOptionDialog(QWidget *parent=0);
	~meshOptionDialog();
public:
	Vector3d center;
	double range;
	bool inputFlag;

private slots:
	void onOkbutton();
public:
	void createActions();
	void setTheLayout();
	void getValue(Vector3d &_center,double &_range);
	QGroupBox * firstGroup;
	QLineEdit *centerXLE;
	QLineEdit *centerYLE;
	QLineEdit *centerZLE;
	QLineEdit *rangeLE;
	QPushButton *okbutton;
	QPushButton* exitbutton;
};



#endif