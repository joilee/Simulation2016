#include "mainwindow.h"
#include <QtWidgets/QApplication>
#include <gl/freeglut.h>
#include <QDebug>
int main(int argc, char *argv[])
{
	glutInit(&argc,argv);
	QApplication a(argc, argv);
	a.setStyleSheet("QLineEdit{selection-color:yellow;selection-background-color:rgb(0,0,58);border:1px groove gray;border-radius:5px;}"); //background-color:rgb(255,255,241);color:rgb(127,0,63);
	MainWindow w;
	w.show();
	return a.exec();
}
