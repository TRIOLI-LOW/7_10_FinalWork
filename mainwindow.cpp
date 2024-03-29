#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    dataDb = new dbdata(this);
    dataBase = new DataBase(this);


    ui->setupUi(this);
    ui->lb_status->setStyleSheet("color:red");
    ui->pb_getList->setDisabled(true);
    ui->pb_graphPrint->setEnabled(false);
    dataForConnect.resize(NUM_DATA_DB);
    dataBase->AddDB(POSTGRE_DRIVER, DB_NAME);

    connect(dataDb, &dbdata::sig_sendData, this, [&](QVector<QString> receivData){
        dataForConnect = receivData;
    });

        //Соединяем статус с сигналом
    connect(dataBase,&DataBase::sig_SendStatusConnection,this, &MainWindow::ReceiveStatusConnectionDb);
    connect(dataBase,&DataBase::sig_SendStatusRequest, this, &MainWindow::ReceiveStatusRequestToDB);
      // Коннект сигнала для отображения
    //Объявим Chart
     graphClass = new GraphChart(dataBase);
     connect(dataBase, &DataBase::sig_SendDataFromDB, this, &MainWindow::ScreenDataFromDB);
       //

     connect(this,&MainWindow::sig_airportCode,graphClass ,&GraphChart::set_airportCode);


   // Автоматическое подключение
     dataBase->AutoConnect();
    //bool result = dataDb->exec();
    //if (result = QDialog::Accepted){
    //on_a_connectData_triggered();}
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_graphPrint_clicked()
{

  QString airportCode;
  QString airportName = ui->cbox_airportName->currentText();
  for(const auto& code : dataBase->airportNameMap){
      if(code["airportName"] == airportName) {
                 airportCode = code["airportCode"];
                 break;
             }
  }
    emit sig_airportCode(airportCode);
  graphClass->exec();
}

void MainWindow::on_a_addData_triggered(){
    dataDb->show();
}
void MainWindow::on_a_connectData_triggered(){
     //qDebug() << "a_connectData";
    bool dataStatusConnect ;
    auto conn = [&](){ dataStatusConnect  = dataBase->ConnectToDB(dataForConnect);};
        QtConcurrent::run(conn);
    if(dataStatusConnect){
        qDebug() << "Connect";
     };
}
void MainWindow::ReceiveStatusConnectionDb(bool status){
    QTimer* timer = new QTimer(this);
    timer->setInterval(5000);
    connect(timer, &QTimer::timeout, this, &MainWindow::on_a_connectData_triggered);

    if(status){
        timer->stop();
        ui->lb_status->setText("Подключено");
        ui->lb_status->setStyleSheet("color:green");
        auto apNameCon = [&](){dataBase->RequestToDB(requestAirport, airportNameRequest);
                               airportName = dataBase->getAirportNames();
                               ui->cbox_airportName->addItems(airportName);
                               ui->cbox_arrival_departure->addItems(arrival_departure);
                               ui->pb_getList->setEnabled(true);
                               ui->pb_graphPrint->setEnabled(true);
                        };
        //qDebug() << "get airport name __ and append in comboBox" ;
        QtConcurrent::run(apNameCon);
    }
    else{
        ui->lb_status->setText("Отключено");
        ui->lb_status->setStyleSheet("color:red");
        msgBox.setWindowTitle("Ошибка подключения");
        msgBox.setText("Не удалось подключиться к базе данных. Повторить попытку после закрытия окна.");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        if(msgBox.close()){
        timer->start();
        }

    }
}
// -----------------Кнопка "Получить список" ----
void MainWindow::on_pb_getList_clicked()
{
    QString airportCode;
    QString airportName = ui->cbox_airportName->currentText();
    for(const auto& code : dataBase->airportNameMap){
        if(code["airportName"] == airportName) {
                   airportCode = code["airportCode"];
                   break;
               }
    }
    QDate selectDate = ui->de_data->date();

    if (ui->cbox_arrival_departure->currentText() == "Прилёт") {

         QString request = "SELECT flight_no, scheduled_arrival, ad.airport_name->>'ru' as \"Name\" "
                           "from bookings.flights f "
                           "JOIN bookings.airports_data ad on ad.airport_code = f.departure_airport "
                           "where f.arrival_airport  = '" + airportCode + "' "
                           "And DATE(scheduled_arrival) = '"+ selectDate.toString("yyyy-MM-dd") + "'";
                            ;
        auto arrivalRun = [&](){dataBase->ReadAnswerFromDB(request,requestArrivalPlanes);};
        QtConcurrent::run(arrivalRun);
                qDebug()<< "on_pb_clicked_getList_clicked";
    }
    else {
        QString request = "SELECT flight_no, scheduled_departure, ad.airport_name->>'ru' AS \"Name\" "
                          "from bookings.flights f "
                          "JOIN bookings.airports_data ad on ad.airport_code = f.arrival_airport "
                          "WHERE f.departure_airport  = '" + airportCode + "' "
                          "And DATE(scheduled_arrival) = '"+ selectDate.toString("yyyy-MM-dd") + "'";
        auto departureRun = [&](){dataBase->ReadAnswerFromDB(request,requestDeparturePlanes);};
        QtConcurrent::run(departureRun);
                qDebug()<< "on_pb_clicked_getList_clicked";

    }
}
void MainWindow::ScreenDataFromDB(QAbstractItemModel *model, int typeRequest)
{
    switch(typeRequest){
    case requestArrivalPlanes:{
        ui->tableView->setModel(model);
        ui->tableView->show();
         break;}
    case requestDeparturePlanes:{
        ui->tableView->setModel(model);
        ui->tableView->show();
                //qDebug() << "ScreenDataFromDB";
     break;}

        break;
}
}
void MainWindow::ReceiveStatusRequestToDB(QSqlError err, int requestType, QString request){
                //qDebug() << "ReceiveStatusRequestToDB" << requestType ;
    if(err.type() != QSqlError::NoError){
        //msgBox->setText(err.text());
        //msgBox->exec();
    }
    else if(requestType == requestArrivalPlanes){

      dataBase->RequestToDB(requestArrivalPlanes, request);
    }
    else if(requestType == requestDeparturePlanes){

      dataBase->RequestToDB(requestDeparturePlanes, request);
    }

}







