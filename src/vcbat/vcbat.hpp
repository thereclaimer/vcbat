#ifndef VCBAT_HPP
#define VCBAT_HPP

#include "vcbat-types.hpp"
#include "vcbat-platform-api.hpp"
#include "vcbat-dependencies.hpp"
#include "vcbat-cl-options.hpp"

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
// MEMORY
//-------------------------------------------------




//-------------------------------------------------
// STRING
//-------------------------------------------------

#define VCBAT_STRING_MEMORY_SIZE_BYTES VCBAT_MEMORY_KILOBYTES(64)
#define VCBAT_STRING_MAX_SIZE_BYTES    256
#define VCBAT_STRING_MAX_COUNT         (VCBAT_STRING_MEMORY_SIZE_BYTES / VCBAT_STRING_MAX_SIZE_BYTES) 
#define VCBAT_STRING_INVALID           -1

typedef s64 VCBatStringHandle;

struct VCBatString {
    u64   string_buffer_length_bytes;
    char* string_buffer;
};

typedef VCBatString* VCBatStringPtr;
typedef VCBatString& VCBatStringRef;

struct VCBatStringAllocator {
    VCBatMemoryArenaHandle arena_handle;
};

typedef VCBatStringAllocator* VCBatStringAllocatorPtr; 
typedef VCBatStringAllocator& VCBatStringAllocatorRef;

struct VCBatStringManager {
    VCBatStringAllocator string_allocator;
    VCBatString          string_array[VCBAT_STRING_MAX_COUNT];
};  

typedef VCBatStringManager* VCBatStringManagerPtr;
typedef VCBatStringManager& VCBatStringManagerRef;

VCBatStringManager
vcbat_string_manager_create_and_initialize(
    VCBatMemoryRef memory_ref);

inline b8
vcbat_string_valid(
    const VCBatStringHandle string_handle) {

    b8 string_valid = 
        string_handle >= 0 ||
        string_handle < VCBAT_STRING_MAX_COUNT;

    return(string_valid);
}

VCBatStringHandle
vcbat_string_new(
          VCBatStringManagerRef string_manager_ref,
    const char*                 string_val);

void
vcbat_string_delete(
          VCBatStringManagerRef string_manager_ref,
    const VCBatStringHandle     string_handle);

u64
vcbat_string_length(
          VCBatStringManagerRef string_manager_ref,
    const VCBatStringHandle     string_handle);

const char*
vcbat_string_c_str(
          VCBatStringManagerRef string_manager_ref,
    const VCBatStringHandle     string_handle);

//-------------------------------------------------
// CORE
//-------------------------------------------------

struct VCBat{
    VCBatImGui         imgui;
    VCBatMemory        memory;
    VCBatStringManager string_manager;
};

typedef VCBat& VCBatRef;

VCBat
vcbat_create_and_initialize(
    VCBatPlatformApi platform_api);

b8
vcbat_update(
    VCBatRef vcbat_ref);


#endif //VCBAT_HPP