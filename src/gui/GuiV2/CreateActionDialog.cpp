#include "CreateActionDialog.hpp"
#include "ui_CreateActionDialog.h"
#include "Action.hpp"
#include "Variable.hpp"
#include "Event.hpp"
#include "Image.hpp"
#include "Text.hpp"
#include "Sound.hpp"

CreateActionDialog::CreateActionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateActionDialog)
{
    ui->setupUi(this);
    updateAll();
}

CreateActionDialog::~CreateActionDialog()
{
    delete ui;
}

void CreateActionDialog::on_variableListComboBox_currentIndexChanged(int index)
{

    switch (index){
    case 0:
    {
        disableAllFrame();
        ui->assignementFrame->setEnabled(true);
        break;
    }
    case 1:
    {
        disableAllFrame();
        ui->MoveFrame->setEnabled(true);
        break;
    }
    case 2:
    {
        disableAllFrame();
        ui->playerFrame->setEnabled(true);
        break;
    }
    case 3:
    {
        disableAllFrame();
        ui->tileFrame->setEnabled(true);
        break;
    }
    case 4:
    {
        disableAllFrame();
        ui->textOnFrame->setEnabled(true);
        break;
    }
    case 5:
    {
        disableAllFrame();
        ui->textOFFFrame->setEnabled(true);
        break;
    }
    case 6:
    {
        disableAllFrame();
        ui->queueFrame->setEnabled(true);
        break;
    }
    case 7:
    {
        disableAllFrame();
        ui->soundONFrame->setEnabled(true);
    }
    case 8:
    {
        disableAllFrame();
        ui->soundOFFFrame->setEnabled(true);
    }
    }
}

void CreateActionDialog::disableAllFrame()
{
    ui->assignementFrame->setEnabled(false);
    ui->playerFrame->setEnabled(false);
    ui->MoveFrame->setEnabled(false);
    ui->queueFrame->setEnabled(false);
    ui->soundOFFFrame->setEnabled(false);
    ui->textOFFFrame->setEnabled(false);
    ui->soundONFrame->setEnabled(false);
    ui->textOnFrame->setEnabled(false);
    ui->tileFrame->setEnabled(false);
}

void CreateActionDialog::updateAll()
{
    updateEventList();
    updateVariableList();
    updateTilesetList();
    updateSoundList();
    updateTextList();
}

void CreateActionDialog::updateEventList()
{
    ui->queueComboBox->clear();
    for (EventManager::const_iterator it = EventManager::singleton().begin(); it != EventManager::singleton().end(); ++it)
    {
        ui->queueComboBox->addItem(it->second->res_data.name);
    }
}


void CreateActionDialog::updateSoundList()
{
    for (SoundManager::iterator it = SoundManager::singleton().begin(); it != SoundManager::singleton().end(); ++it)
    {
       ui->playerComboBox->addItem(it->second->res_data.path);
        ui->tileComboBox->addItem(it->second->res_data.path);
    }
}

void CreateActionDialog::updateTextList()
{
    for (TextManager::iterator it = TextManager::singleton().begin(); it != TextManager::singleton().end(); ++it)
    {
        ui->playerComboBox->addItem(it->second->res_data.path);
        ui->tileComboBox->addItem(it->second->res_data.path);
    }
}

void CreateActionDialog::updateTilesetList()
{
    for (ImageManager::iterator it = ImageManager::singleton().begin(); it != ImageManager::singleton().end(); ++it)
    {
        ui->playerComboBox->addItem(it->second->res_data.path);
        ui->tileComboBox->addItem(it->second->res_data.path);
    }
}

void CreateActionDialog::updateVariableList()
{
    for (VariableManager::const_iterator it = VariableManager::singleton().begin(); it != VariableManager::singleton().end(); ++it)
    {
        ui->var1AssigncomboBox->addItem(it->second->res_data.name);
        ui->var2AssigncomboBox->addItem(it->second->res_data.name);
        ui->var1MovePcomboBox->addItem(it->second->res_data.name);
        ui->var2MovePcomboBox->addItem(it->second->res_data.name);
    }
}

