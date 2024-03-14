#include "dbdata.h"
#include "database.h"
#include "ui_dbdata.h"

dbdata::dbdata(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dbdata)
{
    ui->setupUi(this);
    data.resize(NUM_DATA_DB);
    ui->le_nameDb->setText("demo");
    ui->le_host->setText("981757-ca08998.tmweb.ru");
    ui->le_login->setText("netology_usr_cpp");
    ui->le_pass->setText("CppNeto3");
    ui->spb_port->setValue(5432);

}

dbdata::~dbdata()
{
    delete ui;
}

void dbdata::on_ok_button_accepted(){
    data[host] = ui->le_host->text();
    data[nameDb] = ui->le_nameDb->text();
    data[login] = ui->le_login->text();
    data[pass] = ui->le_pass->text();
    data[port] = ui->spb_port->text();
    //qDebug() << data;

    emit sig_sendData(data);
};
