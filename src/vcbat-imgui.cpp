#pragma once

#include "vcbat.hpp"

VCBatImGui
vcbat_imgui_create_and_initialize() {
    
    VCBatImGui vcbat_imgui = {0};
    
    return(vcbat_imgui);
};

void
vcbat_imgui_update(
    VCBatImGuiRef vcbat_imgui_ref) {

    ImGui::ShowDemoWindow(&vcbat_imgui_ref.show_demo_window);
}