#include<QSound>

#include "DatabaseDialog.hpp"
#include "ui_DatabaseDialog.h"

#include "CreateTextDialog.hpp"

#include "ProjectManager.hpp"
#include "Image.hpp"
#include "Sound.hpp"
#include "Text.hpp"

DatabaseDialog::DatabaseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatabaseDialog)
{
    ui->setupUi(this);

    ui->AutotNamelineEdit_->setText(ProjectManager::singleton().getProjectAuthor());

    ui->xCooBeginSpinBox->setValue(ProjectManager::singleton().getXStartCoor());
    ui->xCooBeginSpinBox->setMaximum(ProjectManagerBase::map_width - 1);
    ui->yCooBeginSpinBox->setValue(ProjectManager::singleton().getYStartCoor());
    ui->yCooBeginSpinBox->setMaximum(ProjectManagerBase::map_height - 1);

    ui->xCooCharacterTilesetSpinBox->setValue(ProjectManager::singleton().getTileSetX());
    ui->xCooCharacterTilesetSpinBox->setMaximum(7);
    ui->yCooCharacterTilesetSpinBox->setValue(ProjectManager::singleton().getTileSetY());
    ui->yCooCharacterTilesetSpinBox->setMaximum(16);

    for (ImageManager::const_iterator it = ImageManager::singleton().begin(); it != ImageManager::singleton().end(); ++it)
    {
        ui->tilesetList->addItem(QString((*it).second->getPath().c_str()));
    }

    for (SoundManager::const_iterator it = SoundManager::singleton().begin(); it != SoundManager::singleton().end(); ++it)
    {
        ui->audioList->addItem(QString((*it).second->getPath().c_str()));
    }

    for (TextManager::const_iterator it = TextManager::singleton().begin(); it != TextManager::singleton().end(); ++it)
    {
        ui->textList->addItem(QString((*it).second->getPath().c_str()));
    }

    ui->audioList->setCurrentRow(0);
}

DatabaseDialog::~DatabaseDialog()
{
    delete ui;
}

void DatabaseDialog::on_buttonBox_accepted()
{
    //    if (ui->AutotNamelineEdit_->text())
    ProjectManager::singleton().setProjectAuthor(ui->AutotNamelineEdit_->text());

    if (ui->xCooBeginSpinBox->value() >= 0 && ui->xCooBeginSpinBox->value() < ProjectManagerBase::map_width)
        ProjectManager::singleton().setXStartCoor(ui->xCooCharacterTilesetSpinBox->value());
    if (ui->yCooBeginSpinBox->value() >= 0 && ui->yCooBeginSpinBox->value() < ProjectManagerBase::map_height)
        ProjectManager::singleton().setYStartCoor(ui->yCooCharacterTilesetSpinBox->value());

    if (ui->xCooCharacterTilesetSpinBox->value() >= 0 && ui->xCooCharacterTilesetSpinBox->value() < 8)
        ProjectManager::singleton().setTileSetX(ui->xCooCharacterTilesetSpinBox->value());
    if (ui->yCooCharacterTilesetSpinBox->value() >= 0 && ui->yCooCharacterTilesetSpinBox->value() < 17)
        ProjectManager::singleton().setTileSetY(ui->yCooCharacterTilesetSpinBox->value());
    ProjectManager::singleton().setTileSetId(ImageManager::singleton().getIdByRank(ui->tilesetList->currentRow()));
}

void DatabaseDialog::on_buttonBox_rejected()
{

}

void DatabaseDialog::on_tilesetList_currentRowChanged(int currentRow)
{

}

void DatabaseDialog::on_addTextToolButton_clicked()
{
    CreateTextDialog textDialog;

    if (textDialog.exec() && textDialog.getName() != "")
    {
        for (TextManager::iterator it = TextManager::singleton().begin(); it != TextManager::singleton().end(); ++it)
        {
            if ((*it).second->getPath() == textDialog.getName().toStdString())
            {
                QMessageBox::critical(this, "Error", "This name is already used for another text");
                return;
            }
        }
        TextManager::singleton().push(new Text(textDialog.getName().toStdString()));
        ui->textList->addItem(textDialog.getName());
    }
}

void DatabaseDialog::on_playSoundButton_clicked()
{
    SoundManager::singleton().getByRank(ui->audioList->currentRow())->Play();
}

void DatabaseDialog::on_stopSoundButton_clicked()
{
    SoundManager::singleton().getByRank(ui->audioList->currentRow())->Stop();
}
