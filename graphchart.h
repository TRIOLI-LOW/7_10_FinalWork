#ifndef GRAPHCHART_H
#define GRAPHCHART_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtConcurrent>
#include <QLineSeries>
#include <QtCharts>
#include <QChartView>
#include "database.h"

#include <QSql>
#include <QSqlError>

#define FIRST_GRAPH 0
#define NUM_GRAPHS 1

namespace Ui {
class GraphChart;
}
enum series{
    numBar = 0,
    numLine = 1
};
class GraphChart : public QDialog
{
    Q_OBJECT
public slots:


    void GraphPrintSlot(QChart* chart, int requestType);
    void set_airportCode(QString airPCode){
        airportCode = airPCode;};
    void requestProcess(int index);
    void monthIndexSave(int index);
    void LoadStatistic(int requestType, QVector<QMap<QString, QString>> data);

signals:
    void sig_GraphPrintSlot(QChart* chart, int requestType);

public:
    explicit GraphChart(DataBase* db, QWidget *parent = nullptr);
    ~GraphChart();
    void AddToGraph(QVector<uint> x , QVector<uint> y);
    void UpdateGraph(QChart *chart,int numSeries);
    void ClearGraph (QChart *chart);


private slots:
    void on_tabWidget_tabBarClicked(int index);

private:
    int monthIndex = 0;
    DataBase* dataBase;
    QChart* chart;
    QChartView* chartView;
    GraphChart* graphClass;

    QBarSeries* barSeries;
    QLineSeries* lineSeries;
    uint numGraph;
    Ui::GraphChart *ui;
    QString airportCode;
    QVector<QString> month {    "Январь",
                                "Февраль",
                                "Март",
                                "Апрель",
                                "Май",
                                "Июнь",
                                "Июль",
                                "Август",
                                "Сентябрь",
                                "Октябрь",
                                "Ноябрь",
                                "Декабрь"};

};

#endif // GRAPHCHART_H
