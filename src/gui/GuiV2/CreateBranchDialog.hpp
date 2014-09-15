#ifndef CREATEBRANCHDIALOG_HPP
#define CREATEBRANCHDIALOG_HPP

#include <QDialog>

namespace Ui {
    class CreateBranchDialog;
}

class CreateBranchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateBranchDialog(QWidget *parent = 0);
    ~CreateBranchDialog();

private slots:
    void on_buttonBox_accepted();

    void on_operatorListWidget_currentRowChanged(int currentRow);

    void on_variableListWidget_currentRowChanged(int currentRow);

    void on_variableNUmberButton_clicked();

private:
    Ui::CreateBranchDialog *ui;
    std::vector<std::string> _operatorList;
    bool        _numberVariable;
    int         _variable1Rank;
    int         _variable2Rank;
    int         _operatorRank;
private:
    void        updateEventList();
    void        updateVariableList();
    void        updateTilesetList();
    void        updateSoundList();
    void        updateTextList();
};

#endif // CREATEBRANCHDIALOG_HPP
