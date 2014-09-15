#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QMainWindow>
#include <QtGui/QDirModel>
#include <QtGui/QTreeView>
#include <string>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:    
    void on_pushButton_import_clicked();
    void on_pushButton_ajout_clicked();
    void on_pushButton_quit_clicked();
    void on_listWidget_doc_clicked();
    void on_listWidget_contenu_clicked();


private:
    Ui::MainWindow *ui;
    QString                 _path;

};

#endif // MAINWINDOW_H
