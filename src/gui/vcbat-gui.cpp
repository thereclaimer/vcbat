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

internal void
vcbat_gui_windows_load_all() {

    VCBatGuiWindows& windows = vcbat_gui.windows;
    windows.build_script   = vcbat_gui_build_script_window_create_and_initialize();
    windows.build_settings = vcbat_gui_build_settings_window_create_and_initialize();
    windows.cl_options     = vcbat_gui_cl_options_create_and_initialize();

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
vcbat_gui_dockspace() {
ImGuiDockNodeFlags dock_node_flags = 
        ImGuiDockNodeFlags_NoResize |
        ImGuiDockNodeFlags_NoUndocking;

    ImVec2 main_window_pos  = ImGui::GetWindowPos();
    ImVec2 main_window_size = ImGui::GetWindowSize();

    if (!vcbat_gui.dockspace.dock_node_id) {

        //create the dock node id
        vcbat_gui.dockspace.dock_node_id = ImGui::GetID("DockNode");
        ImGui::DockBuilderRemoveNode(vcbat_gui.dockspace.dock_node_id);
        ImGui::DockBuilderAddNode(vcbat_gui.dockspace.dock_node_id,dock_node_flags);

        //set the dock node dimensions
        ImGui::DockBuilderSetNodePos(vcbat_gui.dockspace.dock_node_id, main_window_pos);
        ImGui::DockBuilderSetNodeSize(vcbat_gui.dockspace.dock_node_id,main_window_size);

        vcbat_gui.dockspace.output_node_id  = ImGui::DockBuilderSplitNode(vcbat_gui.dockspace.dock_node_id,    ImGuiDir_Left, 0.5f, NULL, &vcbat_gui.dockspace.dock_node_id);
        vcbat_gui.dockspace.control_node_id = ImGui::DockBuilderSplitNode(vcbat_gui.dockspace.output_node_id,  ImGuiDir_Left, 0.5f, NULL, &vcbat_gui.dockspace.output_node_id);
        vcbat_gui.dockspace.options_node_id = ImGui::DockBuilderSplitNode(vcbat_gui.dockspace.control_node_id, ImGuiDir_Down, 0.5f, NULL, &vcbat_gui.dockspace.control_node_id);

        ImGui::DockBuilderDockWindow(VCBAT_GUI_BUILD_SCRIPT_WINDOW_TITLE,   vcbat_gui.dockspace.output_node_id);
        ImGui::DockBuilderDockWindow(VCBAT_GUI_DEMO,                        vcbat_gui.dockspace.output_node_id);
        ImGui::DockBuilderDockWindow(VCBAT_GUI_BUILD_SETTINGS_WINDOW_TITLE, vcbat_gui.dockspace.control_node_id);
        ImGui::DockBuilderDockWindow(VCBAT_GUI_CL_OPTIONS_TITLE,            vcbat_gui.dockspace.options_node_id);

        ImGui::DockBuilderFinish(vcbat_gui.dockspace.dock_node_id);

        return;
    }

    ImGuiID dock_node_id = ImGui::GetID("DockNode");
    ImGui::DockBuilderSetNodePos(dock_node_id, main_window_pos);
    ImGui::DockBuilderSetNodeSize(dock_node_id,main_window_size);    
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

    vcbat_gui_dockspace();

    vcbat_gui_cl_options_render();
    vcbat_gui_build_script_window_render();
    vcbat_gui_build_settings_window_render();

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

internal u32
vcbat_gui_text_width_pixels(
    const char* text) {

    u32 char_width_pixels = ImGui::CalcTextSize("A").x;
    u32 text_length       = strlen(text);
    u32 text_width_pixels = char_width_pixels * text_length;  

    return(text_width_pixels);
}