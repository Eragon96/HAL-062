/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout * horizontalLayout1;
    QHBoxLayout * horizontalLayout2;
    QPushButton *snapButton;
    QPushButton *playButton;
    QLineEdit *portLineEdit;
    QLineEdit *capsLineEdit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(435, 362);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

        QWidget *horizontalWidget1 = new QWidget(MainWindow);
        horizontalWidget1->setObjectName(QStringLiteral("horizontalWidget1"));

        horizontalLayout1 = new QHBoxLayout(horizontalWidget1);
        horizontalLayout1->setSpacing(0);
        horizontalLayout1->setContentsMargins(11, 11, 11, 11);
        horizontalLayout1->setObjectName(QStringLiteral("horizontalLayout1"));

        snapButton = new QPushButton(horizontalWidget1);
        snapButton->setObjectName(QStringLiteral("playButton"));

        playButton = new QPushButton(horizontalWidget1);
        playButton->setObjectName(QStringLiteral("snapButton"));

        horizontalLayout1->addWidget(snapButton);
        horizontalLayout1->addWidget(playButton);

        QWidget *horizontalWidget2 = new QWidget(MainWindow);
        horizontalWidget2->setObjectName(QStringLiteral("horizontalWidget2"));

        horizontalLayout2 = new QHBoxLayout(horizontalWidget2);
        horizontalLayout2->setSpacing(0);
        horizontalLayout2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout2->setObjectName(QStringLiteral("horizontalLayout2"));

        QLabel *portLabel = new QLabel("Port:");
        portLineEdit = new QLineEdit;
        QLabel *capsLabel = new QLabel("Caps:");
        capsLineEdit = new QLineEdit;

        horizontalLayout2->addWidget(portLabel);
        horizontalLayout2->addWidget(portLineEdit);
        horizontalLayout2->addWidget(capsLabel);
        horizontalLayout2->addWidget(capsLineEdit);

        verticalLayout->addWidget(horizontalWidget1);
        verticalLayout->addWidget(horizontalWidget2);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "HAL-062 stream", 0));
        snapButton->setText(QApplication::translate("MainWindow", "Take Snapshot", 0));
        playButton->setText(QApplication::translate("MainWindow", "Play stream", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOW_H
