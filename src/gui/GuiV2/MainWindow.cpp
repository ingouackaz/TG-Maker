#include <iostream>

#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "ResourceManagerDialog.hpp"
#include "EventManagerDialog.hpp"
#include "DatabaseDialog.hpp"
#include "ProjectGeneration.hpp"

#include "Action.hpp"
#include "Branch.hpp"
#include "Event.hpp"
#include "Image.hpp"
#include "Position.hpp"
#include "Sound.hpp"
#include "Text.hpp"
#include "Variable.hpp"
#include "ProjectGeneration.hpp"

std::vector<std::pair< std::pair<int,int>,int > > MainWindow::_tilesSelected;
int MainWindow::_tilesSelectedMapWidth = 1;
int MainWindow::_tilesSelectedMapHeight = 1;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //show();

    _mapEditorCanvas = new MapEditorCanvas(ui->mapEditorContainer , QPoint(0, 0), QSize(MAP_EDITOR_SCREEN_WIDTH, MAP_EDITOR_SCREEN_HEIGHT));
    _tileEditorCanvas = new TileEditorCanvas(ui->tileEditorContainer, QPoint(0, 0), QSize(TILE_EDITOR_SCREEN_WIDTH, TILE_EDITOR_SCREEN_HEIGHT));
    ui->mapEditorContainer->show();
    ui->tileEditorContainer->show();
    ui->secondToolBar->setEnabled(false);
    ui->mapToolBar->setEnabled(false);
    ui->listTileSet->setEnabled(false);
    ui->TileSetListLabel->setEnabled(false);
    ui->tileSetNameLabel->setEnabled(false);
    ui->actionPen_mode->setCheckable(true);
    ui->actionRectangle_mode->setCheckable(true);
    ui->actionFill_mode->setCheckable(true);
    ui->actionCollision_Mode->setCheckable(true);

    ui->actionPen_mode->setEnabled(false);
    ui->actionRectangle_mode->setEnabled(false);
    ui->actionFill_mode->setEnabled(false);
    ui->actionCollision_Mode->setEnabled(false);
    ui->actionDatabase->setEnabled(false);
    ui->actionEvent_mode->setEnabled(false);
    ui->actionResource_manager->setEnabled(false);
    ui->actionSave_Project->setEnabled(false);
    ui->actionClose_Project->setEnabled(false);
    ui->action->setEnabled(false);

    _xCoo.setNum(0);
    _yCoo.setNum(1);
    ui->cooLabel->setText("");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_Project_triggered()
{

    NewProjectDialog newp(this);

    _mapEditorCanvas->setCanvasEnabled(false);
    _tileEditorCanvas->setCanvasEnabled(false);

    newp.exec();
    if (ProjectManager::singleton().isInit())
    {
        if (_tilesSelected.size())
        {
            _tilesSelected[0].first.first = 0;
            _tilesSelected[0].first.second = 0;
            _tilesSelected[0].second = 0;
            _tilesSelectedMapWidth = 1;
            _tilesSelectedMapHeight = 1;
        }
        ui->listTileSet->clear();
        setGuiEnabled(true);
        _tileEditorCanvas->initAllTileSet();
        _mapEditorCanvas->setCanvasEnabled(true);
        _tileEditorCanvas->setCanvasEnabled(true);
    }
}

void MainWindow::on_actionOpen_Project_triggered()
{
    ActionManager::singleton();
    BranchManager::singleton();
    EventManager::singleton();
    ImageManager::singleton();
    PositionManager::singleton();
    SoundManager::singleton();
    TextManager::singleton();
    VariableManager::singleton();


    QString path = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                "",
                                                tr("Files (*.tgmproj)"));

    if (path != "")
    {
        ProjectManager::singleton().clear();
        ui->listTileSet->clear();
        if (_tilesSelected.size())
        {
            _tilesSelected[0].first.first = 0;
            _tilesSelected[0].first.second = 0;
            _tilesSelected[0].second = 0;
            _tilesSelectedMapWidth = 1;
            _tilesSelectedMapHeight = 1;
        }

        std::string buf = path.toStdString();
        buf = buf.substr(0, buf.find(".tgmproj"));

        ProjectManager::singleton().setProjectPath(buf.substr(0, buf.find_last_of('/') + 1).c_str());
        ProjectManager::singleton().setProjectName(buf.substr(buf.find_last_of('/') + 1).c_str());
        ProjectManager::singleton().deserialize(path.toStdString());

        setGuiEnabled(true);
        _tileEditorCanvas->initAllTileSet();
    }
}

void MainWindow::on_actionSave_Project_triggered()
{
    ProjectManager::singleton().serialize((ProjectManager::singleton().getProjectPath() + ProjectManager::singleton().getProjectName() + ".tgmproj").toStdString());
}


void MainWindow::on_actionClose_Project_triggered()
{
    CloseProjectDialog newp(this);

    if (newp.exec())
    {
        ProjectManager::singleton().clear();
        // enlever selection
        //        ui->listTileSet->cu
        if (_tilesSelected.size())
        {
            _tilesSelected[0].first.first = 0;
            _tilesSelected[0].first.second = 0;
            _tilesSelected[0].second = 0;
            _tilesSelectedMapWidth = 1;
            _tilesSelectedMapHeight = 1;
        }
        ui->listTileSet->clear();
        setGuiEnabled(false);
    }
}

void MainWindow::on_actionDatabase_activated()
{
    DatabaseDialog res_datad(this);

    res_datad.exec();
}

void MainWindow::on_actionEvent_mode_activated()
{
    EventManagerDialog eventd(this);

    eventd.exec();
}

void MainWindow::on_actionResource_manager_activated()
{
    ResourceManagerDialog resd(this);

    resd.exec();
    // update res
    initTileSetList();
}

