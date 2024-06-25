#ifndef VCBAT_GUI_HPP
#define VCBAT_GUI_HPP

#include "vcbat-types.hpp"
#include "vcbat-font-ui.hpp"
#include "vcbat-dependencies.hpp"
#include "vcbat-cl-options.hpp"

struct  VCBatGui;
typedef VCBatGui* VCBatGuiPtr;
typedef VCBatGui& VCBatGuiRef;

struct  VCBatGuiMenuBar; 
typedef VCBatGuiMenuBar* VCBatGuiMenuBarPtr;
typedef VCBatGuiMenuBar& VCBatGuiMenuBarRef;

struct  VCBatGuiBuildScriptWindow;
typedef VCBatGuiBuildScriptWindow* VCBatGuiBuildScriptWindowPtr;
typedef VCBatGuiBuildScriptWindow& VCBatGuiBuildScriptWindowRef;

struct  VCBatGuiClOptions;
typedef VCBatGuiClOptions* VCBatGuiClOptionsPtr;
typedef VCBatGuiClOptions& VCBatGuiClOptionsRef;

//-------------------------------------------------
// GUI
//-------------------------------------------------

#define VCBAT_GUI_MAIN_WINDOW_TITLE "Main Window"

struct VCBatGuiFonts {
    ImFont* ui;
    ImFont* code;
};

struct VCBatGui {
    VCBatGuiFonts                fonts;
    VCBatGuiMenuBarPtr           menu_bar_ptr; 
    VCBatGuiBuildScriptWindowPtr build_script_window_ptr;
    VCBatGuiClOptionsPtr         cl_options_ptr;
    ImGuiWindowFlags             main_window_flags;
};

struct VCBatGuiTextSizePixels {
    f32 width;
    f32 height;
};

VCBatGuiPtr
vcbat_gui_create_and_initialize();

void
vcbat_gui_render();

VCBatGuiTextSizePixels
vcbat_gui_text_size_pixels();

//-------------------------------------------------
// MENU BAR
//-------------------------------------------------

struct VCBatGuiMenuBar {
    bool menu_file_item_exit;
    bool menu_view_item_demo;
};

VCBatGuiMenuBarPtr
vcbat_gui_menu_bar_create_and_initialize();

void
vcbat_gui_menu_bar_render();

//-------------------------------------------------
// CL OPTIONS
//-------------------------------------------------

#define VCBAT_GUI_CL_OPTIONS_TITLE                  "Cl Options"

#define VCBAT_GUI_CL_OPTIONS_HEADER_OPTIMIZATION    "Optimization"
#define VCBAT_GUI_CL_OPTIONS_HEADER_CODE_GENERATION "Code"
#define VCBAT_GUI_CL_OPTIONS_HEADER_OUTPUT_FILES    "OutpuT"
#define VCBAT_GUI_CL_OPTIONS_HEADER_PREPROCESSOR    "Preprocessor"
#define VCBAT_GUI_CL_OPTIONS_HEADER_HEADER_MODULES  "Header"
#define VCBAT_GUI_CL_OPTIONS_HEADER_LANGUAGE        "Language"
#define VCBAT_GUI_CL_OPTIONS_HEADER_LINKING         "Linking"
#define VCBAT_GUI_CL_OPTIONS_HEADER_MISCELLANEOUS   "Miscellaneous"
#define VCBAT_GUI_CL_OPTIONS_HEADER_DIAGNOSTICS     "Diagnostics"
#define VCBAT_GUI_CL_OPTIONS_HEADER_EXPERIMENTAL    "Experimental"
#define VCBAT_GUI_CL_OPTIONS_HEADER_DEPRECATED      "Deprecated"

#define VCBAT_GUI_CL_OPTIONS_TABLE_OPTIMIZATION     "cl_options_table_optimizations"
#define VCBAT_GUI_CL_OPTIONS_TABLE_CODE_GENERATION  "cl_options_table_codegeneration"
#define VCBAT_GUI_CL_OPTIONS_TABLE_OUTPUT_FILES     "cl_options_table_outputfiles"
#define VCBAT_GUI_CL_OPTIONS_TABLE_PREPROCESSOR     "cl_options_table_preprocessor"
#define VCBAT_GUI_CL_OPTIONS_TABLE_HEADER_MODULES   "cl_options_table_headermodules"
#define VCBAT_GUI_CL_OPTIONS_TABLE_LANGUAGE         "cl_options_table_language"
#define VCBAT_GUI_CL_OPTIONS_TABLE_LINKING          "cl_options_table_linking"
#define VCBAT_GUI_CL_OPTIONS_TABLE_MISCELLANEOUS    "cl_options_table_miscellaneous"
#define VCBAT_GUI_CL_OPTIONS_TABLE_DIAGNOSTICS      "cl_options_table_diagnostics"
#define VCBAT_GUI_CL_OPTIONS_TABLE_EXPERIMENTAL     "cl_options_table_experimental"
#define VCBAT_GUI_CL_OPTIONS_TABLE_DEPRECATED       "cl_options_table_deprecated"

#define VCBAT_GUI_CL_OPTIONS_TABLE_COLUMN_INDEX_FLAG        0
#define VCBAT_GUI_CL_OPTIONS_TABLE_COLUMN_INDEX_DESCRIPTION 1

struct VCBatGuiClOptions {
    bool            enabled;
    ImGuiTableFlags table_flags;
};

VCBatGuiClOptionsPtr
vcbat_gui_cl_options_create_and_initialize();

void
vcbat_gui_cl_options_render();

#endif //VCBAT_GUI_HPP