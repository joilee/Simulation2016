#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include "outdoorFile.h"
#include "computerOptionDialog.h"
class QAction; 

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void openOutdoorFile();
	void computerOption();
	//内部界面控件
private:
	Ui::MainWindowClass ui;
	outdoorFileDialog*  M_outdoorFileDialog;
	computerOptionDialog* M_computeroptionDialog;

	//内部变量
 private:
	 QString material_path;
	 QString Scene2DInfoFile_path;
	 QString SceneHeightInfoFile_path;
	 QString ScenePlaneHeightInfoFile_path;

private:

	void init();
	void createActions();



	/************************************************************************/
	/* QAction variable                                                     */
	/************************************************************************/

};

#endif // MAINWINDOW_H