void MainWindow::on_actionPen_mode_activated(int arg1)
{
    if (ui->actionPen_mode->isCheckable())
    {
        _tileEditorCanvas->setCursorMode(PEN_CURSOR_MODE);
        _mapEditorCanvas->setCursorMode(PEN_CURSOR_MODE);
        ui->actionPen_mode->setChecked(true);
        ui->actionRectangle_mode->setChecked(false);
        ui->actionFill_mode->setChecked(false);
    }
}

void MainWindow::on_actionRectangle_mode_activated(int arg1)
{
    if (ui->actionRectangle_mode->isCheckable())
    {
        _tileEditorCanvas->setCursorMode(RECT_CURSOR_MODE);
        _mapEditorCanvas->setCursorMode(RECT_CURSOR_MODE);
        ui->actionPen_mode->setChecked(false);
        ui->actionRectangle_mode->setChecked(true);
        ui->actionFill_mode->setChecked(false);
    }
}

void MainWindow::on_actionFill_mode_activated(int arg1)
{
    if (ui->actionFill_mode->isCheckable())
    {
        _tileEditorCanvas->setCursorMode(FILL_CURSOR_MODE);
        _mapEditorCanvas->setCursorMode(FILL_CURSOR_MODE);
        ui->actionPen_mode->setChecked(false);
        ui->actionRectangle_mode->setChecked(false);
        ui->actionFill_mode->setChecked(true);
    }
}

void MainWindow::on_actionRectangle_mode_triggered()
{
}


void    MainWindow::setGuiEnabled(bool state)
{
    if (state == true)
    {
        this->setWindowTitle("TG Maker");
        //        activer toolbar et sfml
        ui->secondToolBar->setEnabled(true);
        ui->mapToolBar->setEnabled(true);
        _tileEditorCanvas->setCanvasEnabled(true);
        _mapEditorCanvas->setCanvasEnabled(true);
        // Initialiser la liste des TileSets
        initTileSetList();
        initMapList();
        ui->TileSetListLabel->setEnabled(true);
        ui->tileSetNameLabel->setEnabled(true);

        ui->actionPen_mode->setEnabled(true);
        ui->actionRectangle_mode->setEnabled(true);
        ui->actionFill_mode->setEnabled(true);
        ui->actionCollision_Mode->setEnabled(true);
        ui->actionDatabase->setEnabled(true);
        ui->actionEvent_mode->setEnabled(true);
        ui->actionResource_manager->setEnabled(true);
        ui->actionSave_Project->setEnabled(true);
        ui->actionClose_Project->setEnabled(true);
        ui->action->setEnabled(true);
        connect(ui->listTileSet, SIGNAL (doubleClicked (const QModelIndex & )), this,
                SLOT (listTileSedoubleclicked(const QModelIndex & )));
    }
    else
    {
        //phand
        ui->listTileSet->setEnabled(false);
        ui->secondToolBar->setEnabled(false);
        ui->mapToolBar->setEnabled(false);
        _tileEditorCanvas->setCanvasEnabled(false);
        _mapEditorCanvas->setCanvasEnabled(false);

        ui->actionPen_mode->setEnabled(false);
        ui->actionRectangle_mode->setEnabled(false);
        ui->actionFill_mode->setEnabled(false);
        ui->actionCollision_Mode->setEnabled(false);
        ui->actionDatabase->setEnabled(false);
        ui->actionEvent_mode->setEnabled(false);
        ui->actionResource_manager->setEnabled(false);
        ui->actionSave_Project->setEnabled(false);
        ui->actionClose_Project->setEnabled(false);
        ui->action->setEnabled(false);
    }
}


void    MainWindow::initTileSetList()
{
    ui->listTileSet->setEnabled(true);
    ui->listTileSet->clear();
    for (ImageManager::iterator it = ImageManager::singleton().begin(); it != ImageManager::singleton().end(); ++it)
    {
        ui->listTileSet->addItem(new QListWidgetItem(QString((*it).second->getFileName().c_str())));
    }
}

void    MainWindow::initMapList()
{

}

void MainWindow::listTileSedoubleclicked(const QModelIndex & index)
{

}

void MainWindow::on_actionCollision_Mode_activated()
{
    if (ui->actionCollision_Mode->isChecked())
    {
        _mapEditorCanvas->setMapMode(1);
        _tileEditorCanvas->setCanvasEnabled(false);
    }
    else
    {
        _mapEditorCanvas->setMapMode(0);

        _tileEditorCanvas->setCanvasEnabled(true);
    }
}

void MainWindow::on_actionHelp_activated()
{

}





void MainWindow::on_listTileSet_activated(const QModelIndex &index)
{
    /*
    if (_tileEditorCanvas != 0)
    {
        ui->tileSetNameLabel->setText(ui->listTileSet->currentItem()->text());
        _tileEditorCanvas->updateTileSet(index.row());
    }
    */
}

void MainWindow::on_listTileSet_itemChanged(QListWidgetItem *item)
{

}

void MainWindow::on_listTileSet_currentRowChanged(int currentRow)
{
    if (currentRow >= 0 && currentRow < ui->listTileSet->count())
        if (_tileEditorCanvas && ui->listTileSet->count())
        {
            ui->tileSetNameLabel->setText(ui->listTileSet->currentItem()->text());
            _tileEditorCanvas->updateTileSet(currentRow);
        }
}

void MainWindow::on_action_activated()
{
    try{
        ProjectManager::singleton().serialize((ProjectManager::singleton().getProjectPath() + ProjectManager::singleton().getProjectName() + ".tgmproj").toStdString());
        ProjectGeneration::generate();
    }
    catch(std::string& s)
    {
        std::cerr << s << std::endl;
    }
}
