#include "CreateTextDialog.hpp"
#include "ui_CreateTextDialog.h"

CreateTextDialog::CreateTextDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateTextDialog)
{
    ui->setupUi(this);
}

CreateTextDialog::~CreateTextDialog()
{
    delete ui;
}

QString CreateTextDialog::getName() const
{
    return ui->textNameLineEdit->text();
}

void CreateTextDialog::on_buttonBox_accepted()
{

}
