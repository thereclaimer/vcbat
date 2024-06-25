#pragma once

#include "vcbat-gui.hpp"

global VCBatGuiSourcesWindow vcbat_gui_sources_window;

internal VCBatGuiSourcesWindowPtr
vcbat_gui_sources_window_create_and_initialize() {

    vcbat_gui_sources_window = {0};

    return(&vcbat_gui_sources_window);
}

internal void
vcbat_gui_sources_window_render() {

    ImGui::Begin(
        VCBAT_GUI_SOURCES_WINDOW_TITLE,
        NULL,
        vcbat_gui_sources_window.flags);

    ImGui::End();
}  