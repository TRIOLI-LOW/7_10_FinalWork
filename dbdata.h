#ifndef DBDATA_H
#define DBDATA_H

#include <QDialog>

namespace Ui {
class dbdata;
}

class dbdata : public QDialog
{
    Q_OBJECT

public:
    explicit dbdata(QWidget *parent = nullptr);
    ~dbdata();
signals:
     sig_sendData(QVector<QString> dbData);
private slots:
    void on_ok_button_accepted();

private:
    bool firstConn = true;
    Ui::dbdata *ui;
    QVector<QString> data;
};

#endif // DBDATA_H
