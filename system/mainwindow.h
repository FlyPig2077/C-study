#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "login.h"
#include "registered.h"
#include "adminmanage.h"
#include "help.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pbtn1_clicked();

    void on_pbtn2_clicked();

    void timeUpdate();

    void on_pushButton_clicked();

    void on_actionsetup_triggered();

private:
    Ui::MainWindow *ui;
    login *login1=new login;
    registered *registered1=new registered;
    adminmanage *manage=new adminmanage;
    help  *help1=new help;
};

#endif // MAINWINDOW_H
