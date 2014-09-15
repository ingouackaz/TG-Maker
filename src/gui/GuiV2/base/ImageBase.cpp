
#include "ImageBase.hpp"

char const* const ImageBase::manager_id = "IMG";

unsigned int ImageBase::_res_data_size() const
{
    return sizeof(ImageBase::ResourceData);
}

void const* ImageBase::_res_data() const
{
    return &res_data;
}

void* ImageBase::_res_data()
{
    return &res_data;
}

