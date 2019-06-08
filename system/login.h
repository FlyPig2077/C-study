#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QFile>
#include <QSqlQueryModel>
#include "adminmanage.h"

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    void clearLoginInterface();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::login *ui;
    adminmanage *adminmanage1=new adminmanage;
};

#endif // LOGIN_H
