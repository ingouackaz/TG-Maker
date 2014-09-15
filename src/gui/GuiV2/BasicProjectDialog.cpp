#include "BasicProjectDialog.hpp"
#include "ui_bBasicProjectDialog.h"

BasicProjectDialog::BasicProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BasicProjectDialog)
{
    ui->setupUi(this);
}

BasicProjectDialog::~BasicProjectDialog()
{
    delete ui;
}

void BasicProjectDialog::on_pushButton_clicked()
{
    QString dossier = QFileDialog::getExistingDirectory(this);
    ui->pathEdit->setText(dossier);
}

void BasicProjectDialog::on_buttonBox_accepted()
{
    QDir dir(ui->pathEdit->text());

    if (dir.exists() == false ||ui->pathEdit->text().toStdString() == "" )
    {
        QMessageBox::critical(this, "Error", "The directory " + ui->pathEdit->text() + "doesn't exist");
        _project = NULL;
    }
    else
    {
        _project = new Project( ui->projectName->text(),  ui->pathEdit->text());
    }
}

Project*    BasicProjectDialog::getProject() const
{
    return _project;
}
