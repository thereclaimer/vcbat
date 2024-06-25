#pragma once

#include "vcbat-gui.hpp"

global VCBatGuiMenuBar vcbat_gui_menu_bar;

internal VCBatGuiMenuBarPtr
vcbat_gui_menu_bar_create_and_initialize() {

    vcbat_gui_menu_bar = {0};

    return(&vcbat_gui_menu_bar);
}

internal void
vcbat_gui_menu_bar_render() {
    
    if (ImGui::BeginMainMenuBar()) {

        if (ImGui::BeginMenu("File")) {

            ImGui::MenuItem("Exit",NULL,&vcbat_gui_menu_bar.menu_file_item_exit);

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View")) {

            ImGui::MenuItem("Demo",NULL,&vcbat_gui_menu_bar.menu_view_item_demo);

            ImGui::EndMenu();
        }
    
        ImGui::BeginMenuBar();
    }

    if (vcbat_gui_menu_bar.menu_view_item_demo) {
        ImGui::ShowDemoWindow(&vcbat_gui_menu_bar.menu_view_item_demo);
    }

}
