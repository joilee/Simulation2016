/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <glWidget.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *action;
    QAction *action_3;
    QAction *action_saveLocal;
    QAction *action_6;
    QAction *action_startMesh;
    QAction *action_9;
    QAction *computerOption;
    QAction *action_8;
    QAction *action_11;
    QAction *action_ShowAll;
    QAction *action_obj;
    QAction *action_matFile;
    QAction *action_localscene;
    QAction *action_loadPlugin;
    QAction *action_deletePlugin;
    QAction *action_run;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget_Dispaly;
    GLWidget *ModelView;
    GLWidget *simuArea;
    QMenuBar *menuBar;
    QMenu *menuFILE;
    QMenu *menuMesh;
    QMenu *menuComputer;
    QMenu *menuVisualize;
    QMenu *menuAbout;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidget_outputLog;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser;
    QProgressBar *progressBar;
    QDockWidget *dockWidget_outline;
    QWidget *dockWidgetContents_2;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QTreeWidget *treeWidget_project;
    QDockWidget *dockWidget_2;
    QWidget *dockWidgetContents_5;
    QVBoxLayout *verticalLayout_3;
    QStackedWidget *stackedWidget_Info;
    QDockWidget *dockWidget_para;
    QWidget *dockWidgetContents_3;
    QVBoxLayout *verticalLayout_6;
    QTreeWidget *treeWidget_para;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(1191, 837);
        MainWindowClass->setMinimumSize(QSize(1024, 768));
        action = new QAction(MainWindowClass);
        action->setObjectName(QStringLiteral("action"));
        action_3 = new QAction(MainWindowClass);
        action_3->setObjectName(QStringLiteral("action_3"));
        action_saveLocal = new QAction(MainWindowClass);
        action_saveLocal->setObjectName(QStringLiteral("action_saveLocal"));
        action_6 = new QAction(MainWindowClass);
        action_6->setObjectName(QStringLiteral("action_6"));
        action_startMesh = new QAction(MainWindowClass);
        action_startMesh->setObjectName(QStringLiteral("action_startMesh"));
        action_9 = new QAction(MainWindowClass);
        action_9->setObjectName(QStringLiteral("action_9"));
        computerOption = new QAction(MainWindowClass);
        computerOption->setObjectName(QStringLiteral("computerOption"));
        action_8 = new QAction(MainWindowClass);
        action_8->setObjectName(QStringLiteral("action_8"));
        action_11 = new QAction(MainWindowClass);
        action_11->setObjectName(QStringLiteral("action_11"));
        action_ShowAll = new QAction(MainWindowClass);
        action_ShowAll->setObjectName(QStringLiteral("action_ShowAll"));
        action_obj = new QAction(MainWindowClass);
        action_obj->setObjectName(QStringLiteral("action_obj"));
        action_matFile = new QAction(MainWindowClass);
        action_matFile->setObjectName(QStringLiteral("action_matFile"));
        action_localscene = new QAction(MainWindowClass);
        action_localscene->setObjectName(QStringLiteral("action_localscene"));
        action_loadPlugin = new QAction(MainWindowClass);
        action_loadPlugin->setObjectName(QStringLiteral("action_loadPlugin"));
        action_deletePlugin = new QAction(MainWindowClass);
        action_deletePlugin->setObjectName(QStringLiteral("action_deletePlugin"));
        action_run = new QAction(MainWindowClass);
        action_run->setObjectName(QStringLiteral("action_run"));
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tabWidget_Dispaly = new QTabWidget(centralWidget);
        tabWidget_Dispaly->setObjectName(QStringLiteral("tabWidget_Dispaly"));
        tabWidget_Dispaly->setTabPosition(QTabWidget::South);
        ModelView = new GLWidget();
        ModelView->setObjectName(QStringLiteral("ModelView"));
        tabWidget_Dispaly->addTab(ModelView, QString());
        simuArea = new GLWidget();
        simuArea->setObjectName(QStringLiteral("simuArea"));
        tabWidget_Dispaly->addTab(simuArea, QString());

        horizontalLayout->addWidget(tabWidget_Dispaly);

        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1191, 23));
        menuFILE = new QMenu(menuBar);
        menuFILE->setObjectName(QStringLiteral("menuFILE"));
        menuMesh = new QMenu(menuBar);
        menuMesh->setObjectName(QStringLiteral("menuMesh"));
        menuComputer = new QMenu(menuBar);
        menuComputer->setObjectName(QStringLiteral("menuComputer"));
        menuVisualize = new QMenu(menuBar);
        menuVisualize->setObjectName(QStringLiteral("menuVisualize"));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        MainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindowClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindowClass->setStatusBar(statusBar);
        dockWidget_outputLog = new QDockWidget(MainWindowClass);
        dockWidget_outputLog->setObjectName(QStringLiteral("dockWidget_outputLog"));
        dockWidget_outputLog->setMinimumSize(QSize(128, 139));
        dockWidget_outputLog->setFeatures(QDockWidget::DockWidgetFloatable);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        verticalLayout_2 = new QVBoxLayout(dockWidgetContents);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        textBrowser = new QTextBrowser(dockWidgetContents);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        verticalLayout->addWidget(textBrowser);

        progressBar = new QProgressBar(dockWidgetContents);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(0);

        verticalLayout->addWidget(progressBar);


        verticalLayout_2->addLayout(verticalLayout);

        dockWidget_outputLog->setWidget(dockWidgetContents);
        MainWindowClass->addDockWidget(static_cast<Qt::DockWidgetArea>(8), dockWidget_outputLog);
        dockWidget_outline = new QDockWidget(MainWindowClass);
        dockWidget_outline->setObjectName(QStringLiteral("dockWidget_outline"));
        dockWidget_outline->setMinimumSize(QSize(256, 300));
        dockWidget_outline->setFeatures(QDockWidget::NoDockWidgetFeatures);
        dockWidget_outline->setAllowedAreas(Qt::LeftDockWidgetArea);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        verticalLayout_5 = new QVBoxLayout(dockWidgetContents_2);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        treeWidget_project = new QTreeWidget(dockWidgetContents_2);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget_project->setHeaderItem(__qtreewidgetitem);
        treeWidget_project->setObjectName(QStringLiteral("treeWidget_project"));

        verticalLayout_4->addWidget(treeWidget_project);


        verticalLayout_5->addLayout(verticalLayout_4);

        dockWidget_outline->setWidget(dockWidgetContents_2);
        MainWindowClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget_outline);
        dockWidget_2 = new QDockWidget(MainWindowClass);
        dockWidget_2->setObjectName(QStringLiteral("dockWidget_2"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dockWidget_2->sizePolicy().hasHeightForWidth());
        dockWidget_2->setSizePolicy(sizePolicy);
        dockWidget_2->setMinimumSize(QSize(250, 56));
        dockWidget_2->setFeatures(QDockWidget::NoDockWidgetFeatures);
        dockWidgetContents_5 = new QWidget();
        dockWidgetContents_5->setObjectName(QStringLiteral("dockWidgetContents_5"));
        verticalLayout_3 = new QVBoxLayout(dockWidgetContents_5);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        stackedWidget_Info = new QStackedWidget(dockWidgetContents_5);
        stackedWidget_Info->setObjectName(QStringLiteral("stackedWidget_Info"));

        verticalLayout_3->addWidget(stackedWidget_Info);

        dockWidget_2->setWidget(dockWidgetContents_5);
        MainWindowClass->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget_2);
        dockWidget_para = new QDockWidget(MainWindowClass);
        dockWidget_para->setObjectName(QStringLiteral("dockWidget_para"));
        dockWidget_para->setMinimumSize(QSize(89, 300));
        dockWidget_para->setFeatures(QDockWidget::DockWidgetFloatable);
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QStringLiteral("dockWidgetContents_3"));
        verticalLayout_6 = new QVBoxLayout(dockWidgetContents_3);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        treeWidget_para = new QTreeWidget(dockWidgetContents_3);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setText(0, QStringLiteral("1"));
        treeWidget_para->setHeaderItem(__qtreewidgetitem1);
        treeWidget_para->setObjectName(QStringLiteral("treeWidget_para"));

        verticalLayout_6->addWidget(treeWidget_para);

        dockWidget_para->setWidget(dockWidgetContents_3);
        MainWindowClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget_para);

        menuBar->addAction(menuFILE->menuAction());
        menuBar->addAction(menuMesh->menuAction());
        menuBar->addAction(menuComputer->menuAction());
        menuBar->addAction(menuVisualize->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuFILE->addAction(action);
        menuFILE->addSeparator();
        menuFILE->addAction(action_matFile);
        menuFILE->addSeparator();
        menuFILE->addAction(action_3);
        menuFILE->addAction(action_obj);
        menuFILE->addSeparator();
        menuFILE->addAction(action_saveLocal);
        menuMesh->addAction(action_6);
        menuMesh->addAction(action_startMesh);
        menuMesh->addSeparator();
        menuMesh->addAction(action_9);
        menuComputer->addAction(computerOption);
        menuComputer->addSeparator();
        menuComputer->addAction(action_loadPlugin);
        menuComputer->addAction(action_deletePlugin);
        menuComputer->addSeparator();
        menuComputer->addAction(action_run);
        menuVisualize->addAction(action_ShowAll);
        menuVisualize->addAction(action_localscene);

        retranslateUi(MainWindowClass);

        tabWidget_Dispaly->setCurrentIndex(1);
        stackedWidget_Info->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "\345\256\244\345\206\205\344\277\241\345\217\267\344\273\277\347\234\237", 0));
        action->setText(QApplication::translate("MainWindowClass", "\346\226\260\345\273\272", 0));
        action_3->setText(QApplication::translate("MainWindowClass", "\345\257\274\345\205\245\345\256\244\345\244\226\345\234\272\346\231\257", 0));
        action_saveLocal->setText(QApplication::translate("MainWindowClass", "\344\277\235\345\255\230\345\261\200\351\203\250\345\234\272\346\231\257", 0));
        action_6->setText(QApplication::translate("MainWindowClass", "\345\211\226\345\210\206\345\217\202\346\225\260", 0));
        action_startMesh->setText(QApplication::translate("MainWindowClass", "\345\211\226\345\210\206", 0));
        action_9->setText(QApplication::translate("MainWindowClass", "\346\235\220\346\226\231\351\200\211\351\241\271", 0));
        computerOption->setText(QApplication::translate("MainWindowClass", "\351\200\211\351\241\271", 0));
        action_8->setText(QApplication::translate("MainWindowClass", "\345\234\272\347\202\271", 0));
        action_11->setText(QApplication::translate("MainWindowClass", "\344\273\277\347\234\237\345\217\202\346\225\260", 0));
        action_ShowAll->setText(QApplication::translate("MainWindowClass", "\346\225\264\344\275\223\345\234\272\346\231\257\345\261\225\347\244\272", 0));
        action_obj->setText(QApplication::translate("MainWindowClass", "\345\257\274\345\205\245obj\346\250\241\345\236\213", 0));
        action_matFile->setText(QApplication::translate("MainWindowClass", "\345\257\274\345\205\245\346\235\220\346\226\231\346\226\207\344\273\266", 0));
        action_localscene->setText(QApplication::translate("MainWindowClass", "\344\273\277\347\234\237\345\214\272\345\237\237\345\261\225\347\244\272", 0));
        action_loadPlugin->setText(QApplication::translate("MainWindowClass", "\345\212\240\350\275\275\347\256\227\346\263\225", 0));
        action_deletePlugin->setText(QApplication::translate("MainWindowClass", "\345\215\270\350\275\275\347\256\227\346\263\225", 0));
        action_run->setText(QApplication::translate("MainWindowClass", "\350\256\241\347\256\227", 0));
        tabWidget_Dispaly->setTabText(tabWidget_Dispaly->indexOf(ModelView), QApplication::translate("MainWindowClass", "\346\250\241\345\236\213\345\234\272\346\231\257", 0));
        tabWidget_Dispaly->setTabText(tabWidget_Dispaly->indexOf(simuArea), QApplication::translate("MainWindowClass", "\344\273\277\347\234\237\345\234\272\346\231\257", 0));
        menuFILE->setTitle(QApplication::translate("MainWindowClass", "File", 0));
        menuMesh->setTitle(QApplication::translate("MainWindowClass", "Mesh", 0));
        menuComputer->setTitle(QApplication::translate("MainWindowClass", "Computer", 0));
        menuVisualize->setTitle(QApplication::translate("MainWindowClass", "Visualize", 0));
        menuAbout->setTitle(QApplication::translate("MainWindowClass", "About", 0));
        dockWidget_outputLog->setWindowTitle(QApplication::translate("MainWindowClass", "Log", 0));
        dockWidget_outline->setWindowTitle(QApplication::translate("MainWindowClass", "\347\233\256\345\275\225", 0));
        dockWidget_para->setWindowTitle(QApplication::translate("MainWindowClass", "\345\217\202\346\225\260", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
