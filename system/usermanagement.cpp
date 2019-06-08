#include "usermanagement.h"
#include "ui_usermanagement.h"

usermanagement::usermanagement(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::usermanagement)
{
    ui->setupUi(this);
}

usermanagement::~usermanagement()
{
    delete ui;
}
