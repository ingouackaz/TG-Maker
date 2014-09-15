
#include <cstring>
#include <unistd.h>

#include "AResource.hpp"

AResource::~AResource()
{
}

bool AResource::serialize(int fd) const
{
    write(fd, _res_data(), _res_data_size());
    return true;
}

void AResource::deserialize(void const* res_data)
{
    memcpy(_res_data(), res_data, _res_data_size());
}

