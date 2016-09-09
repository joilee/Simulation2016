/********************************************************************************
** Form generated from reading UI file 'outdoorFile.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OUTDOORFILE_H
#define UI_OUTDOORFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_outdoorFile
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBox;
    QPushButton *materialButton;
    QPushButton *pushButton_2;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *checkBox_2;
    QPushButton *buildingButton;
    QPushButton *pushButton_6;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *checkBox_4;
    QPushButton *heightButton;
    QPushButton *pushButton_10;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkBox_3;
    QPushButton *altitudeButton;
    QPushButton *pushButton_4;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_7;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton_8;

    void setupUi(QDialog *outdoorFile)
    {
        if (outdoorFile->objectName().isEmpty())
            outdoorFile->setObjectName(QStringLiteral("outdoorFile"));
        outdoorFile->resize(321, 370);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(outdoorFile->sizePolicy().hasHeightForWidth());
        outdoorFile->setSizePolicy(sizePolicy);
        layoutWidget = new QWidget(outdoorFile);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 281, 251));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(layoutWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        checkBox = new QCheckBox(groupBox);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        horizontalLayout->addWidget(checkBox);

        materialButton = new QPushButton(groupBox);
        materialButton->setObjectName(QStringLiteral("materialButton"));

        horizontalLayout->addWidget(materialButton);

        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addWidget(groupBox);

        groupBox_3 = new QGroupBox(layoutWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_3);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        checkBox_2 = new QCheckBox(groupBox_3);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));

        horizontalLayout_3->addWidget(checkBox_2);

        buildingButton = new QPushButton(groupBox_3);
        buildingButton->setObjectName(QStringLiteral("buildingButton"));

        horizontalLayout_3->addWidget(buildingButton);

        pushButton_6 = new QPushButton(groupBox_3);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        horizontalLayout_3->addWidget(pushButton_6);


        verticalLayout->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(layoutWidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        horizontalLayout_5 = new QHBoxLayout(groupBox_4);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        checkBox_4 = new QCheckBox(groupBox_4);
        checkBox_4->setObjectName(QStringLiteral("checkBox_4"));

        horizontalLayout_5->addWidget(checkBox_4);

        heightButton = new QPushButton(groupBox_4);
        heightButton->setObjectName(QStringLiteral("heightButton"));

        horizontalLayout_5->addWidget(heightButton);

        pushButton_10 = new QPushButton(groupBox_4);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));

        horizontalLayout_5->addWidget(pushButton_10);


        verticalLayout->addWidget(groupBox_4);

        groupBox_2 = new QGroupBox(layoutWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        checkBox_3 = new QCheckBox(groupBox_2);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));

        horizontalLayout_2->addWidget(checkBox_3);

        altitudeButton = new QPushButton(groupBox_2);
        altitudeButton->setObjectName(QStringLiteral("altitudeButton"));

        horizontalLayout_2->addWidget(altitudeButton);

        pushButton_4 = new QPushButton(groupBox_2);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        horizontalLayout_2->addWidget(pushButton_4);


        verticalLayout->addWidget(groupBox_2);

        layoutWidget1 = new QWidget(outdoorFile);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(130, 310, 164, 31));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        pushButton_7 = new QPushButton(layoutWidget1);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));

        horizontalLayout_4->addWidget(pushButton_7);

        horizontalSpacer_4 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        pushButton_8 = new QPushButton(layoutWidget1);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));

        horizontalLayout_4->addWidget(pushButton_8);


        retranslateUi(outdoorFile);

        QMetaObject::connectSlotsByName(outdoorFile);
    } // setupUi

    void retranslateUi(QDialog *outdoorFile)
    {
        outdoorFile->setWindowTitle(QApplication::translate("outdoorFile", "Dialog", 0));
        groupBox->setTitle(QApplication::translate("outdoorFile", "\345\257\274\345\205\245\346\235\220\350\264\250\346\226\207\344\273\266", 0));
        checkBox->setText(QApplication::translate("outdoorFile", "\347\212\266\346\200\201", 0));
        materialButton->setText(QApplication::translate("outdoorFile", "\346\211\223\345\274\200", 0));
        pushButton_2->setText(QApplication::translate("outdoorFile", "\345\210\240\351\231\244", 0));
        groupBox_3->setTitle(QApplication::translate("outdoorFile", "\345\257\274\345\205\245\345\273\272\347\255\221\347\211\251\346\226\207\344\273\266", 0));
        checkBox_2->setText(QApplication::translate("outdoorFile", "\347\212\266\346\200\201", 0));
        buildingButton->setText(QApplication::translate("outdoorFile", "\346\211\223\345\274\200", 0));
        pushButton_6->setText(QApplication::translate("outdoorFile", "\345\210\240\351\231\244", 0));
        groupBox_4->setTitle(QApplication::translate("outdoorFile", "\345\257\274\345\205\245\345\273\272\347\255\221\347\211\251\351\253\230\345\272\246\346\226\207\344\273\266", 0));
        checkBox_4->setText(QApplication::translate("outdoorFile", "\347\212\266\346\200\201", 0));
        heightButton->setText(QApplication::translate("outdoorFile", "\346\211\223\345\274\200", 0));
        pushButton_10->setText(QApplication::translate("outdoorFile", "\345\210\240\351\231\244", 0));
        groupBox_2->setTitle(QApplication::translate("outdoorFile", "\345\257\274\345\205\245\346\265\267\346\213\224\346\226\207\344\273\266", 0));
        checkBox_3->setText(QApplication::translate("outdoorFile", "\347\212\266\346\200\201", 0));
        altitudeButton->setText(QApplication::translate("outdoorFile", "\346\211\223\345\274\200", 0));
        pushButton_4->setText(QApplication::translate("outdoorFile", "\345\210\240\351\231\244", 0));
        pushButton_7->setText(QApplication::translate("outdoorFile", "OK", 0));
        pushButton_8->setText(QApplication::translate("outdoorFile", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class outdoorFile: public Ui_outdoorFile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OUTDOORFILE_H
