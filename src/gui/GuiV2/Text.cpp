#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include "Text.hpp"
#include "ProjectManager.hpp"
#include <iostream>

Text::Text()
  : _text(""), _loaded(false)
{

}

Text::Text(const std::string &path)
  : _text(""), _loaded(false)
{
    setPath(path.c_str());
}

void Text::load()
{
  
}

const std::string &Text::getText()
{
  int fd, size;
  char *ptr;

  if (!_loaded)
    {
      _loaded = !(-1 == (fd = open((ProjectManager::singleton().getProjectPath().toStdString() + "res/txt/" + res_data.path).c_str(), O_RDONLY))
		  || ((off_t)-1 == (size = lseek(fd, 0, SEEK_END)))
		  || ((off_t)-1 == lseek(fd, 0, SEEK_SET))
		  || (NULL == (ptr = (char *)malloc(size + 1)))
		  || (size > read(fd, ptr, size))
		  || -1 == close(fd));
      if (_loaded)
	{
	  ptr[size] = '\0';
	  _text = ptr;
	}
      else
	_text = "";
      return _text;
    }
  _loaded = true;
  return _text;
}

void Text::setText(const std::string &text)
{
  int fd;

  _text = "";
  if (-1 == (fd = open((ProjectManager::singleton().getProjectPath().toStdString() + "res/txt/" + res_data.path).c_str(), O_TRUNC | O_WRONLY | O_CREAT, 0777))
      || 0 > write(fd, text.c_str(), text.size())
      || -1 == close(fd))
    return;
  _text = text;
}


TextManager::TextManager()
    : Manager<Text>(Text::manager_id)
{


}

TextManager &TextManager::singleton()
{
    static bool registered(false);
    static TextManager singleton;

    if (!registered)
    {
        ProjectManager::singleton().register_manager(&singleton);

        registered = true;
    }

    return singleton;
}
