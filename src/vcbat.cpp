#pragma once

#include "vcbat.hpp"

internal VCBat
vcbat_create_and_initialize(
    VCBatPlatformApi platform_api) {

    VCBat vcbat = {0};

    vcbat.imgui = vcbat_imgui_create_and_initialize();

    return(vcbat);
}

internal void
vcbat_update(
    VCBatRef vcbat_ref) {

    vcbat_ref.imgui.show_demo_window = true;

    vcbat_imgui_update(vcbat_ref.imgui);
}
