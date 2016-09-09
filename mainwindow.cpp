#include "mainwindow.h"

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
}

void  MainWindow::openOutdoorFile()
{
	if (M_outdoorFileDialog==NULL)
	{
		M_outdoorFileDialog=new outdoorFileDialog(this);
	}
	M_outdoorFileDialog->show();
	M_outdoorFileDialog->raise();
	M_outdoorFileDialog->activateWindow();

}

void MainWindow:: createActions()
{
		connect(ui.action_3, SIGNAL(triggered()), this, SLOT(openOutdoorFile()));
}