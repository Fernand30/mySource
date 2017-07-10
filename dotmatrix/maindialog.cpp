#include "maindialog.h"
#include "ui_maindialog.h"

mainDialog::mainDialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainDialog)
{
    ui->setupUi(this);
    setMaximumSize(this->size());
    setMinimumSize(this->size());
}
mainDialog::~mainDialog()
{
    delete ui;
}
