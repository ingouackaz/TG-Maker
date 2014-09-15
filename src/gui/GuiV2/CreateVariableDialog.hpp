#ifndef CREATEVARIABLEDIALOG_HPP
#define CREATEVARIABLEDIALOG_HPP

#include <QDialog>

namespace Ui {
    class CreateVariableDialog;
}

class CreateVariableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateVariableDialog(QWidget *parent = 0);
    ~CreateVariableDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();
public:
    QString     getNameVariable();
private:
    Ui::CreateVariableDialog *ui;
};

#endif // CREATEVARIABLEDIALOG_HPP
