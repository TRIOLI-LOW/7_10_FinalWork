#include "database.h"

DataBase::DataBase(QObject *parent)
{
    dataBase = new QSqlDatabase();
    simpleQuery = new QSqlQuery();
    queryModel = new QSqlQueryModel();
    qDebug() << "dataBase";


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
       // qDebug() << "Database opened successfully.";
    } else {
        qDebug() << "Failed to open database. Error: " << dataBase->lastError().text();
    }

    emit sig_SendStatusConnection(status);

    return status;
};


void DataBase::ReadAnswerFromDB (QString request, int requestType){
    *simpleQuery = QSqlQuery(request, *dataBase);
    QSqlError err;
    qDebug ()<<"Read Answer" ;
    QString airCode;

    if(simpleQuery->exec(request) == false){
        err = simpleQuery->lastError();
        qDebug() << "Error executing query: " << err.text();
    }
    else{
        while (simpleQuery->next()) {
            QString airportName = simpleQuery->value("airportName").toString();
            QString airportCode = simpleQuery->value("airport_code").toString();

            QMap<QString, QString> airportInfo;
            airportInfo["airportName"] = airportName;
            airportInfo["airportCode"] = airportCode;


            airportNameMap.append(airportInfo);
        }
            qDebug() << "------------------"<< airCode;
            //qDebug()<< airportNameMap;
    }
    qDebug ()<< "Read Answer  ___ emit signals complite";
    emit sig_SendStatusRequest(err, requestType, request);

}
QStringList DataBase::getAirportNames() {
    QStringList airportNames;
    for (const auto& airport : airportNameMap) {
        airportNames.append(airport["airportName"]);
    }
     qDebug()<< "getAirportNames()"<< airportNames;
    return airportNames;
}

void DataBase::RequestToDB(int requestType, QString request){
    //airportCode = "'"+airportCode+"'";
    switch(requestType){
    //case requestAirport:{}
    case requestArrivalPlanes:{
        qDebug() << "RequestToDB ->" <<"case -- requestArrivalPlanes" ;


        queryModel->setQuery(request, *dataBase);
        queryModel->setHeaderData(0,Qt::Horizontal,"Номер рейса");
        queryModel->setHeaderData(1,Qt::Horizontal,"Время вылета");
        queryModel->setHeaderData(2,Qt::Horizontal,"Аэропорт назначения");

        qDebug() << "emit sig_SendDataFromDB --- ";
        emit sig_SendDataFromDB(queryModel, requestArrivalPlanes);
        break;
    }
    case requestDeparturePlanes :{

        qDebug() << "RequestToDB --"<< "case --  requestDeparturePlanes" ;

        queryModel->setQuery(request, *dataBase);
        queryModel->setHeaderData(0,Qt::Horizontal,"Номер рейса");
        queryModel->setHeaderData(1,Qt::Horizontal,"Время вылета");
        queryModel->setHeaderData(2,Qt::Horizontal,"Аэропорт отправления");
        qDebug() << "emit sig_SendDataFromDB->";
        emit sig_SendDataFromDB(queryModel, requestDeparturePlanes);
         break;
    }
    case requestStatisticsMonth :{

    }
    case requestStatisticsDay :{

    }
    break;
    }
}

