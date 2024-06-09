#ifndef VCBAT_IMGUI_HPP
#define VCBAT_IMGUI_HPP

#include "vcbat-types.hpp"
#include "vcbat-dependencies.hpp"

struct VCBatImGui {
    b8 show_demo_window;
};

typedef VCBatImGui& VCBatImGuiRef;

VCBatImGui
vcbat_imgui_create_and_initialize();

void
vcbat_imgui_update(
    VCBatImGuiRef vcbat_imgui_ref);

#endif //VCBAT_IMGUI_HPPs