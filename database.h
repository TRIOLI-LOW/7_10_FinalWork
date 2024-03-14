#ifndef DATABASE_H
#define DATABASE_H

#include <QMainWindow>
#include <QObject>
#include <QTableWidget>
#include <QSql>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QMessageBox>

#define NUM_DATA_DB 5
#define POSTGRE_DRIVER "QPSQL"
#define DB_NAME "MyDB"

enum fieldsForConnect{
    host = 0,
    nameDb = 1,
    login = 2,
    pass = 3,
    port = 4
};
enum requestType{
    requestAirport = 0,
    requestArrivalPlanes = 1,
    requestDeparturePlanes = 2,
    requestStatisticsMonth = 3,
    requestStatisticsDay = 4
};

class DataBase: public QObject
{
    friend class MainWindow;
    Q_OBJECT


public:
    explicit DataBase(QObject *parent = nullptr);
    ~DataBase();

    void AddDB (QString driver, QString nameDb );
    void DisconnectDB(QString nameDb = "");
    bool ConnectToDB(QVector<QString> db_data);
    void RequestToDB(int requestType, QString request);
    void ReadAnswerFromDB(QString request, int requestType);
    QStringList getAirportNames();


signals:
    void sig_SendStatusConnection(bool status);
    void sig_SendDataFromDB(QAbstractItemModel *QAbstractItemModel, int typeR);
    void sig_SendStatusRequest(QSqlError err, int requestType, QString request);


private:
    QVector<QMap<QString,QString>> airportNameMap;
    QSqlDatabase* dataBase;
    QSqlTableModel* tableModel;
    QSqlQueryModel* queryModel;
    QSqlQuery* simpleQuery;



};

#endif // DATABASE_H
