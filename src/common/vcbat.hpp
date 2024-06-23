#ifndef VCBAT_HPP
#define VCBAT_HPP

#include "vcbat-types.hpp"
#include "vcbat-platform-api.hpp"
#include "vcbat-dependencies.hpp"
#include "vcbat-memory.hpp"

//-------------------------------------------------
// IMGUI
//-------------------------------------------------

struct VCBatImGui {
    b8 show_demo_window;
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
    VCBatMemoryPtr memory;
};

typedef VCBat& VCBatRef;

VCBat
vcbat_create_and_initialize(
    VCBatPlatformApi platform_api);

void
vcbat_update(
    VCBatRef vcbat_ref);


#endif //VCBAT_HPP