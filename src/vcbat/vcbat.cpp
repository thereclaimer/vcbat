#pragma once

#include "vcbat.hpp"

internal VCBat
vcbat_create_and_initialize(
    VCBatPlatformApi platform_api) {

    VCBat vcbat = {0};

    VCBAT_ASSERT(platform_api.memory_allocate);
    VCBAT_ASSERT(platform_api.memory_free);
    VCBAT_ASSERT(platform_api.file_size);
    VCBAT_ASSERT(platform_api.file_open);
    VCBAT_ASSERT(platform_api.file_close);
    VCBAT_ASSERT(platform_api.file_write);
    VCBAT_ASSERT(platform_api.file_read);

    vcbat_platform_api = platform_api;

    vcbat.imgui  = vcbat_imgui_create_and_initialize();
    vcbat.memory = vcbat_memory_create_and_initialize();

    return(vcbat);
}

internal void
vcbat_update(
    VCBatRef vcbat_ref) {

    vcbat_ref.imgui.show_demo_window = true;
    vcbat_ref.imgui.show_cl_options  = true;

    vcbat_imgui_update(vcbat_ref.imgui);
}
