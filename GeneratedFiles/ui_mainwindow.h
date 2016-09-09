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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *action;
    QAction *action_3;
    QAction *action_5;
    QAction *action_6;
    QAction *action_7;
    QAction *action_9;
    QAction *action_2;
    QAction *action_8;
    QAction *action_11;
    QWidget *centralWidget;
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
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser;
    QProgressBar *progressBar;
    QDockWidget *dockWidget_outline;
    QWidget *dockWidgetContents_2;
    QDockWidget *dockWidget_para;
    QWidget *dockWidgetContents_3;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(1024, 768);
        MainWindowClass->setMinimumSize(QSize(1024, 768));
        action = new QAction(MainWindowClass);
        action->setObjectName(QStringLiteral("action"));
        action_3 = new QAction(MainWindowClass);
        action_3->setObjectName(QStringLiteral("action_3"));
        action_5 = new QAction(MainWindowClass);
        action_5->setObjectName(QStringLiteral("action_5"));
        action_6 = new QAction(MainWindowClass);
        action_6->setObjectName(QStringLiteral("action_6"));
        action_7 = new QAction(MainWindowClass);
        action_7->setObjectName(QStringLiteral("action_7"));
        action_9 = new QAction(MainWindowClass);
        action_9->setObjectName(QStringLiteral("action_9"));
        action_2 = new QAction(MainWindowClass);
        action_2->setObjectName(QStringLiteral("action_2"));
        action_8 = new QAction(MainWindowClass);
        action_8->setObjectName(QStringLiteral("action_8"));
        action_11 = new QAction(MainWindowClass);
        action_11->setObjectName(QStringLiteral("action_11"));
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 23));
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
        dockWidget_outputLog->setMinimumSize(QSize(102, 183));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        verticalLayoutWidget = new QWidget(dockWidgetContents);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(40, 10, 961, 144));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        textBrowser = new QTextBrowser(verticalLayoutWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        verticalLayout->addWidget(textBrowser);

        progressBar = new QProgressBar(verticalLayoutWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(24);

        verticalLayout->addWidget(progressBar);

        dockWidget_outputLog->setWidget(dockWidgetContents);
        MainWindowClass->addDockWidget(static_cast<Qt::DockWidgetArea>(8), dockWidget_outputLog);
        dockWidget_outline = new QDockWidget(MainWindowClass);
        dockWidget_outline->setObjectName(QStringLiteral("dockWidget_outline"));
        dockWidget_outline->setMinimumSize(QSize(256, 256));
        dockWidget_outline->setFeatures(QDockWidget::AllDockWidgetFeatures);
        dockWidget_outline->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea|Qt::TopDockWidgetArea);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        dockWidget_outline->setWidget(dockWidgetContents_2);
        MainWindowClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget_outline);
        dockWidget_para = new QDockWidget(MainWindowClass);
        dockWidget_para->setObjectName(QStringLiteral("dockWidget_para"));
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QStringLiteral("dockWidgetContents_3"));
        dockWidget_para->setWidget(dockWidgetContents_3);
        MainWindowClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget_para);

        menuBar->addAction(menuFILE->menuAction());
        menuBar->addAction(menuMesh->menuAction());
        menuBar->addAction(menuComputer->menuAction());
        menuBar->addAction(menuVisualize->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuFILE->addAction(action);
        menuFILE->addSeparator();
        menuFILE->addAction(action_3);
        menuFILE->addSeparator();
        menuFILE->addAction(action_5);
        menuMesh->addAction(action_6);
        menuMesh->addAction(action_7);
        menuMesh->addSeparator();
        menuMesh->addAction(action_9);
        menuComputer->addAction(action_2);
        menuComputer->addSeparator();
        menuComputer->addAction(action_8);
        menuComputer->addSeparator();
        menuComputer->addAction(action_11);

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "\345\256\244\345\206\205\344\277\241\345\217\267\344\273\277\347\234\237", 0));
        action->setText(QApplication::translate("MainWindowClass", "\346\226\260\345\273\272", 0));
        action_3->setText(QApplication::translate("MainWindowClass", "\345\257\274\345\205\245\345\256\244\345\244\226\345\234\272\346\231\257", 0));
        action_5->setText(QApplication::translate("MainWindowClass", "\344\277\235\345\255\230\347\273\223\346\236\234", 0));
        action_6->setText(QApplication::translate("MainWindowClass", "\345\211\226\345\210\206", 0));
        action_7->setText(QApplication::translate("MainWindowClass", "\345\217\226\346\266\210\345\211\226\345\210\206", 0));
        action_9->setText(QApplication::translate("MainWindowClass", "\351\200\211\351\241\271", 0));
        action_2->setText(QApplication::translate("MainWindowClass", "\345\217\221\345\260\204\346\272\220\345\217\202\346\225\260", 0));
        action_8->setText(QApplication::translate("MainWindowClass", "\345\234\272\347\202\271", 0));
        action_11->setText(QApplication::translate("MainWindowClass", "\344\273\277\347\234\237\345\217\202\346\225\260", 0));
        menuFILE->setTitle(QApplication::translate("MainWindowClass", "File", 0));
        menuMesh->setTitle(QApplication::translate("MainWindowClass", "Mesh", 0));
        menuComputer->setTitle(QApplication::translate("MainWindowClass", "Computer", 0));
        menuVisualize->setTitle(QApplication::translate("MainWindowClass", "Visualize", 0));
        menuAbout->setTitle(QApplication::translate("MainWindowClass", "About", 0));
        dockWidget_outputLog->setWindowTitle(QApplication::translate("MainWindowClass", "Log", 0));
        dockWidget_outline->setWindowTitle(QApplication::translate("MainWindowClass", "Outline", 0));
        dockWidget_para->setWindowTitle(QApplication::translate("MainWindowClass", "Property", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
