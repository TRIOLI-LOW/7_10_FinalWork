/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *a_addData;
    QAction *a_connectData;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *lb_status;
    QSpacerItem *horizontalSpacer;
    QTableView *tableView;
    QFormLayout *formLayout;
    QComboBox *cbox_airportName;
    QComboBox *cbox_arrival_departure;
    QDateEdit *de_data;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *pb_getList;
    QMenuBar *menubar;
    QMenu *menuFunc;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(386, 389);
        a_addData = new QAction(MainWindow);
        a_addData->setObjectName("a_addData");
        a_connectData = new QAction(MainWindow);
        a_connectData->setObjectName("a_connectData");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        lb_status = new QLabel(centralwidget);
        lb_status->setObjectName("lb_status");

        gridLayout->addWidget(lb_status, 2, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 1, 1, 1);

        tableView = new QTableView(centralwidget);
        tableView->setObjectName("tableView");

        gridLayout->addWidget(tableView, 1, 1, 1, 1);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        cbox_airportName = new QComboBox(centralwidget);
        cbox_airportName->setObjectName("cbox_airportName");

        formLayout->setWidget(0, QFormLayout::SpanningRole, cbox_airportName);

        cbox_arrival_departure = new QComboBox(centralwidget);
        cbox_arrival_departure->setObjectName("cbox_arrival_departure");

        formLayout->setWidget(1, QFormLayout::SpanningRole, cbox_arrival_departure);

        de_data = new QDateEdit(centralwidget);
        de_data->setObjectName("de_data");
        de_data->setDateTime(QDateTime(QDate(2016, 8, 14), QTime(23, 45, 0)));
        de_data->setMaximumDateTime(QDateTime(QDate(2017, 9, 14), QTime(20, 55, 0)));
        de_data->setMinimumDateTime(QDateTime(QDate(2016, 8, 14), QTime(23, 45, 0)));
        de_data->setMinimumDate(QDate(2016, 8, 14));
        de_data->setMaximumTime(QTime(20, 55, 0));

        formLayout->setWidget(2, QFormLayout::LabelRole, de_data);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");

        formLayout->setLayout(3, QFormLayout::LabelRole, verticalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(3, QFormLayout::FieldRole, verticalSpacer);

        pb_getList = new QPushButton(centralwidget);
        pb_getList->setObjectName("pb_getList");

        formLayout->setWidget(4, QFormLayout::LabelRole, pb_getList);


        gridLayout->addLayout(formLayout, 1, 2, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 386, 22));
        menuFunc = new QMenu(menubar);
        menuFunc->setObjectName("menuFunc");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFunc->menuAction());
        menuFunc->addAction(a_addData);
        menuFunc->addAction(a_connectData);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        a_addData->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\321\201\321\202\320\270 \320\264\320\260\320\275\320\275\321\213\320\265", nullptr));
        a_connectData->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\270\321\202\321\214\321\201\321\217", nullptr));
        lb_status->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\320\273\321\216\321\207\320\265\320\275\320\276", nullptr));
        pb_getList->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\273\321\203\321\207\320\270\321\202\321\214 \321\201\320\277\320\270\321\201\320\276\320\272", nullptr));
        menuFunc->setTitle(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\265\320\275\320\270\320\265 \320\272 \320\221\320\224", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
