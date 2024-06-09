#ifndef VCBAT_HPP
#define VCBAT_HPP

#include "vcbat-types.hpp"
#include "vcbat-platform-api.hpp"
#include "vcbat-imgui.hpp"

struct VCBat{
    VCBatImGui imgui;
};

typedef VCBat& VCBatRef;

VCBat
vcbat_create_and_initialize(
    VCBatPlatformApi platform_api);

void
vcbat_update(
    VCBatRef vcbat_ref);

#endif //VCBAT_HPP