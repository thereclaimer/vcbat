#pragma once

#include "vcbat-gui.hpp"

global VCBatGui vcbat_gui;

internal void
vcbat_gui_main_window_config() {

    vcbat_gui.main_window_flags = 
        ImGuiWindowFlags_MenuBar               |
        ImGuiWindowFlags_NoDocking             |
        ImGuiWindowFlags_NoTitleBar            |
        ImGuiWindowFlags_NoCollapse            |
        ImGuiWindowFlags_NoResize              |
        ImGuiWindowFlags_NoMove                |
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoNavFocus            |
        ImGuiWindowFlags_NoBackground;

}

internal void
vcbat_gui_fonts_load_all() {

    ImGuiIO& io = ImGui::GetIO();

    ImFont* font_ui = 
        io.Fonts->AddFontFromMemoryCompressedBase85TTF(
            vcbat_ui_font_compressed_data_base85,
            18.0f);
    
    VCBAT_ASSERT(font_ui);

    vcbat_gui.fonts.ui = font_ui;
}


internal VCBatGuiPtr
vcbat_gui_create_and_initialize() {

    vcbat_gui = {0};

    vcbat_gui_fonts_load_all();
    vcbat_gui_main_window_config();

    vcbat_gui.menu_bar_ptr = vcbat_gui_menu_bar_create_and_initialize();
    VCBAT_ASSERT(vcbat_gui.menu_bar_ptr);

    return(&vcbat_gui);
}


internal void
vcbat_gui_render() {

    vcbat_gui_menu_bar_render();

    ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(main_viewport->WorkPos);
    ImGui::SetNextWindowSize(main_viewport->WorkSize);

    //main window start
    ImGui::Begin(
        VCBAT_GUI_MAIN_WINDOW_TITLE,
        NULL,
        vcbat_gui.main_window_flags);

    //main window end
    ImGui::End();
}

internal VCBatGuiTextSizePixels
vcbat_gui_text_size_pixels() {

    VCBatGuiTextSizePixels text_size = {0};

    text_size.width  = ImGui::CalcTextSize("A").x;
    text_size.height = ImGui::GetTextLineHeightWithSpacing();

    return(text_size);
}