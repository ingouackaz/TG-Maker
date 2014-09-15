#include "ProjectManager.hpp"

ProjectManager::ProjectManager()
    : _isInit(false)
{

}

ProjectManager  &ProjectManager::singleton()
{
    static ProjectManager pm_singleton;

    return pm_singleton;
}

void        ProjectManager::initProject(QString projectName, QString projectPath)
{
    QDir lDir;

    // creation de l'arbo du projet
    lDir.mkdir( projectPath + "/" + projectName );
    lDir.mkdir( projectPath + "/" + projectName +  "/res");
    lDir.mkdir( projectPath + "/" + projectName +  "/res/img");
    lDir.mkdir( projectPath + "/" + projectName +  "/res/snd");
    lDir.mkdir( projectPath + "/" + projectName +  "/res/txt");

    QFile file(projectPath + "/" +  projectName + "/" + projectName + ".tgmproj");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    set_name(projectName.toStdString());
    _projectPath = projectPath + "/" + projectName + "/";


    clear();

    _isInit = true;
}

void        ProjectManager::clear()
{
    _isInit = false;
    ProjectManagerBase::clear();
}

void        ProjectManager::deserialize(const std::string &path)
{
    ProjectManagerBase::deserialize(path);
    _isInit = true;
}
