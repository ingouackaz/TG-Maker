
#include "BranchBase.hpp"

char const* const BranchBase::manager_id = "BRC";

unsigned int BranchBase::_res_data_size() const
{
    return sizeof(BranchBase::ResourceData);
}

void const* BranchBase::_res_data() const
{
    return &res_data;
}

void* BranchBase::_res_data()
{
    return &res_data;
}

