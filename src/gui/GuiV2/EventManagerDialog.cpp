#include <QTreeWidgetItem>
#include <QtCore>
#include "EventManagerDialog.hpp"
#include "ui_EventManagerDialog.h"
#include <QTreeWidget>

#include "Event.hpp"
#include "Branch.hpp"
#include "Action.hpp"
#include "Variable.hpp"
#include "CreateActionDialog.hpp"
#include "CreateEventDialog.hpp"
#include "CreateBranchDialog.hpp"
#include "CreateVariableDialog.hpp"



EventManagerDialog::EventManagerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EventManagerDialog)
{
    ui->setupUi(this);
    ui->eventTreeWidget->clear();
    disableAllFrame();
    ui->constantFrame->setEnabled(true);

    updateAllList();


    for (EventManager::const_iterator it = EventManager::singleton().begin(); it != EventManager::singleton().end(); ++it)
    {
        _idsEvent.push_back((*it).first);
        ui->counterComboBox->addItem((QString((*it).second->res_data.name)));
    }
}

EventManagerDialog::~EventManagerDialog()
{
    delete ui;
}



void EventManagerDialog::on_addEvent_clicked()
{
    CreateEventDialog eventd(this);

    if (eventd.exec())
    {
        addEvent(eventd.getEventName());
    }
}


void EventManagerDialog::on_addBranch_clicked()
{

    if (dynamic_cast<Event*>(ui->eventTreeWidget->currentItem())  || dynamic_cast<Branch*>(ui->eventTreeWidget->currentItem()) )
    {
        CreateBranchDialog eventd(this);
        if (eventd.exec())
        {
            std::cout << "BRANCH CREE" << std::endl;
            addBranchItem();
        }
    }
}

void EventManagerDialog::on_addAction_clicked()
{
    if (dynamic_cast<Event*>(ui->eventTreeWidget->currentItem())  || dynamic_cast<Branch*>(ui->eventTreeWidget->currentItem()))
    {
        CreateActionDialog eventd(this);
        if (eventd.exec())
        {
            std::cout << "ACTIONN CREE" << std::endl;
            addActionItem();
        }
    }
}

void EventManagerDialog::addEvent(QString eventName)
{
    // add event in display
    Event * item = new Event();
    item->setText(0,eventName);
    ui->eventTreeWidget->addTopLevelItem(item);
    // add event in data
    item->res_data.id_first = -1;
    item->res_data.flags = 0;
    item->res_data.n = -1;
    memset(item->res_data.name, 0, sizeof(item->res_data.name));
    strncpy(item->res_data.name, eventName.toStdString().c_str(), sizeof(item->res_data.name) - 1);
    EventManager::singleton().push(item);
}



void EventManagerDialog::addBranchItem()
{
    if (!dynamic_cast<Action*>(ui->eventTreeWidget->currentItem()))
    {
        QTreeWidgetItem * item = new QTreeWidgetItem();

        item->setText(0,"Branch");
        ui->eventTreeWidget->currentItem()->addChild(item);
    }
}

void EventManagerDialog::addActionItem()
{
    if (!dynamic_cast<Action*>(ui->eventTreeWidget->currentItem()))
    {
        QTreeWidgetItem * item = new QTreeWidgetItem();
        item->setText(0,"Action ");
        ui->eventTreeWidget->currentItem()->addChild(item);
    }
}

void EventManagerDialog::on_variableListComboBox_currentIndexChanged(int index)
{
    switch (index){
    case 0:
    {
        disableAllFrame();
        ui->constantFrame->setEnabled(true);
        break;
    }
    case 1:
    {
        disableAllFrame();
        ui->additionFrame->setEnabled(true);
        break;
    }
    case 2:
    {
        disableAllFrame();
        ui->collidableFrame->setEnabled(true);
        break;
    }
    case 3:
    {
        disableAllFrame();
        ui->counterFrame->setEnabled(true);
        break;
    }
    case 4:
    {
        disableAllFrame();
        ui->keyFrame->setEnabled(true);
        break;
    }
    case 5:
    {
        disableAllFrame();
        ui->positionFrame->setEnabled(true);
        break;
    }
    case 6:
    {
        disableAllFrame();
        break;
    }
    }
}

void EventManagerDialog::disableAllFrame()
{

    ui->additionFrame->setEnabled(false);
    ui->collidableFrame->setEnabled(false);
    ui->constantFrame->setEnabled(false);
    ui->counterFrame->setEnabled(false);
    ui->keyFrame->setEnabled(false);
    ui->positionFrame->setEnabled(false);
}

