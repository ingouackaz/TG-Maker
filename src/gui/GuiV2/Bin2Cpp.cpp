#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <cstdio>
#include <sstream>
#include <unistd.h>
#include "Bin2Cpp.hpp"
#include "ResourceHeaders.hpp"
#include "Position.hpp"
//action, branche, event, image, variable, texte, son, position

bool loldump(char const *path, std::string& s, int& fsize){
  char buf[512];
  char subbuf[32];
  int sz;
  int fd;

  if (-1 == (fd = open(path, O_RDONLY)))
    return false;
  if ((off_t)-1 == (fsize = lseek(fd, 0, SEEK_END))
      || ((off_t)-1 == lseek(fd, 0, SEEK_SET)))
    return false;
  while (0 < (sz = read(fd, &buf, 512)))
    {
      int i = -1;
      while (++i < sz)
	{
	  sprintf(subbuf, "\\x%x", (unsigned int)(unsigned char)(buf[i]));
	  s.append(subbuf);
	}
    }
  close(fd);
  return true;
}

int Bin2Cpp::addResource(Bin2Cpp::restype t, int id, void *r, std::string& s){
  std::ostringstream oss("");
  std::ostringstream oss2("");
  Image *img = (Image *)r;
  Position *pos = (Position *)r;
  int fsize;  
  std::string path = ProjectManager::singleton().getProjectPath().toStdString();
  std::string tmp;

  path += "/res/";
  switch (t){    
  case RES_IMAGE:
    
    oss << "_img[" << id << "] = new sf::Image();" << std::endl;
    oss << "_img[" << id << "]->LoadFromMemory(\"";
    if (!loldump((path + "img/" + img->res_data.path).c_str(), tmp, fsize))
      return 0;
    oss << tmp << "\", " << fsize << ");" << std::endl;
    oss << "_img[" << id << "]->SetSmooth(false);" << std::endl << std::endl;
    break;

  case RES_POS:
    
    oss2 << "_pos[" << pos->getMapX() << "][" << pos->getMapY() << "]";
    tmp = oss2.str();
    oss << tmp << " = (Position *)malloc(sizeof(Position));" << std::endl;
    oss << tmp << "->s = new sf::Sprite(*(_img[" << pos->getTilesetId() << "]));" << std::endl;
    oss << tmp << "->s->SetSubRect(sf::IntRect("
	<< pos->getTilesetX() * 32 << ", "
	<< pos->getTilesetY() * 32 << ", "
	<< pos->getTilesetX() * 32 + 32 << ", "
	<< pos->getTilesetY() * 32 + 32 << "));" << std::endl;
    oss << tmp << "->collision = " << pos->getCollision() << ";" << std::endl;
    break;

  };
  s += oss.str();
  return fsize;
}
