#ifndef DATABASEDIALOG_HPP
#define DATABASEDIALOG_HPP

#include <QDialog>

namespace Ui {
    class DatabaseDialog;
}

class DatabaseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DatabaseDialog(QWidget *parent = 0);
    ~DatabaseDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_tilesetList_currentRowChanged(int currentRow);

    void on_addTextToolButton_clicked();


    void on_playSoundButton_clicked();

    void on_stopSoundButton_clicked();

private:
    Ui::DatabaseDialog *ui;
};

#endif // DATABASEDIALOG_HPP
