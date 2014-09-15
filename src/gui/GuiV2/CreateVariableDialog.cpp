#include "CreateVariableDialog.hpp"
#include "ui_CreateVariableDialog.h"

CreateVariableDialog::CreateVariableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateVariableDialog)
{
    ui->setupUi(this);
}

CreateVariableDialog::~CreateVariableDialog()
{
    delete ui;
}

void CreateVariableDialog::on_buttonBox_accepted()
{

}

void CreateVariableDialog::on_buttonBox_rejected()
{
    this->close();
}

QString CreateVariableDialog::getNameVariable()
{
   return ui->variableLineEdit->text();
}