void CreateActionDialog::on_addVariableButton_clicked()
{
    switch (ui->actionListWidget->currentRow()){
    case 0:
    {
        addVarAssign();
        //addConstantVariable(variableName);
        break;
    }
    case 1:
    {
        addPlayerMove();
        //addAdditionVariable(variableName);
        break;
    }
    case 2:
    {
        addPlayerSetImage();
        //addCollidablePosVariable(variableName);
        break;
    }
    case 3:
    {
        addPositionSetImage();
        //addCounterEventVariable(variableName);
        break;
    }
    case 4:
    {
        addTextOn();
        //addKeyStateVariable(variableName);
        break;
    }
    case 5:
    {
        addTextOff();
        //addStatePosVariable(variableName);
        break;
    }
    case 6:
    {
        addEventQueue();
        //addPlayerXVariable(variableName);
        break;
    }
    case 7:
    {
        addSoundOn();
       // addPlayerYVariable(variableName);
        break;
    }
    case 8:
    {
        addSoundOff();
    }
    }
    updateAll();
}


void    CreateActionDialog::addVarAssign()
{
    Action* v(new Action);

    v->set_Action(Action::VariableAssign,
                  VariableManager::singleton().getIdByRank(ui->var1AssigncomboBox->currentIndex()),
                  VariableManager::singleton().getIdByRank(ui->var2AssigncomboBox->currentIndex())
    );
    ActionManager::singleton().push(v);

}

void    CreateActionDialog::addPlayerMove()
{
    Action* v(new Action);

    v->set_Action(Action::PlayerMove,
                  VariableManager::singleton().getIdByRank(ui->var1MovePcomboBox->currentIndex()),
                  VariableManager::singleton().getIdByRank(ui->var2MovePcomboBox->currentIndex())
    );
    ActionManager::singleton().push(v);
}

void    CreateActionDialog::addPlayerSetImage()
{
    Action* v(new Action);

    v->set_Action(Action::PlayerSetImage,
                  ImageManager::singleton().getIdByRank(ui->playerComboBox->currentIndex()),
                  VariableManager::singleton().getIdByRank(ui->xStateSpinBox_2->value()),
                  VariableManager::singleton().getIdByRank(ui->yStateSpinBox_2->value())
    );
    ActionManager::singleton().push(v);
}

void    CreateActionDialog::addPositionSetImage()
{
    Action* v(new Action);

    v->set_Action(Action::PositionSetImage,
                  ui->xTileMSpinBox->value(),
                  ui->yTileMSpinBox->value(),
                  ImageManager::singleton().getIdByRank(ui->tileComboBox->currentIndex()),
                  ui->xTileTSpinBox->value(),
                  ui->yTileTSpinBox->value()
    );
    ActionManager::singleton().push(v);
}

void    CreateActionDialog::addTextOn()
{
    Action* v(new Action);

    v->set_Action(Action::TextOn,
                  TextManager::singleton().getIdByRank(ui->textOncomboBox_2->currentIndex())
    );
    ActionManager::singleton().push(v);
}

void    CreateActionDialog::addTextOff()
{
    Action* v(new Action);

    v->set_Action(Action::TextOff,
                  TextManager::singleton().getIdByRank(ui->textOffcomboBox->currentIndex())
    );
    ActionManager::singleton().push(v);
}

void    CreateActionDialog::addEventQueue()
{
    Action* v(new Action);

    v->set_Action(Action::EventQueue,
                  EventManager::singleton().getIdByRank(ui->queueComboBox->currentIndex()),
                  ui->queueDelay->value()

    );
    ActionManager::singleton().push(v);
}

void    CreateActionDialog::addSoundOn()
{

}

void    CreateActionDialog::addSoundOff()
{

}

void CreateActionDialog::on_buttonBox_accepted()
{

}
