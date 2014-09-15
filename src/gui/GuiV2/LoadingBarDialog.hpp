#ifndef LOADINGBARDIALOG_HPP
#define LOADINGBARDIALOG_HPP

#include <QDialog>
#include <QMutex>

namespace Ui {
    class LoadingBarDialog;
}

class LoadingBarDialog : public QDialog
{
    Q_OBJECT

public:
    static int loadingValue;
    static QMutex mutex;
public:
    explicit LoadingBarDialog(QWidget *parent);
    ~LoadingBarDialog();
    void    setValue(int value);
public slots:
   void valueChangedSlot(void);
private:
    Ui::LoadingBarDialog *ui;
};

#endif // LOADINGBARDIALOG_HPP
