#ifndef TEXT_HPP
#define TEXT_HPP

#include "Manager.hpp"
#include "TextBase.hpp"

class Text : public TextBase
{
public:
    Text();
    Text(const std::string &path);

public:
    std::string getPath() const
    {
        return std::string(res_data.path);
    }
    void setPath(const std::string &path)
    {
        strncpy(res_data.path, path.c_str(), sizeof(res_data.path));
        res_data.path[sizeof(res_data.path) - 1] = 0;
    }
  const std::string &getText();
  void setText(const std::string &);
    

public:
    void load();

private:
    std::string     _text;
    bool	    _loaded;
};

class TextManager : public Manager<Text>
{
private:
    TextManager();

public:
    static TextManager &singleton();
};

#endif // TEXT_HPP