void EventManagerDialog::on_addVariableButton_clicked()
{
    std::cout << "INDEX = " << ui->variable1comboBox->currentIndex() << std::endl;
    CreateVariableDialog eventd(this);
    QString variableName;

    if (eventd.exec())
    {
        variableName = (eventd.getNameVariable());

        switch (ui->variableListComboBox->currentIndex()){
        case 0:
        {
            addConstantVariable(variableName);
            break;
        }
        case 1:
        {
            addAdditionVariable(variableName);
            break;
        }
        case 2:
        {
            addCollidablePosVariable(variableName);
            break;
        }
        case 3:
        {
            addCounterEventVariable(variableName);
            break;
        }
        case 4:
        {
            addKeyStateVariable(variableName);
            break;
        }
        case 5:
        {
            addStatePosVariable(variableName);
            break;
        }
        case 6:
        {
            addPlayerXVariable(variableName);
            break;
        }
        case 7:
        {
            addPlayerYVariable(variableName);
            break;
        }
        }
        updateAllList();
    }
}


void EventManagerDialog::addConstantVariable(QString name)
{
     Variable* v(new Variable);

    v->set_Variable(Variable::Constant, ui->constantSpinBox->value());
    ui->variableListWidget->addItem(new QListWidgetItem(name));
    v->set_name(name.toStdString());
    VariableManager::singleton().push(v);

}

void EventManagerDialog::addAdditionVariable(QString name)
{
    Variable* v(new Variable);
    
    v->set_Variable(Variable::Addition,
                             _idsVariable[ui->variable1comboBox->currentIndex()],
                             _idsVariable[ui->variable2ComboBox->currentIndex()]);
    v->set_name(name.toStdString());
    VariableManager::singleton().push(v);
}

void EventManagerDialog::addCollidablePosVariable(QString name)
{
    Variable* v(new Variable);
    
    v->set_Variable(Variable::PositionCollidable,
                             ui->xCollidableSpinBox->value(),
                             ui->xCollidableSpinBox->value());
    v->set_name(name.toStdString());
    VariableManager::singleton().push(v);
}

void EventManagerDialog::addCounterEventVariable(QString name)
{
    Variable* v(new Variable);
    
    v->set_Variable(Variable::EventCounter,
                             _idsEvent[ui->counterComboBox->currentIndex()]);

    v->set_name(name.toStdString());
    VariableManager::singleton().push(v);
}

void EventManagerDialog::addKeyStateVariable(QString name)
{
    Variable* v(new Variable);
    
    v->set_Variable(Variable::KeyState,
                             ui->keyComboBox->currentIndex());
    v->set_name(name.toStdString());
    VariableManager::singleton().push(v);
}

void EventManagerDialog::addStatePosVariable(QString name)
{
    Variable* v(new Variable);
    
    v->set_Variable(Variable::PositionState,
                             ui->xStateSpinBox->value(),
                             ui->yStateSpinBox->value());

    v->set_name(name.toStdString());
    VariableManager::singleton().push(v);
}

void EventManagerDialog::addPlayerXVariable(QString name)
{
    Variable* v(new Variable);
    
    v->set_Variable(Variable::PlayerX);

    v->set_name(name.toStdString());
    VariableManager::singleton().push(v);
}

void EventManagerDialog::addPlayerYVariable(QString name)
{
    Variable* v(new Variable);
    
    v->set_Variable(Variable::PlayerY);

    v->set_name(name.toStdString());
    VariableManager::singleton().push(v);
}

void EventManagerDialog::updateAllList()
{
    ui->variableListWidget->clear();
    ui->variable1comboBox->clear();
    ui->variable2ComboBox->clear();
    _idsVariable.clear();

    for (VariableManager::const_iterator it = VariableManager::singleton().begin(); it != VariableManager::singleton().end(); ++it)
    {
        _idsVariable.push_back((*it).first);
        ui->variableListWidget->addItem(new QListWidgetItem(QString((*it).second->res_data.name)));
        ui->variable1comboBox->addItem((QString((*it).second->res_data.name)));
        ui->variable2ComboBox->addItem((QString((*it).second->res_data.name)));
    }
}

void EventManagerDialog::updateEventList()
{
    _idsEvent.clear();
    ui->counterComboBox->clear();
    for (EventManager::const_iterator it = EventManager::singleton().begin(); it != EventManager::singleton().end(); ++it)
    {
        _idsEvent.push_back((*it).first);
        ui->counterComboBox->addItem((QString((*it).second->res_data.name)));
    }
}

void EventManagerDialog::on_tabWidget_selected(const QString &arg1)
{
    if (arg1 == "Variable list")
    {
        std::cout << "IN VARIABLE MODE " << std::endl;
        updateEventList();
    }
}
