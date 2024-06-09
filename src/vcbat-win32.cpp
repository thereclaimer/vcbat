#pragma once

#include "vcbat-win32.hpp"
#include "vcbat-win32-window.cpp"
#include "vcbat-win32-opengl.cpp"
#include "vcbat-win32-imgui.cpp"
#include "vcbat-win32-platform-api.cpp"
#include "vcbat.cpp"

s32 
vcbat_win32_main(
    HINSTANCE instance, 
    HINSTANCE prev_instance, 
    PWSTR     cmd_line, 
    s32       cmd_show) {

    VCBatWin32Window window = 
        vcbat_win32_window_create(
            instance,
            cmd_show);

    VCBatPlatformApi win32_platform_api = 
        vcbat_win32_platform_api_create_and_init();

    VCBat vcbat = 
        vcbat_create_and_initialize(win32_platform_api);

    b8 running = true;

    while(running && !window.quit) {

        running = vcbat_win32_window_update_and_render(&window);

        vcbat_update(vcbat);
    }

    return(0);
} 