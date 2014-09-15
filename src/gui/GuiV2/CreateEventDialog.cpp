#include "CreateEventDialog.hpp"
#include "ui_CreateEventDialog.h"

CreateEventDialog::CreateEventDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateEventDialog)
{
    ui->setupUi(this);
}

CreateEventDialog::~CreateEventDialog()
{
    delete ui;
}

QString    CreateEventDialog::getEventName()
{
    return ui->eventLineEdit->text();
}
