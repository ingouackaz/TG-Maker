#include <QDir>
#include <iostream>
#include <QFileDialog>
#include <QImage>

#include "ImgSize.hpp"

#include "ProjectManager.hpp"
#include "Image.hpp"

#include "Sound.hpp"

#include "ResourceManagerDialog.hpp"
#include "ui_ResourceManagerDialog.h"

ResourceManagerDialog::ResourceManagerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResourceManagerDialog)
{
    ui->setupUi(this);

    _soundDirectoryPath = ProjectManager::singleton().getProjectPath().toStdString() + "res/snd/";

    _soundDirectory.setPath(QString(_soundDirectoryPath.c_str()));
    _soundList = _soundDirectory.entryInfoList(QDir::Files);

    foreach( QFileInfo fi, _soundList )
    {
        ui->soundList->addItem(new QListWidgetItem(fi.fileName()));
    }


    _imageDirectoryPath = ProjectManager::singleton().getProjectPath().toStdString() + "res/img/";
    _imageDirectory.setPath(QString(_imageDirectoryPath.c_str()));
    _imageList = _imageDirectory.entryInfoList(QDir::Files);

    foreach( QFileInfo fi, _imageList )
    {
        ui->imageList->addItem(new QListWidgetItem(fi.fileName()));
    }
}

ResourceManagerDialog::~ResourceManagerDialog()
{
    delete ui;
}

void ResourceManagerDialog::visualUpdateWindowImage(std::string &mypath)
{
    (void)mypath;


    /*
    //phand
    // clean le contenu de la window
    QDir dir;
    while(ui->imageList->count() > 0)
            ui->imageList->takeItem(0);

    // set le le dir
    ui->imageList->selectedItems();
    dir.setSorting(QDir::Size | QDir::Reversed);
    dir.cd(qPrintable(mypath.c_str()));
    QFileInfoList list = dir.entryInfoList();
    // je fais un ls dans le dir
    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);
        if (QString("%1").arg(fileInfo.fileName()) != "." && QString("%1").arg(fileInfo.fileName()) != "..")
        {
            QListWidgetItem *item = new QListWidgetItem(QString("%1").arg(fileInfo.fileName()));
            ui->imageList->addItem(item);
        }
    }
    */
}



void ResourceManagerDialog::on_importSoundButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName( this, tr("Open Document"), QDir::currentPath(), tr("images (*.flac *.wav)"), 0, QFileDialog::DontUseNativeDialog );
    /*if( !filePath.isNull() )
        qDebug( filePath.toAscii() );*/
    // fin de modif



    for (SoundManager::iterator it = SoundManager::singleton().begin(); it != SoundManager::singleton().end(); ++it)
    {
        if ((*it).second->getPath() == filePath.toStdString().substr(filePath.toStdString().find_last_of('/') + 1))
        {
            QMessageBox::critical(this, "Error", "There is already a sound with this filename");
            return;
        }
    }

    QString mailingList(filePath);
    QStringList mailids = mailingList.split(QString("/"));
    QString name = mailids.toVector()[mailids.toVector().size() - 1];

    QFile::copy(filePath, _soundDirectoryPath.c_str() + name);

    SoundManager::singleton().push(new Sound(name.toStdString()));
    ui->soundList->addItem(new QListWidgetItem(name));

    updateList();
    visualUpdateWindowSound(_soundDirectoryPath);
}

void ResourceManagerDialog::on_importImageButton_clicked()
{
    // verifier extension.
    //phand2
    //    QFileDialog fileDialog(this);
    // 1er graphique

    QString filePath = QFileDialog::getOpenFileName( this, tr("Open Document"), QDir::currentPath(), tr("Images (*.png)"), 0, QFileDialog::DontUseNativeDialog );
    // 2eme
    //QString filePath = QFileDialog::getOpenFileName( this, tr("Open Document"), QDir::currentPath(), tr("Images (*.jpg *.png)"), 0);
    /*if( !filePath.isNull() )
        qDebug( filePath.toAscii() );*/
    //finmodif

    if (!ImgSize::checkImgXY(filePath.toStdString().c_str()))
    {
        QMessageBox::critical(this, "Error", "The image must be at least 256*544");
        return;
    }

    for (ImageManager::iterator it = ImageManager::singleton().begin(); it != ImageManager::singleton().end(); ++it)
    {
        if ((*it).second->getPath() == filePath.toStdString().substr(filePath.toStdString().find_last_of('/') + 1))
        {
            QMessageBox::critical(this, "Error", "There is already an image with this filename");
            return;
        }
    }

    QString mailingList(filePath);
    QStringList mailids = mailingList.split(QString("/"));
    QString name = mailids.toVector()[mailids.toVector().size() - 1];
    QFile::copy(filePath, _imageDirectoryPath.c_str() + name);
    ImageManager::singleton().push(new Image(name.toStdString()));
    ui->imageList->addItem(new QListWidgetItem(name));

    ///    ui->imageList->res
    updateList();
    visualUpdateWindowImage(_imageDirectoryPath);
}


void ResourceManagerDialog::updateList()
{
    ui->imageList->clear();
    ui->soundList->clear();

    _soundList = _soundDirectory.entryInfoList(QDir::Files);
    std::cout << "TOTO" << std::endl;
    foreach( QFileInfo fi, _soundList )
    {
        ui->soundList->addItem(new QListWidgetItem(fi.fileName()));
    }
    _imageList = _imageDirectory.entryInfoList(QDir::Files);


    foreach( QFileInfo fi, _imageList )
    {
        ui->imageList->addItem(new QListWidgetItem(fi.fileName()));
    }
}

void ResourceManagerDialog::visualUpdateWindowSound(std::string &mypath)
{
    (void)mypath;
 /*
    //phand
    // clean le contenu de la window
    QDir dir;
    while(ui->soundList->count() > 0)
        ui->soundList->takeItem(0);

    // set le le dir
    ui->soundList->selectedItems();
    dir.setSorting(QDir::Size | QDir::Reversed);
    dir.cd(qPrintable(mypath.c_str()));
    QFileInfoList list = dir.entryInfoList();
    // je fais un ls dans le dir
    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);
        if (QString("%1").arg(fileInfo.fileName()) != "." && QString("%1").arg(fileInfo.fileName()) != "..")
        {
            QListWidgetItem *item = new QListWidgetItem(QString("%1").arg(fileInfo.fileName()));
            ui->soundList->addItem(item);
        }
    }
    */
}


