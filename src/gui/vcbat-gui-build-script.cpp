#pragma once

#include "vcbat-gui.hpp"
#include "vcbat-core.hpp"


global VCBatGuiBuildScriptWindow vcbat_gui_build_script_window;

internal VCBatGuiBuildScriptWindowPtr
vcbat_gui_build_script_window_create_and_initialize() {

    vcbat_gui_build_script_window = {0};

    return(&vcbat_gui_build_script_window);
}

internal void
vcbat_gui_build_script_window_render() {

    ImGui::Begin(
        VCBAT_GUI_BUILD_SCRIPT_WINDOW_TITLE,
        NULL,
        vcbat_gui_build_script_window.flags);

    const char* script_string = vcbat_build_script_string(); 

    ImGui::TextUnformatted(script_string);

    ImGui::End();
}