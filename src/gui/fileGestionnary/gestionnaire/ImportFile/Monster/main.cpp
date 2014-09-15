#include <QApplication>
#include "mainwindow.h"
#include <QPushButton>
#include <QtGui/QDirModel>
#include <QtGui/QTreeView>
#include <QDirIterator>
#include <QDebug>
#include <QStringList>
#include <QDir>
#include <string>
#include <iostream>
#include <QApplication>
#include <QListWidgetItem>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
     w.show();

    return a.exec();
}
