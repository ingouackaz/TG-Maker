
#include "EventBase.hpp"

char const* const EventBase::manager_id = "EVT";

unsigned int EventBase::_res_data_size() const
{
    return sizeof(EventBase::ResourceData);
}

void const* EventBase::_res_data() const
{
    return &res_data;
}

void* EventBase::_res_data()
{
    return &res_data;
}

