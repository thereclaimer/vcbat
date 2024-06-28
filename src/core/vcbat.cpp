#pragma once

#include "vcbat-core.hpp"

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
    VCBAT_ASSERT(platform_api.file_dialog);

    vcbat_platform_api = platform_api;

    vcbat.memory_ptr       = vcbat_memory_create_and_initialize();
    vcbat.build_script_ptr = vcbat_build_script_create_and_initialize();
    vcbat.gui_ptr          = vcbat_gui_create_and_initialize();

    return(vcbat);
}

internal b8
vcbat_update(
    VCBatRef vcbat_ref) {

    b8 running = true;

    vcbat_gui_render();

    return(running);
}
