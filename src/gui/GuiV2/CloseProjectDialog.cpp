#include "CloseProjectDialog.hpp"
#include "ui_CloseProjectDialog.h"

CloseProjectDialog::CloseProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CloseProjectDialog)
{
    ui->setupUi(this);
}

CloseProjectDialog::~CloseProjectDialog()
{
    delete ui;
}
