#include <QImage>
#include "ImgSize.hpp"

bool ImgSize::checkImgXY(char const * s){
  QImage img(s);

  if (img.width() < 256 || img.height() < 544)
    return false;
  return true;
}
