#ifndef VCBAT_HPP
#define VCBAT_HPP

#include "vcbat-types.hpp"
#include "vcbat-platform-api.hpp"
#include "vcbat-dependencies.hpp"
#include "vcbat-memory.hpp"
#include "vcbat-string.hpp"
#include "vcbat-cl.hpp"

//-------------------------------------------------
// IMGUI
//-------------------------------------------------

struct VCBatImGuiMenuBar {
    b8 menu_file_item_exit;
    b8 menu_view_item_demo;
};

typedef VCBatImGuiMenuBar* VCBatImGuiMenuBarPtr;
typedef VCBatImGuiMenuBar& VCBatImGuiMenuBarRef;

struct VCBatImGuiDockNodes{
    ImGuiID dock_group;
    ImGuiID left_panel;
    ImGuiID right_panel;
};

struct VCBatImGui {
    b8                  show_demo_window;
    b8                  show_cl_options;
    b8                  show_main_window;
    VCBatImGuiMenuBar   menu_bar;
    VCBatImGuiDockNodes dock_nodes;
};

typedef VCBatImGui& VCBatImGuiRef;

VCBatImGui
vcbat_imgui_create_and_initialize();

void
vcbat_imgui_update(
    VCBatImGuiRef vcbat_imgui_ref);

//-------------------------------------------------
// CORE
//-------------------------------------------------

struct VCBat{
    VCBatImGui     imgui;
    VCBatMemoryPtr memory_ptr;
    VCBatClPtr     cl_ptr;
};

typedef VCBat& VCBatRef;

VCBat
vcbat_create_and_initialize(
    VCBatPlatformApi platform_api);

b8
vcbat_update(
    VCBatRef vcbat_ref);


#endif //VCBAT_HPP