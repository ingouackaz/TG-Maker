#ifndef CREATETEXTDIALOG_HPP
#define CREATETEXTDIALOG_HPP

#include <QDialog>
#include <QString>

namespace Ui {
class CreateTextDialog;
}

class CreateTextDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit CreateTextDialog(QWidget *parent = 0);
    ~CreateTextDialog();
    
public:
    QString getName() const;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::CreateTextDialog *ui;
};

#endif // CREATETEXTDIALOG_HPP
