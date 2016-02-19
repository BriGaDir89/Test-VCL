/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QWidget *widgetPlayer;
    QHBoxLayout *horizontalLayout_3;
    QSlider *horizontalSliderProgress;
    QLineEdit *lineEdit;
    QSlider *horizontalSliderVolume;
    QVBoxLayout *verticalLayout;
    QListView *listView;
    QPushButton *buttonOpenFile;
    QPushButton *buttonOpenUrl;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(780, 452);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setBaseSize(QSize(0, 0));
        MainWindow->setLayoutDirection(Qt::LeftToRight);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setLayoutDirection(Qt::LeftToRight);
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetNoConstraint);
        widgetPlayer = new QWidget(centralWidget);
        widgetPlayer->setObjectName(QStringLiteral("widgetPlayer"));
        sizePolicy.setHeightForWidth(widgetPlayer->sizePolicy().hasHeightForWidth());
        widgetPlayer->setSizePolicy(sizePolicy);
        widgetPlayer->setMinimumSize(QSize(0, 0));
        widgetPlayer->setSizeIncrement(QSize(0, 0));
        widgetPlayer->setLayoutDirection(Qt::LeftToRight);
        widgetPlayer->setAutoFillBackground(false);
        widgetPlayer->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));

        verticalLayout_2->addWidget(widgetPlayer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSliderProgress = new QSlider(centralWidget);
        horizontalSliderProgress->setObjectName(QStringLiteral("horizontalSliderProgress"));
        horizontalSliderProgress->setMaximum(1000);
        horizontalSliderProgress->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(horizontalSliderProgress);

        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setMaximumSize(QSize(40, 16777215));
        lineEdit->setStyleSheet(QStringLiteral("background-color: transparent;"));
        lineEdit->setFrame(false);

        horizontalLayout_3->addWidget(lineEdit);

        horizontalSliderVolume = new QSlider(centralWidget);
        horizontalSliderVolume->setObjectName(QStringLiteral("horizontalSliderVolume"));
        horizontalSliderVolume->setMaximumSize(QSize(60, 16777215));
        horizontalSliderVolume->setMaximum(200);
        horizontalSliderVolume->setValue(200);
        horizontalSliderVolume->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(horizontalSliderVolume);


        verticalLayout_2->addLayout(horizontalLayout_3);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        listView = new QListView(centralWidget);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setMaximumSize(QSize(200, 16777215));

        verticalLayout->addWidget(listView);

        buttonOpenFile = new QPushButton(centralWidget);
        buttonOpenFile->setObjectName(QStringLiteral("buttonOpenFile"));
        buttonOpenFile->setMaximumSize(QSize(200, 16777215));

        verticalLayout->addWidget(buttonOpenFile);

        buttonOpenUrl = new QPushButton(centralWidget);
        buttonOpenUrl->setObjectName(QStringLiteral("buttonOpenUrl"));
        buttonOpenUrl->setMaximumSize(QSize(200, 16777215));

        verticalLayout->addWidget(buttonOpenUrl);


        horizontalLayout->addLayout(verticalLayout);


        horizontalLayout_2->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        lineEdit->setText(QApplication::translate("MainWindow", "Volume", 0));
        buttonOpenFile->setText(QApplication::translate("MainWindow", "Add from file...", 0));
        buttonOpenUrl->setText(QApplication::translate("MainWindow", "Add from URL...", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
