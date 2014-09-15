
#include "ActionBase.hpp"

char const* const ActionBase::manager_id = "ACT";

unsigned int ActionBase::_res_data_size() const
{
    return sizeof(ActionBase::ResourceData);
}

void const* ActionBase::_res_data() const
{
    return &res_data;
}

void* ActionBase::_res_data()
{
    return &res_data;
}

