#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H

#include <QMainWindow>

namespace Ui {
class usermanagement;
}

class usermanagement : public QMainWindow
{
    Q_OBJECT

public:
    explicit usermanagement(QWidget *parent = nullptr);
    ~usermanagement();

private:
    Ui::usermanagement *ui;
};

#endif // USERMANAGEMENT_H
