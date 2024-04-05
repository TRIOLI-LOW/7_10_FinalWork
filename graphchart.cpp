#include "graphchart.h"
#include "ui_graphchart.h"

GraphChart::GraphChart(DataBase* db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphChart)
{
    ui->setupUi(this);
    dataBase = db;
    //Объявим Chart
     chart = new QChart();
     chartView = new QChartView(chart);
     ui->tabWidget->setTabText(0, "Стастистика за год");
     ui->tabWidget->setTabText(1, "Стастистика за месяц");
    ui->cbox_month->addItems(month);
    qRegisterMetaType<QVector<QMap<QString, QString>>>("QVector<QMap<QString, QString>>");
    connect(dataBase, &DataBase::sig_SendDataFromGraph, this, &GraphChart::LoadStatistic);
    connect(this, &GraphChart::sig_GraphPrintSlot,this,&GraphChart::GraphPrintSlot);
       numGraph = NUM_GRAPHS;
       barSeries = new QBarSeries();
       lineSeries = new QLineSeries();
       //Сигнал передачи ответа запроса.

    connect(ui->tabWidget,&QTabWidget::currentChanged, this, &GraphChart::requestProcess);



}

void GraphChart::GraphPrintSlot(QChart* chartPrint){
    chartView = new QChartView(chartPrint);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->gv_year->setViewport(chartView);
}

void GraphChart::LoadStatistic(int requestType, QVector<QMap<QString, QString>>& data){
            qDebug() << "LoadStatistic ---- open";
    if(requestType == requestStatisticsYear){
        //---------------Заполняем стобиковую диаграмму данными--------------
        QBarSet *barSet = new QBarSet("Колличество полётов");
        for(const auto& it : data){
            int flightCount = it["FlightCount"].toInt();
            *barSet << flightCount;
        }
        barSeries->append(barSet);
        // ----------Заполняем месяцы -------
        QBarCategoryAxis *axis = new QBarCategoryAxis();
        axis->append(month);
        barSeries->attachAxis(axis);
        // ---------добавляем в Chart---------
        chart->addSeries(barSeries);
        chart->addAxis(axis, Qt::AlignBottom);
        chart->setTitle("Статистика загруженности за год");
        chart->setAnimationOptions(QChart::SeriesAnimations);
        chart->createDefaultAxes();
        emit sig_GraphPrintSlot(chart);
        qDebug() << "emit ------ signals for print chart";

    }
    // ------------- Иначе если в месяце ----------
    else if(requestType == requestStatisticsMonth){
        uint i  = 1;
        QVector<uint> y;
        QVector<uint> x;
        for(const auto it: data){
           //------- Создаем вектор Чисел выбранного месяца
            QDate date = QDate::fromString(it["Day"]);
            if(ui->cbox_month->currentIndex() == date.month()){
                    y.append(it["FlightCount"].toUInt());
                      x.append(i++);
            }
            qDebug() << y << x;
        }
        AddToGraph(x,y);
        chart->addSeries(lineSeries);
        chart->setTitle("Статистика загруженности за " + ui->cbox_month->currentText());
        chart->setAnimationOptions(QChart::SeriesAnimations);
        chart->createDefaultAxes();
        emit sig_GraphPrintSlot(chart);

    }

}
void GraphChart::requestProcess(int index){
    if(index == 0){
      QString request = "SELECT count(flight_no), date_trunc('month', scheduled_departure) as \"Month\" "
                        "FROM bookings.flights f "
                        "WHERE (scheduled_departure::date > date('2016-08-31') "
                        "and scheduled_departure::date <= date('2017-08-31')) "
                        "and ( departure_airport = '" + airportCode + "' or arrival_airport = '" + airportCode + "' ) "
                        "group by \"Month\" ";
      auto requestYear = [&](){dataBase->RequestToDB( requestStatisticsYear, request);};
      QtConcurrent::run(requestYear);
      qDebug() << "requestProcess ----" << index << airportCode ;
    }
    else if(index == 1){
      QString request = "SELECT count(flight_no), date_trunc('day', scheduled_departure) as \"Day\" "
                        "from bookings.flights f "
                        "WHERE(scheduled_departure::date > date('2016-08-31') "
                        "and scheduled_departure::date <= date('2017-08-31')) "
                        "and ( departure_airport = '" + airportCode + "' or arrival_airport = '" + airportCode + "' ) "
                        "GROUP BY \"Day\" ";

      auto requestMonth = [&](){dataBase->RequestToDB( requestStatisticsMonth, request);};
      QtConcurrent::run(requestMonth);
      qDebug() << "requestProcess ----" << index << airportCode ;
    }

}
void GraphChart::AddToGraph(QVector<uint> x , QVector<uint> y){
    uint size = 0;
    if(x.size() >= y.size()){
        size = y.size();}
    else{
        size = x.size();}
    for(int i = 0; i < size; i++){
        lineSeries->append(x[i],y[i]);
    }
}
void GraphChart::ClearGraph(QChart *chart){
    for(uint i = 0; i < numGraph; ++i){
        barSeries->clear();
        lineSeries->clear();
        chart->removeSeries(barSeries);
        chart->removeSeries(lineSeries);
    }
}
void GraphChart::UpdateGraph(QChart *chart, int numSeries){
    for(uint i = 0;i < numGraph;++i){
            chart->addSeries(lineSeries);
    }
}

GraphChart::~GraphChart()
{
    delete ui;
}

void GraphChart::on_tabWidget_tabBarClicked(int index)
{

}

