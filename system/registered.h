#ifndef REGISTERED_H
#define REGISTERED_H

#include <QDialog>

namespace Ui {
class registered;
}

class registered : public QDialog
{
    Q_OBJECT

public:
    explicit registered(QWidget *parent = nullptr);
    ~registered();
    void clearUserInterface();

private slots:
    void on_pbtn2_clicked();

    void on_pbtn1_clicked();

private:
    Ui::registered *ui;
};

#endif // REGISTERED_H
