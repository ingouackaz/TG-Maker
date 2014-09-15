#ifndef CREATEEVENTDIALOG_HPP
#define CREATEEVENTDIALOG_HPP

#include <QDialog>
#include <QString>


namespace Ui {
    class CreateEventDialog;
}

class CreateEventDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateEventDialog(QWidget *parent = 0);
    ~CreateEventDialog();

QString    getEventName();
private:
    Ui::CreateEventDialog *ui;
};

#endif // CREATEEVENTDIALOG_HPP
