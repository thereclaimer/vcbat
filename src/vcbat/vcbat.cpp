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

    vcbat.imgui      = vcbat_imgui_create_and_initialize();
    vcbat.memory_ptr = vcbat_memory_create_and_initialize();

    VCBatMemoryInfo memory_info = {0};
    vcbat_memory_info(memory_info);


    return(vcbat);
}

internal b8
vcbat_update(
    VCBatRef vcbat_ref) {

    b8 running = true;

    vcbat_ref.imgui.show_cl_options  = true;
    vcbat_ref.imgui.show_main_window = true;

    vcbat_imgui_update(vcbat_ref.imgui);

    running &= !vcbat_ref.imgui.menu_bar.menu_file_item_exit;

    return(running);
}
