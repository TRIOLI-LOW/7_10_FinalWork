#include "database.h"

DataBase::DataBase(QObject *parent)
{
    dataBase = new QSqlDatabase();
    simpleQuery = new QSqlQuery();
    queryModel = new QSqlQueryModel();
    //qDebug() << "dataBase";

}
void DataBase::AutoConnect(){
    dataBase->setHostName("981757-ca08998.tmweb.ru");
    dataBase->setDatabaseName("demo");
    dataBase->setUserName("netology_usr_cpp");
    dataBase->setPassword("CppNeto3");
    dataBase->setPort(5432);
    bool status;
    status = dataBase->open();
    emit sig_SendStatusConnection(status);
}
DataBase::~DataBase()

{
        delete simpleQuery;
        delete queryModel;
        delete tableModel;
        delete dataBase;
}

void DataBase::AddDB(QString driver, QString nameDb){
    *dataBase = QSqlDatabase::addDatabase(driver, nameDb);

     tableModel = new QSqlTableModel(this, *dataBase);

}
void DataBase::DisconnectDB(QString nameDb){
    *dataBase = QSqlDatabase::database(nameDb);
    dataBase->close();
}
// ------------
bool DataBase::ConnectToDB(QVector<QString> dbData){

    dataBase->setHostName(dbData[host]);
    dataBase->setDatabaseName(dbData[nameDb]);
    dataBase->setUserName(dbData[login]);
    dataBase->setPassword(dbData[pass]);
    dataBase->setPort(dbData[port].toInt());
    qDebug() << dbData;

    bool status;
    status = dataBase->open();
    if (status) {
        qDebug() << "Database opened successfully.";
    } else {
        qDebug() << "Failed to open database. Error: " << dataBase->lastError().text();
    }

    emit sig_SendStatusConnection(status);

    return status;
};

// ----------Обработка ошибки при выполнении запроса
void DataBase::ReadAnswerFromDB (QString request, int requestType){
    QSqlError err;
    qDebug ()<<"Read Answer" ;
    if(simpleQuery->exec(request) == false){
        err = simpleQuery->lastError();
        //qDebug() << "Error executing query: " << err.text();
    }
    //Debug ()<< "Read Answer  ___ emit signals complite";
    emit sig_SendStatusRequest(err, requestType, request);

}
//-------------- Получаем код аэропорта
QStringList DataBase::getAirportNames() {
    QStringList airportNames;
    for (const auto& airport : airportNameMap) {
        airportNames.append(airport["airportName"]);
    }
    // qDebug()<< "getAirportNames()"<< airportNames;
    return airportNames;
}

void DataBase::RequestToDB(int requestType, QString request){


    switch(requestType){
    // ---------------- Заполняем мапу названиями и кодом аэропорта
    case requestAirport:{
        *simpleQuery = QSqlQuery(request, *dataBase);
        while (simpleQuery->next()) {
            QString airportName = simpleQuery->value("airportName").toString();
            QString airportCode = simpleQuery->value("airport_code").toString();

            QMap<QString, QString> airportInfo;
            airportInfo["airportName"] = airportName;
            airportInfo["airportCode"] = airportCode;
            airportNameMap.append(airportInfo);
        }
        break;      //qDebug()<< airportNameMap;
    }
        // -------------- Прибывающие
    case requestArrivalPlanes:{
        //qDebug() << "RequestToDB ->" <<"case -- requestArrivalPlanes" ;

        queryModel->setQuery(request, *dataBase);
        queryModel->setHeaderData(0,Qt::Horizontal,"Номер рейса");
        queryModel->setHeaderData(1,Qt::Horizontal,"Время вылета");
        queryModel->setHeaderData(2,Qt::Horizontal,"Аэропорт назначения");

        //qDebug() << "emit sig_SendDataFromDB --- ";
        emit sig_SendDataFromDB(queryModel, requestArrivalPlanes);
        break;
    }
     // ------------------- Убывающие
    case requestDeparturePlanes :{
        qDebug() << "RequestToDB --"<< "case --  requestDeparturePlanes" ;

        queryModel->setQuery(request, *dataBase);
        queryModel->setHeaderData(0,Qt::Horizontal,"Номер рейса");
        queryModel->setHeaderData(1,Qt::Horizontal,"Время вылета");
        queryModel->setHeaderData(2,Qt::Horizontal,"Аэропорт отправления");
        //qDebug() << "emit sig_SendDataFromDB->";
        emit sig_SendDataFromDB(queryModel, requestDeparturePlanes);
         break;
    }
        //---------Добавляем в мапу из запроса статистики года
    case requestStatisticsYear :{
        //queryModel->setQuery(request, *dataBase);
        //qDebug() << request;
        *simpleQuery = QSqlQuery(request, *dataBase);
        QVector<QMap<QString, QString>> dataYear;
        while(simpleQuery->next()){
            QString month = simpleQuery->value("Month").toString();
            QString flightCount  = simpleQuery->value(0).toString();

            QMap<QString, QString> monthData;
            monthData["Month"] = month;
            monthData["FlightCount"] = flightCount;

            dataYear.append(monthData);
        }

        emit sig_SendDataFromGraph(requestStatisticsYear, dataYear);
       // qDebug()  <<" emit  && dataYear ===" << dataYear;
        break;
    }
        //---------Добавляем в мапу из запроса статистики месяца
    case requestStatisticsMonth :{
       // queryModel->setQuery(request, *dataBase);
        //qDebug() << request;
        *simpleQuery = QSqlQuery(request, *dataBase);
        QVector<QMap<QString, QString>> dataMonth;
        while(simpleQuery->next()){
            QString day = simpleQuery->value("Day").toString();
            QString flightCount  = simpleQuery->value(0).toString();

            QMap<QString, QString> dayData;
            dayData["Day"] = day;
            dayData["FlightCount"] = flightCount;

            dataMonth.append(dayData);
        }

        qRegisterMetaType<QVector<QMap<QString, QString>>>("QVector<QMap<QString, QString>>");
       // qDebug()  <<"dataYear =" << dataMonth;
        emit sig_SendDataFromGraph(requestStatisticsMonth, dataMonth);
        qDebug() << "emit sig_SendDataFromGraph";
        break;
    }
    break;
    }
}

