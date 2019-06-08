#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QPalette>
#include <QTimer>
#include <QDateTime>
#include <QDebug>
#include "help.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeUpdate()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;

}
void MainWindow::timeUpdate(){

    QDateTime time = QDateTime::currentDateTime();
    QString time_show = time.toString("hh:mm:ss");
    QString date_show = time.toString("yyyy-MM-dd");
    QString week_show= time.toString("dddd");
    this->ui->time->setText(time_show);
    this->ui->date->setText(date_show);
    this->ui->week->setText(week_show);
}

void MainWindow::on_pbtn1_clicked()
{
    //this->hide();
    login1->show();
    login1->exec();
   // manage->exec();
    //this->show();
}

void MainWindow::on_pbtn2_clicked()
{
    //this->hide();
    registered1->show();
    registered1->exec();
    //this->show();
}


void MainWindow::on_pushButton_clicked()
{
    this->close();
}

void MainWindow::on_actionsetup_triggered()
{

    help1->show();
}
