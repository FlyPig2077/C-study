#ifndef ADD_H
#define ADD_H

#include <QDialog>

namespace Ui {
class add;
}

class add : public QDialog
{
    Q_OBJECT

public:
    explicit add(QWidget *parent = nullptr);
    ~add();
    void clearUserInterface();
    void writeToFile(QString cnt);

private slots:
    void on_pbtn_ok_clicked();

    void on_pbtn_cancle_clicked();

private:
    Ui::add *ui;
};

#endif // ADD_H
