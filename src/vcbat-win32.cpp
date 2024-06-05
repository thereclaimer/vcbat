#pragma once

#include "vcbat-win32.hpp"
#include "vcbat-win32-window.cpp"


int 
vcbat_win32_main(
    HINSTANCE instance, 
    HINSTANCE prev_instance, 
    PWSTR     cmd_line, 
    s32       cmd_show) {

    VCBatWin32Window window = 
        vcbat_win32_window_create(
            instance,
            cmd_show);

    b8 running = true;

    while(running) {

        running = vcbat_win32_window_update_and_render(window);
    }

    return(0);
}