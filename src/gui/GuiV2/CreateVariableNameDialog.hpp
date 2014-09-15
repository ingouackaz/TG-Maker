#ifndef CREATEVARIABLENAMEDIALOG_HPP
#define CREATEVARIABLENAMEDIALOG_HPP

#include <QDialog>

namespace Ui {
    class CreateVariableNameDialog;
}

class CreateVariableNameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateVariableNameDialog(QWidget *parent = 0);
    ~CreateVariableNameDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::CreateVariableNameDialog *ui;
};

#endif // CREATEVARIABLENAMEDIALOG_HPP
