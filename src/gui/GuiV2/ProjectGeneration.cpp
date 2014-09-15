#include <string>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include "ProjectGeneration.hpp"
#include "Bin2Cpp.hpp"
#include "ResourceHeaders.hpp"

void leldump(const char *const src, std::string& dst){
  int i = -1;
  char buf[32];

  while (src[++i])
    {
      sprintf(buf, "\\x%2x", (unsigned int)(src[i]));
      dst += buf;
    }
}

void topleldump(std::string& s, char const *t, int i, std::vector<std::string> const& ss){
  std::ostringstream oss;
  std::string var;

  oss << "tmp" << t << i;
  var = oss.str();
  oss.str("");
  oss << t << " *" << var << " = new " << t << "();" << std::endl;
  for(std::vector<std::string>::const_iterator cit = ss.begin(); cit != ss.end(); ++cit)
    oss << var << (*cit) << std::endl;
  oss << t << "Manager::singleton()[" << i << "] = " << var << ";" << std::endl << std::endl;
  s += oss.str();
}

void ProjectCodeGeneration(std::string& hdr){
  int fsize;
  char sint[32];

  std::string res;
  std::vector<std::string> sset;
  std::ostringstream oss("");

  hdr = "#include <string>\n#include <vector>\n#include <cstdlib>\n#include <SFML/Graphics.hpp>\n#include <SFML/System.hpp>\n#include <iostream>\n#include <unistd.h>\n\n";
  hdr += "struct Position{ sf::Sprite *s; bool collision;};\n\n";
  hdr += "std::vector<sf::Image *> _img(100);\nPosition *_pos[100][100];\n";
  hdr += "std::string _project_name(\"" + ProjectManager::singleton().getProjectName().toStdString() + "\");\n";
  hdr += "std::string _project_author(\"" + ProjectManager::singleton().getProjectAuthor().toStdString() + "\");\n";
  oss << ProjectManager::singleton().getXStartCoor() << ", " << ProjectManager::singleton().getYStartCoor();
  hdr += "sf::Vector2f _start_pos(" + oss.str() + ");\n\n";
  hdr += "void load(){\n";

  ImageManager& im = ImageManager::singleton();
  for (ImageManager::const_iterator cit = im.begin(); cit != im.end(); ++cit){
    fsize = Bin2Cpp::addResource(Bin2Cpp::RES_IMAGE, cit->first, cit->second, hdr);
    if (fsize <= 0)
      throw (std::string("File not found: ") + cit->second->res_data.path);
  }

  PositionManager& pm = PositionManager::singleton();
  for (PositionManager::const_iterator cit = pm.begin(); cit != pm.end(); ++cit){
    Bin2Cpp::addResource(Bin2Cpp::RES_POS, 0, cit->second, hdr);
  }
 
  hdr += "\n}\n\n";

  chdir("game2");
  system("cat DAPROJECT.cpp | grep -v '#include' > ../.project_code");
  chdir("..");


  int fd, sz;
  char buf[513];

  if (-1 == (fd = open(".project_code", O_RDONLY)))
    throw std::string("Code body generation failed");
  while (0 < (sz = read(fd, &buf, 512)))
    {
      buf[sz] = '\0';
      hdr += buf;
    }
  close(fd);
}

void ProjectGeneration::generate(){
  std::string code;
  int fd, ret;
  std::string const& path = ProjectManager::singleton().getProjectPath().toStdString();
  std::string const& name = ProjectManager::singleton().getProjectName().toStdString();

  ProjectCodeGeneration(code);
  system("echo \"#!/bin/sh\n\n\" > .installer");
  system((std::string("echo \"game=\\\"") + name + "\\\"\" >> .installer").c_str());
  system("cat .template.do_not_alter >> .installer");
  if (-1 == (fd = open(".project_code", O_WRONLY | O_TRUNC)))
    throw std::string("Code body dump failed");
  code = "\n" + code + "\n";
  write(fd, code.c_str(), code.size());
  close(fd);
  ret = system("gzip .project_code && base64 .project_code.gz >> .installer && chmod +x .installer && rm -f .project_code.gz");
  if (ret < 0 || WEXITSTATUS(ret))
    throw std::string("Installer creation error");
  system((std::string("rm -rf \"") + name + "__install.sh\" README.txt Game.zip").c_str());
  ret = system((std::string("cp .installer \"") + name + "__install.sh\" && cp .readme README.txt && zip Game \"" + name + "__install.sh\" README.txt && cp Game.zip \"" + path + "\" && echo 'Game exported'").c_str());
  if (ret < 0 || WEXITSTATUS(ret))
    throw std::string("Export error");
}
