#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QMainWindow>

namespace Ui {
class mainDialog;
}

class mainDialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainDialog(QWidget *parent = 0);
    ~mainDialog();

private:
    Ui::mainDialog *ui;
};

#endif // MAINDIALOG_H
