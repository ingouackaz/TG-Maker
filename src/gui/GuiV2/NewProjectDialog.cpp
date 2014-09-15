#include <QFuture>
#include <QtCore>
#include <QtConcurrentFilter>
#include <string>
#include <QTimer>

#include "NewProjectDialog.hpp"
#include "ui_NewProjectDialog.h"
#include "Image.hpp"
#include "Position.hpp"
#include "Sound.hpp"
#include "LoadingBarDialog.hpp"

NewProjectDialog::NewProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewProjectDialog)
{
    ui->setupUi(this);
    ui->pathEditField->setEnabled(false);
}

NewProjectDialog::~NewProjectDialog()
{
    delete ui;
}

void NewProjectDialog::on_browseButton_clicked()
{
    QString dossier = QFileDialog::getExistingDirectory(this);
    //    ui->pathEdit->setText(dossier);
    ui->pathEditField->setText(dossier);
}

void NewProjectDialog::on_buttonBox_accepted()
{
    QDir dir(ui->pathEditField->text());

    if (dir.exists() == false ||ui->pathEditField->text().toStdString() == "" )
    {
        QMessageBox::critical(this, "Error", "The directory " + ui->pathEditField->text() + "doesn't exist");
    }
    else if (ui->projectNameEditField->text().toStdString().find('"') != std::string::npos
             || ui->projectNameEditField->text().toStdString().find('\\') != std::string::npos
             || ui->projectNameEditField->text().toStdString().find(' ') != std::string::npos)
    {
        QMessageBox::critical(this, "Error", "The project name can't contain one of the following characters : ' ' '\"' '\\'");
    }
    else if (ui->projectNameEditField->text() == QString(""))
    {
        QMessageBox::critical(this, "Error", "The project name can't be empty");
    }
    else
    {
        LoadingBarDialog newdialog(this);

        ProjectManager::singleton().initProject( ui->projectNameEditField->text(),  ui->pathEditField->text());
        if (ProjectManager::singleton().isInit())
        {
            // copy resources to project directory
            ImageManager::copyResources();
            SoundManager::copyResources();


            ImageManager::loadDefault();
            SoundManager::loadDefault();

            QFuture<void> future = QtConcurrent::run( PositionManager::loadDefault);

            newdialog.exec();
            ProjectManager::singleton().serialize((ProjectManager::singleton().getProjectPath() + ProjectManager::singleton().getProjectName() + ".tgmproj").toStdString());
        }
    }
}

void NewProjectDialog::on_buttonBox_rejected()
{

}

void NewProjectDialog::valueChangedLoadingBar(int value)
{

}
