#ifndef HPP_BIN2CPP_
# define HPP_BIN2CPP_
# include <string>

namespace Bin2Cpp{
  
  enum restype{
    RES_SOUND,
    RES_TEXT,
    RES_IMAGE,
    RES_POS,
  };
  
  int addResource(restype, int, void *, std::string&);
  
};

#endif
