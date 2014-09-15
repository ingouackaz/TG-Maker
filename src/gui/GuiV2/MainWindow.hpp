#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QModelIndex>
#include <QListWidgetItem>

#include "CloseProjectDialog.hpp"
#include "TileEditorCanvas.hpp"
#include "MapEditorCanvas.hpp"
#include "ProjectManager.hpp"
#include "NewProjectDialog.hpp"
#include "RectSelection.hpp"

#define SCALE_CURSOR_MODE 9

#define PEN_CURSOR_MODE     0
#define RECT_CURSOR_MODE    1
#define FILL_CURSOR_MODE    2

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
    void on_actionNew_Project_triggered();
    void on_actionClose_Project_triggered();
    void on_actionPen_mode_activated(int arg1);
    void on_actionRectangle_mode_activated(int arg1);
    void on_actionRectangle_mode_triggered();
    void on_actionFill_mode_activated(int arg1);
    void on_actionOpen_Project_triggered();
    void on_actionSave_Project_triggered();
    void listTileSedoubleclicked(const QModelIndex &);

    void on_actionCollision_Mode_activated();


    void on_actionHelp_activated();

    void on_actionResource_manager_activated();

    void on_actionDatabase_activated();

    void on_actionEvent_mode_activated();

    void on_listTileSet_activated(const QModelIndex &index);

    void on_listTileSet_itemChanged(QListWidgetItem *item);

    void on_listTileSet_currentRowChanged(int currentRow);

    void on_action_activated();

private:
    void        setGuiEnabled(bool state);
    void        initTileSetList();
    void        initMapList();

private:
    Ui::MainWindow *ui;
    MapEditorCanvas  *_mapEditorCanvas;
    TileEditorCanvas *_tileEditorCanvas;
    QString         _xCoo;
    QString         _yCoo;
    // Commmunication between TileScreen & MapScreen
public:
    static    std::vector<std::pair< std::pair<int,int>,int > > _tilesSelected;
    static    int _tilesSelectedMapWidth;
    static    int _tilesSelectedMapHeight;
};

#endif // MAINWINDOW_HPP
