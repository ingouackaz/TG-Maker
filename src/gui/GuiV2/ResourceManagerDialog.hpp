#ifndef RESOURCEMANAGERDIALOG_HPP
#define RESOURCEMANAGERDIALOG_HPP

#include <QDialog>
#include <QModelIndex>
#include <QDir>
#include <QFileDialog>


namespace Ui {
class ResourceManagerDialog;
}

class ResourceManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResourceManagerDialog(QWidget *parent = 0);
    ~ResourceManagerDialog();

private slots:
    void on_importSoundButton_clicked();

    void on_importImageButton_clicked();
private :
    void        updateList();

private:
    Ui::ResourceManagerDialog *ui;
    void visualUpdateWindowImage(std::string &mypath);
    void visualUpdateWindowSound(std::string &mypath);

    //QFileInfoList    _directoryList;
    QFileInfoList    _soundList;
    QFileInfoList    _imageList;

    QDir                        _imageDirectory;
    QDir                        _soundDirectory;
    QString                     _directoryName;
    std::string                _selectedDirPath;
    std::string                _soundDirectoryPath;
    std::string                _imageDirectoryPath;

};

#endif // RESOURCEMANAGERDIALOG_HPP
