#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtConcurrent>
#include "database.h"
#include "dbdata.h"
#include "graphchart.h"
#include <QSqlQueryModel>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void ReceiveStatusConnectionDb(bool status);
    void ReceiveStatusRequestToDB(QSqlError err, int requestType, QString request);
    void ScreenDataFromDB(QAbstractItemModel *model, int typeRequest);


signals:
        void sig_airportCode(QString airPCode);

private slots:

    void on_a_addData_triggered();
    void on_a_connectData_triggered();
    void on_pb_getList_clicked();


    void on_pb_graphPrint_clicked();

private:
    Ui::MainWindow *ui;
    dbdata* dataDb;
    DataBase* dataBase;
    QMessageBox msgBox;

    GraphChart* graphClass;

    QVector<QString> dataForConnect;
    QStringList airportName;
    QStringList arrival_departure = {"Прилёт", "Вылет"};
    QString airportNameRequest = "SELECT airport_name->>'ru' as airportName, airport_code FROM bookings.airports_data";



};
#endif // MAINWINDOW_H
