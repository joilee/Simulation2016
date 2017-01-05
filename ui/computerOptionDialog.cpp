#include "computerOptionDialog.h"
#include <iostream>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include<QListWidget>
#include <QMessageBox>
#include <fstream>

computerOptionDialog::computerOptionDialog(QWidget *parent){

	es=new emitSource;
	fp=new fieldpoint;
	sa=new simuArgument;


	contentsWidget = new QListWidget;
	//layout
	contentsWidget->setMovement(QListView::Static);
	contentsWidget->setMaximumWidth(128);
	contentsWidget->setSpacing(12);
	//
	 pagesWidget = new QStackedWidget;
	 pagesWidget->addWidget(es);
	 pagesWidget->addWidget(fp);
	 pagesWidget->addWidget(sa);

	 //左边的三个list
	 QListWidgetItem *emitSourceList = new QListWidgetItem(contentsWidget);
	 emitSourceList->setText(QStringLiteral("发射源"));
	 emitSourceList->setTextAlignment(Qt::AlignHCenter);
	 emitSourceList->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

	 QListWidgetItem* fieldpointList=new QListWidgetItem(contentsWidget);
	 fieldpointList->setText(QStringLiteral("仿真区域"));
	 fieldpointList->setTextAlignment(Qt::AlignHCenter);
	 fieldpointList->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

	 QListWidgetItem* simuArgumentList=new QListWidgetItem(contentsWidget);
	 simuArgumentList->setText(QStringLiteral("仿真参数"));
	 simuArgumentList->setTextAlignment(Qt::AlignHCenter);
	 simuArgumentList->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

	 connect(contentsWidget,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this,SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));



	 //设定初始row
	 contentsWidget->setCurrentRow(0);

	  QHBoxLayout *horizontalLayout = new QHBoxLayout;
	  horizontalLayout->addWidget(contentsWidget);
	  horizontalLayout->addWidget(pagesWidget, 1);

	   QVBoxLayout *mainLayout = new QVBoxLayout;
	   mainLayout->addLayout(horizontalLayout);
	    setLayout(mainLayout);
		setWindowTitle(tr("Option"));
}

void computerOptionDialog::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
	//do nothing

	if (!current)
		current = previous;

	pagesWidget->setCurrentIndex(contentsWidget->row(current));

	return;
}



