#ifndef BASICPROJECTDIALOG_HPP
#define BASICPROJECTDIALOG_HPP

#include <QDialog>
#include <Project.hpp>

namespace Ui {
class BasicProjectDialog;
}

class BasicProjectDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit BasicProjectDialog(QWidget *parent = 0);
    ~BasicProjectDialog();
    Project*    getProject() const;
private slots:
    void on_pushButton_clicked();

    void on_buttonBox_accepted();

private:
    Project    *_project;
    Ui::BasicProjectDialog *ui;
};

#endif // BASICPROJECTDIALOG_HPP
