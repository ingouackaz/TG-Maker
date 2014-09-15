
#include "TextBase.hpp"

char const* const TextBase::manager_id = "TXT";

unsigned int TextBase::_res_data_size() const
{
    return sizeof(TextBase::ResourceData);
}

void const* TextBase::_res_data() const
{
    return &res_data;
}

void* TextBase::_res_data()
{
    return &res_data;
}

