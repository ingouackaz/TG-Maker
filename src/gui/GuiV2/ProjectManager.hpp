#ifndef PROJECTMANAGER_HPP
#define PROJECTMANAGER_HPP

#include <QString>
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QTextStream>

#include "ProjectManagerBase.hpp"

class ProjectManager : public ProjectManagerBase
{
private:
    ProjectManager();

public:
    static ProjectManager   &singleton();

public:
    QString         getProjectName() const
    {
        return QString(name().c_str());
    }
    void            setProjectName(const QString &projectName)
    {
        set_name(projectName.toStdString());
    }
    QString         getProjectAuthor() const
    {
        return QString(author().c_str());
    }
    void            setProjectAuthor(const QString &projectAuthor)
    {
        set_author(projectAuthor.toStdString());
    }
    const QString   &getProjectPath() const
    {
        return _projectPath;
    }
    void            setProjectPath(const QString &projectPath)
    {
        _projectPath = projectPath;
    }
    int             getXStartCoor() const
    {
        return m_meta.player.x;
    }
    void            setXStartCoor(int x)
    {
        m_meta.player.x = x;
    }
    int             getYStartCoor() const
    {
        return m_meta.player.y;
    }
    void            setYStartCoor(int y)
    {
        m_meta.player.y = y;
    }
    int             getTileSetId() const
    {
        return m_meta.player.image.id;
    }
    void            setTileSetId(int id)
    {
        m_meta.player.image.id = id;
    }
    int             getTileSetX() const
    {
        return m_meta.player.image.at_x ;
    }
    void            setTileSetX(int tileSetX)
    {
        m_meta.player.image.at_x = tileSetX;
    }
    int             getTileSetY() const
    {
        return m_meta.player.image.at_y ;
    }
    void            setTileSetY(int tileSetY)
    {
        m_meta.player.image.at_y = tileSetY;
    }

    bool            isInit() const
    {
        return _isInit;
    }


public:
    void            initProject(QString projectName, QString projectPath);
    void            clear();
    void            deserialize(const std::string &path);


private:
    bool            _isInit;
    QString         _projectPath;

};

#endif // PROJECTMANAGER_HPP
