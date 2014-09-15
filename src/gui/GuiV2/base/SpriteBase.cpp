
#include "SpriteBase.hpp"

char const* const SpriteBase::manager_id = "SPR";

unsigned int SpriteBase::_res_data_size() const
{
    return sizeof(SpriteBase::ResourceData);
}

void const* SpriteBase::_res_data() const
{
    return &res_data;
}

void* SpriteBase::_res_data()
{
    return &res_data;
}

