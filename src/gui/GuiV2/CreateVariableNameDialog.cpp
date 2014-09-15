#include "CreateVariablenameDialog.hpp"
#include "ui_CreateVariablenameDialog.h"

CreateVariableNameDialog::CreateVariableNameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateVariableNameDialog)
{
    ui->setupUi(this);
}

CreateVariableNameDialog::~CreateVariableNameDialog()
{
    delete ui;
}
