#ifndef NEWPROJECTDIALOG_HPP
#define NEWPROJECTDIALOG_HPP

#include <QDialog>

#include "ProjectManager.hpp"

namespace Ui {
class NewProjectDialog;
}

class NewProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewProjectDialog(QWidget *parent = 0);
    ~NewProjectDialog();
private slots:
    void on_browseButton_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void valueChangedLoadingBar(int value);
private:
    Ui::NewProjectDialog *ui;
    NewProjectDialog *_loadingBarDialog;

};

#endif // NEWPROJECTDIALOG_HPP
