
#include "SoundBase.hpp"

char const* const SoundBase::manager_id = "SND";

unsigned int SoundBase::_res_data_size() const
{
    return sizeof(SoundBase::ResourceData);
}

void const* SoundBase::_res_data() const
{
    return &res_data;
}

void* SoundBase::_res_data()
{
    return &res_data;
}

