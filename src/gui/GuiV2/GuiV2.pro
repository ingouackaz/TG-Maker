#-------------------------------------------------
#
# Project created by QtCreator 2012-11-25T14:32:01
#
#-------------------------------------------------

QT       += core gui

INCLUDEPATH += base/include
LIBS +=  base/pfa_base.a -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lQtCore -lQtGui -lX11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GuiV2
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp\
        QSFMLCanvas.cpp\
        TileEditorCanvas.cpp\
        MapEditorCanvas.cpp \
    RectSelection.cpp \
    NewProjectDialog.cpp \
    ProjectManager.cpp \
    ProjectGeneration.cpp \
    Image.cpp \
    Bin2Cpp.cpp \
    Position.cpp \
    Text.cpp \
    Sound.cpp \
    Action.cpp \
    Branch.cpp \
    Event.cpp \
    Variable.cpp \
    CloseProjectDialog.cpp \
    LoadingBarDialog.cpp \
    ResourceManagerDialog.cpp \
    DatabaseDialog.cpp \
    ImgSize.cpp \
    EventManagerDialog.cpp \
    CreateEventDialog.cpp \
    CreateBranchDialog.cpp \
    CreateVariableDialog.cpp \
    CreateActionDialog.cpp \
    CreateTextDialog.cpp \



HEADERS  += MainWindow.hpp \
    TileEditorCanvas.hpp  \
    MapEditorCanvas.hpp  \
    QSFMLCanvas.hpp\
    RectSelection.hpp \
    NewProjectDialog.hpp \
    ProjectManager.hpp \
    ProjectGeneration.hpp \
    Image.hpp \
    Bin2Cpp.hpp \
    Position.hpp \
    Text.hpp \
    Sound.hpp \
    Action.hpp \
    Branch.hpp \
    Event.hpp \
    Variable.hpp \
    CloseProjectDialog.hpp \
    LoadingBarDialog.hpp \
    ResourceManagerDialog.hpp \
    DatabaseDialog.hpp \
    ImgSize.hpp \
    EventManagerDialog.hpp \
    CreateEventDialog.hpp \
    CreateBranchDialog.hpp \
    CreateVariableDialog.hpp \
    CreateActionDialog.hpp \
    CreateTextDialog.hpp \




FORMS    += MainWindow.ui \
    NewProjectDialog.ui \
    CloseProjectDialog.ui \
    LoadingBarDialog.ui \
    ResourceManagerDialog.ui \
    DatabaseDialog.ui \
    EventManagerDialog.ui \
    CreateEventDialog.ui \
    CreateBranchDialog.ui \
    CreateVariableDialog.ui \
    CreateActionDialog.ui \
    CreateTextDialog.ui

header.commands = ./generateHeader.sh
alib.commands = (cd base && make)

QMAKE_EXTRA_TARGETS += header alib
PRE_TARGETDEPS += alib
POST_TARGETDEPS += header





















































































