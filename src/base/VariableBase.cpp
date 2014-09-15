
#include "VariableBase.hpp"

char const* const VariableBase::manager_id = "VAR";

unsigned int VariableBase::_res_data_size() const
{
    return sizeof(VariableBase::ResourceData);
}

void const* VariableBase::_res_data() const
{
    return &res_data;
}

void* VariableBase::_res_data()
{
    return &res_data;
}

