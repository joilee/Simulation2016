﻿#include "computerOptionDialog.h"
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
	 QPushButton *closeButton = new QPushButton(tr("Close"));
	 okButton=new QPushButton(tr("OK"));
	 connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
	 connect(okButton,SIGNAL(clicked()),this,SLOT(getPara()));

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

	  QHBoxLayout *buttonsLayout = new QHBoxLayout;
	  buttonsLayout->addStretch(1);
	   buttonsLayout->addWidget(okButton);
	  buttonsLayout->addWidget(closeButton);

	   QVBoxLayout *mainLayout = new QVBoxLayout;
	   mainLayout->addLayout(horizontalLayout);
	   mainLayout->addLayout(buttonsLayout);
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

void computerOptionDialog::getPara()
{
	globalContext *gctx=globalContext::GetInstance();
	gctx->cptPara->phi=es->getAngle();
	fp->getFieldPoint(gctx->cptPara->leftUpX,gctx->cptPara->leftUpY,gctx->cptPara->rightDownX,gctx->cptPara->rightDownY,gctx->cptPara->precision,gctx->cptPara->altitude);
	sa->getSimuArgu(gctx->cptPara->reflectNumPara,gctx->cptPara->refractNumPara,gctx->cptPara->diffractionNumPara,gctx->cptPara->isDiffractionPara,gctx->cptPara->transIndex,gctx->cptPara->RT_sample,gctx->cptPara->RT_radius,gctx->cptPara->RT_BeamNum);
	QMessageBox::information(this, QStringLiteral("计算参数"), QStringLiteral("参数设置成功"), QMessageBox::Yes , QMessageBox::Yes);
}


