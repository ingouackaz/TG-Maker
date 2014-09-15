#ifndef EVENTMANAGERDIALOG_HPP
#define EVENTMANAGERDIALOG_HPP

#include <QDialog>
#include <QModelIndex>
#include <QTreeWidget>
#include <QString>

namespace Ui {
    class EventManagerDialog;
}

class EventManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EventManagerDialog(QWidget *parent = 0);
    ~EventManagerDialog();

private slots:

    void on_addEvent_clicked();

    void on_addBranch_clicked();

    void on_addAction_clicked();


    void addEvent(QString eventName);
    void addBranchItem();
    void addActionItem();

    void on_variableListComboBox_currentIndexChanged(int index);
    void disableAllFrame();
    void on_addVariableButton_clicked();

    void on_tabWidget_selected(const QString &arg1);

private:
    void addConstantVariable(QString name);
    void addAdditionVariable(QString name);
    void addCollidablePosVariable(QString name);
    void addCounterEventVariable(QString name);
    void addKeyStateVariable(QString name);
    void addStatePosVariable(QString name);
    void addPlayerXVariable(QString name);
    void addPlayerYVariable(QString name);


    void updateAllList();
    void updateEventList();

private:
    Ui::EventManagerDialog *ui;
    std::vector <int> _idsVariable;
    std::vector <int> _idsEvent;

};

#endif // EVENTMANAGERDIALOG_HPP
