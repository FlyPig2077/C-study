#include "classnum.h"
#include "ui_classnum.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>

extern QString user;
classnum::classnum(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::classnum)
{
    ui->setupUi(this);
}

classnum::~classnum()
{
    delete ui;
}

void classnum::on_pushButton_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    QString classnum="select classNum as 类别编号,className as 类别名称 from "+user+"contactclass"" ";
    model->setQuery(classnum);
    this->ui->tableView->setModel(model);
}
