
#include "PositionBase.hpp"

char const* const PositionBase::manager_id = "POS";

unsigned int PositionBase::_res_data_size() const
{
    return sizeof(PositionBase::ResourceData);
}

void const* PositionBase::_res_data() const
{
    return &res_data;
}

void* PositionBase::_res_data()
{
    return &res_data;
}

