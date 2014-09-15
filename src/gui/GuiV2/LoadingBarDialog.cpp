#include <QTimer>
#include <iostream>

#include "LoadingBarDialog.hpp"
#include "ui_LoadingBarDialog.h"

int LoadingBarDialog::loadingValue = 0;
QMutex LoadingBarDialog::mutex;


LoadingBarDialog::LoadingBarDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadingBarDialog)
{
    ui->setupUi(this);
    ui->loadingBar->setValue(0);
    QTimer *timer9 = new QTimer(this);
    connect(timer9, SIGNAL(timeout()), this, SLOT(valueChangedSlot(void)));
    timer9->start(300);
}

LoadingBarDialog::~LoadingBarDialog()
{
    delete ui;
}
void LoadingBarDialog::valueChangedSlot(void)
{
    mutex.lock();
    ui->loadingBar->setValue(loadingValue);
    if (loadingValue == 100)
    {
        this->close();
    }
    mutex.unlock();
}

void LoadingBarDialog::setValue(int value)
{
    ui->loadingBar->setValue(value);
}
