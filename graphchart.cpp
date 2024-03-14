#include "graphchart.h"
#include "ui_graphchart.h"

GraphChart::GraphChart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphChart)
{
    ui->setupUi(this);

    //Объявим Chart
     graphClass = new GraphChart(NUM_GRAPHS);
     chart = new QChart();
     chartView = new QChartView(chart);
    connect(this, &GraphChart::sig_GraphPrintSlot,this,&GraphChart::GraphPrintSlot);


}

void GraphChart::GraphPrintSlot(QChart* chart){
}
void GraphChart::CountStatisticMonth(){

}
void GraphChart::CountStatisticYear(){

}
GraphChart::GraphChart(uint numb){
   numGraph = numb;
   ptrGraph.resize(numGraph);
   for (uint i = 0;i < numGraph; ++i ){
       ptrGraph[i] = new QLineSeries(this);
   }
}
void GraphChart::AddToraph(QVector<uint> x , QVector<uint> y, uint num){
    uint size = 0;
    if(x.size() >= y.size()){
        size = y.size();}
    else{
        size = x.size();}
    for(int i = 0; i < size; i++){
        ptrGraph[num]->append(x[i],y[i]);
    }
}
void GraphChart::ClearGraph(QChart *chart){
    for(uint i = 0; i < numGraph; ++i){
        ptrGraph[i]->clear();
        chart->removeSeries(ptrGraph[i]);
    }
}
void GraphChart::UpdateGraph(QChart *chart){
    for(uint i = 0;i < numGraph;++i){
        chart->addSeries(ptrGraph[i]);
    }
}

GraphChart::~GraphChart()
{
    delete ui;
}
