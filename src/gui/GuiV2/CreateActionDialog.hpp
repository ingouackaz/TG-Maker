#ifndef CREATEACTIONDIALOG_HPP
#define CREATEACTIONDIALOG_HPP

#include <QDialog>

namespace Ui {
    class CreateActionDialog;
}

class CreateActionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateActionDialog(QWidget *parent = 0);
    ~CreateActionDialog();

private slots:
    void on_variableListComboBox_currentIndexChanged(int index);
    void disableAllFrame();
    void on_addVariableButton_clicked();

    void on_buttonBox_accepted();

private:
    Ui::CreateActionDialog *ui;
    void        updateEventList();
    void        updateVariableList();
    void        updateTilesetList();
    void        updateSoundList();
    void        updateTextList();
    void        updateAll();


    void        addVarAssign();
    void        addPlayerMove();
    void        addPlayerSetImage();
    void        addPositionSetImage();
    void        addTextOn();
    void        addTextOff();
    void        addEventQueue();
    void        addSoundOn();
    void        addSoundOff();

};

#endif // CREATEACTIONDIALOG_HPP
