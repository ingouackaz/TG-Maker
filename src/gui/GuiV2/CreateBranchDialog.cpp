#include "CreateBranchDialog.hpp"
#include "ui_CreateBranchDialog.h"
#include "Variable.hpp"
#include "Branch.hpp"
#include "CreateBranchDialog.hpp"
#include "ui_CreateBranchDialog.h"
#include "Branch.hpp"
#include "Event.hpp"
#include "Sound.hpp"
#include "Text.hpp"


CreateBranchDialog::CreateBranchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateBranchDialog)
{
    ui->setupUi(this);
    // ajouter variable list gauche
    for (VariableManager::const_iterator it = VariableManager::singleton().begin(); it != VariableManager::singleton().end(); ++it)
    {
        ui->variableListWidget->addItem((QString((*it).second->res_data.name)));
    }

    _operatorList.push_back("Equal");
    _operatorList.push_back("NotEqual");
    _operatorList.push_back("Lesser");
    _operatorList.push_back("Greater");
    _operatorList.push_back("LesserOrEqual");
    _operatorList.push_back("GreaterOrEqual");
    _operatorList.push_back("BranchCompareTotal");

    _numberVariable = true;
}

CreateBranchDialog::~CreateBranchDialog()
{
    delete ui;
}

void CreateBranchDialog::on_buttonBox_accepted()
{

    // add event in display
    //Branch * item = new Branch();
    //item->setText(0,eventName);w
    // add event in data
    /*
    item->res_data.id_next = -1;
    if (ui->conditionComboBox->currentIndex() == 0)
         item->res_data.flags = BranchBase::IfIsBranch;
    else
         item->res_data.flags = BranchBase::IsWhile;
    item->res_data.cmptype = static_cast<BranchBase::BranchCompare>(ui->operatorListWidget->currentRow());
    item->res_data.id_vars[0] = VariableManager::singleton().getIdByRank(_variable1Rank);
    item->res_data.id_vars[1] = VariableManager::singleton().getIdByRank(_variable2Rank);
    item->res_data.id_then = -1;
    //item->res_data.id_else = -1;
    //memset(item->res_data.name, 0, sizeof(item->res_data.name));
    //strncpy(item->res_data.name, eventName.toStdString().c_str(), sizeof(item->res_data.name) - 1);
    BranchManager::singleton().push(item);
    */
}

void CreateBranchDialog::on_operatorListWidget_currentRowChanged(int currentRow)
{
    ui->operatorButton->setText(QString(_operatorList[currentRow].c_str()));
}

void CreateBranchDialog::on_variableListWidget_currentRowChanged(int currentRow)
{
    if(_numberVariable == true)
    {
        ui->variable_1Button->setText( ui->variableListWidget->currentItem()->text());
        _variable1Rank = ui->variableListWidget->currentRow();
    }
    else
    {
        ui->variable_2Button->setText(ui->variableListWidget->currentItem()->text());
        _variable2Rank = ui->variableListWidget->currentRow();

    }
}

void CreateBranchDialog::on_variableNUmberButton_clicked()
{
    _numberVariable = !_numberVariable;
    if (_numberVariable == true)
    {
        ui->variableNUmberButton->setText("1");
    }
    else
    {
        ui->variableNUmberButton->setText("2");
    }
}



void   CreateBranchDialog::updateEventList()
{

}

void  CreateBranchDialog::updateSoundList()
{

}

void   CreateBranchDialog::updateTilesetList()
{

}

void    CreateBranchDialog::updateVariableList()
{

}

