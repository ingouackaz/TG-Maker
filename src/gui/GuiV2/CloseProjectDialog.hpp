#ifndef CLOSEPROJECTDIALOG_HPP
#define CLOSEPROJECTDIALOG_HPP

#include <QDialog>

namespace Ui {
    class CloseProjectDialog;
}

class CloseProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CloseProjectDialog(QWidget *parent = 0);
    ~CloseProjectDialog();

private:
    Ui::CloseProjectDialog *ui;
};

#endif // CLOSEPROJECTDIALOG_HPP
