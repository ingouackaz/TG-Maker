#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QFileDialog>
#include <QIcon>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QTextStream>

#include <string>
#include <iostream>
#include <cstdlib>
#include<cstring>

#include<libgen.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),  ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString string = "Battle";
    QListWidgetItem *item = new QListWidgetItem(string);
    ui->listWidget_doc->addItem(item);
    string = "Battle2";
    QListWidgetItem *item2 = new QListWidgetItem(string);
    ui->listWidget_doc->addItem(item2);
    string = "Monster";
    QListWidgetItem *item3 = new QListWidgetItem(string);
    ui->listWidget_doc->addItem(item3);
    string = "Movie";
    QListWidgetItem *item4 = new QListWidgetItem(string);
    ui->listWidget_doc->addItem(item4);
    string = "Music";
    QListWidgetItem *item5 = new QListWidgetItem(string);
    ui->listWidget_doc->addItem(item5);
    string = "Picture";
    QListWidgetItem *item6 = new QListWidgetItem(string);
    ui->listWidget_doc->addItem(item6);
    string = "Sound";
    QListWidgetItem *item7 = new QListWidgetItem(string);
    ui->listWidget_doc->addItem(item7);
    string = "System";
    QListWidgetItem *item8 = new QListWidgetItem(string);
    ui->listWidget_doc->addItem(item8);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: on_pushButton_import_clicked()
{
    QString dossier = QFileDialog::getOpenFileName(this);
    ui->pathEdit->setText(dossier);
   // std::cout << "IMPORT= " << qPrintable(ui->pathEdit->displayText()) << std::endl;
}

void MainWindow::on_pushButton_ajout_clicked()
{
    // je recupere le path dans lequel je copie le fichier
    QString                 _mpath;
    _mpath = _path;
    QDir dir;
    dir.setSorting(QDir::Size | QDir::Reversed);
    QFileInfoList list = dir.entryInfoList();
    dir.cd(qPrintable(_mpath));
    std::string str;
    str = qPrintable(ui->pathEdit->displayText());
    _mpath.append("/");
    _mpath.append(basename(const_cast<char*>(str.c_str())));


    //je colle dans le bon dossier, et j'affiche le dossier
    QFile file(qPrintable(ui->pathEdit->displayText()));
    bool v = file.copy(QString(_mpath));
    if (v == 0)
        {
            std::cout <<"Impossible d'importer. Un fichier du meme nom existe deja." << std::endl;
        }
    on_listWidget_doc_clicked();
}

void MainWindow::on_pushButton_quit_clicked()
{
    exit(0);
}

void MainWindow::on_listWidget_doc_clicked()
{
    QString s = ui->listWidget_doc->currentItem()->text();
    QDir dir;
    QString path = "/home/einkra/qtpfa/fileGestionnary/gestionnaire/ImportFile/";

    // clean le contenu
    while(ui->listWidget_contenu->count() > 0)
        ui->listWidget_contenu->takeItem(0);

    // set le le dir, et list les fichiers
    ui->listWidget_doc->selectedItems();
    path.append(s);
    dir.setSorting(QDir::Size | QDir::Reversed);
    dir.cd(qPrintable(path));
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);
        //std::cout << qPrintable(QString("%1").arg(fileInfo.fileName()));
        if (QString("%1").arg(fileInfo.fileName()) != "." && QString("%1").arg(fileInfo.fileName()) != "..")
        {
            QListWidgetItem *item = new QListWidgetItem(QString("%1").arg(fileInfo.fileName()));
            ui->listWidget_contenu->addItem(item);
        }
    }
    _path = path;
}

void MainWindow::on_listWidget_contenu_clicked()
{
    // rien pour l'instant
}
