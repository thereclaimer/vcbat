#ifndef VCBAT_HPP
#define VCBAT_HPP

#include "vcbat-types.hpp"
#include "vcbat-platform-api.hpp"

struct VCBat{
};

VCBat
vcbat_create_and_initialize(
    VCBatPlatformApi platform_api);

#endif //VCBAT_HPP