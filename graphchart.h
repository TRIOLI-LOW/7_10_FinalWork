#ifndef GRAPHCHART_H
#define GRAPHCHART_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QLineSeries>
#include <QtCharts>
#include <QChartView>
#include "database.h"

#define FIRST_GRAPH 0
#define NUM_GRAPHS 1

namespace Ui {
class GraphChart;
}

class GraphChart : public QDialog
{
    Q_OBJECT
public slots:
    void CountStatisticMonth();
    void CountStatisticYear();
    void GraphPrintSlot(QChart* chart);
signals:
    void sig_GraphPrintSlot(QChart* chart);

public:
    GraphChart(uint numb);
    explicit GraphChart(QWidget *parent = nullptr);
    ~GraphChart();
    void AddToraph(QVector<uint> x , QVector<uint> y,uint num);
    void UpdateGraph(QChart *chart);
    void ClearGraph (QChart *chart);

private:
    DataBase* dataBase;
    QChart* chart;
    QChartView* chartView;
    GraphChart* graphClass;
    QList <QLineSeries*> ptrGraph;
    uint numGraph;
    Ui::GraphChart *ui;
};

#endif // GRAPHCHART_H
