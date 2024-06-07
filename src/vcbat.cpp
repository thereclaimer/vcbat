#pragma once

#include "vcbat.hpp"

VCBat
vcbat_create_and_initialize(
    VCBatPlatformApi platform_api) {

    VCBat vcbat = {0};

    return(vcbat);
}
