#ifndef VCBAT_GUI_HPP
#define VCBAT_GUI_HPP

#include "vcbat-types.hpp"
#include "vcbat-font-ui.hpp"
#include "vcbat-dependencies.hpp"
#include "vcbat-cl-options.hpp"
#include "vcbat-core.hpp"

struct  VCBatGui;
typedef VCBatGui* VCBatGuiPtr;
typedef VCBatGui& VCBatGuiRef;

struct  VCBatGuiMenuBar; 
typedef VCBatGuiMenuBar* VCBatGuiMenuBarPtr;
typedef VCBatGuiMenuBar& VCBatGuiMenuBarRef;

struct  VCBatGuiBuildScriptWindow;
typedef VCBatGuiBuildScriptWindow* VCBatGuiBuildScriptWindowPtr;
typedef VCBatGuiBuildScriptWindow& VCBatGuiBuildScriptWindowRef;

struct  VCBatGuiClOptionsWindow;
typedef VCBatGuiClOptionsWindow* VCBatGuiClOptionsWindowPtr;
typedef VCBatGuiClOptionsWindow& VCBatGuiClOptionsWindowRef;

struct  VCBatGuiSourcesWindow;
typedef VCBatGuiSourcesWindow* VCBatGuiSourcesWindowPtr;
typedef VCBatGuiSourcesWindow& VCBatGuiSourcesWindowRef;

struct  VCBatGuiBuildSettingsWindow;
typedef VCBatGuiBuildSettingsWindow* VCBatGuiBuildSettingsWindowPtr;
typedef VCBatGuiBuildSettingsWindow& VCBatGuiBuildSettingsWindowRef;

struct  VCBatGuiFileList;
typedef VCBatGuiFileList* VCBatGuiFileListPtr;
typedef VCBatGuiFileList& VCBatGuiFileListRef;

//-------------------------------------------------
// GUI
//-------------------------------------------------

#define VCBAT_GUI_MAIN_WINDOW_TITLE "Main Window"
#define VCBAT_GUI_DEMO              "Dear ImGui Demo"

struct VCBatGuiFonts {
    ImFont* ui;
    ImFont* code;
};

struct VCBatGuiDockSpace {
    ImGuiID dock_node_id;
    ImGuiID control_node_id; 
    ImGuiID options_node_id;
    ImGuiID output_node_id;
};

struct VCBatGuiWindows {
    VCBatGuiBuildScriptWindowPtr   build_script;
    VCBatGuiBuildSettingsWindowPtr build_settings;
    VCBatGuiClOptionsWindowPtr     cl_options;
};

struct VCBatGui {
    VCBatGuiFonts                fonts;
    VCBatGuiMenuBarPtr           menu_bar_ptr; 
    ImGuiWindowFlags             main_window_flags;
    VCBatGuiDockSpace            dockspace;
    VCBatGuiWindows              windows;
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

u32
vcbat_gui_text_width_pixels(
    const char* text);

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
#define VCBAT_GUI_CL_OPTIONS_HEADER_OUTPUT_FILES    "Output"
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

struct VCBatGuiClOptionsWindow {
    bool            enabled;
    ImGuiTableFlags table_flags;
};

VCBatGuiClOptionsWindowPtr
vcbat_gui_cl_options_create_and_initialize();

void
vcbat_gui_cl_options_render();

//-------------------------------------------------
// SCRIPT WINDOW
//-------------------------------------------------

#define VCBAT_GUI_BUILD_SCRIPT_WINDOW_TITLE "Build Script"

struct VCBatGuiBuildScriptWindow {
    ImGuiWindowFlags flags;
};

VCBatGuiBuildScriptWindowPtr
vcbat_gui_build_script_window_create_and_initialize();

void
vcbat_gui_build_script_window_render();

//-------------------------------------------------
// FILE LIST 
//-------------------------------------------------

#define VCBAT_GUI_FILE_PATH_SIZE 256

struct VCBatGuiFileList {
    VCBatMemoryArenaHandle arena;
    memory                 memory;
    u32                    count;
    u32                    index;
    char*                  name;
};

VCBatGuiFileList
vcbat_gui_file_list_create(
    char* file_list_name);

void
vcbat_gui_file_list_reset(
    VCBatGuiFileListRef file_list);

void
vcbat_gui_file_list_add(
          VCBatGuiFileListRef file_list_ref,
    const char*               file_path);

void
vcbat_gui_file_list_remove(
    VCBatGuiFileListRef file_list_ref,
    u32                 file_path_index);

void
vcbat_gui_file_list_update(
          VCBatGuiFileListRef file_list_ref,
    const u32                 file_path_index,
    const char*               file_path_new);

const char*
vcbat_gui_file_list_cstr(
    VCBatGuiFileListRef file_list_ref,
    u32                 index);

const char*
vcbat_gui_file_list_cstr_begin(
    VCBatGuiFileListRef file_list_ref);

const char*
vcbat_gui_file_list_cstr_next(
    VCBatGuiFileListRef file_list_ref);

void
vbat_gui_file_list_render(
    VCBatGuiFileListRef file_list_ref);

//-------------------------------------------------
// BUILD SETTINGS WINDOW 
//-------------------------------------------------

#define VCBAT_GUI_BUILD_SETTINGS_WINDOW_TITLE          "Build Settings"
#define VCBAT_GUI_BUILD_SETTINGS_DIRECTORY_STRING_SIZE 256

struct VCBatGuiBuildSettingsDirectories {
    char working[VCBAT_GUI_BUILD_SETTINGS_DIRECTORY_STRING_SIZE];
    char output[VCBAT_GUI_BUILD_SETTINGS_DIRECTORY_STRING_SIZE];
};

struct VCBatGuiBuildSettingsPathLists {
    VCBatGuiFileList source_files;
    VCBatGuiFileList include_directories;
    VCBatGuiFileList lib_directories;
    VCBatGuiFileList lib_files;
};

struct VCBatGuiBuildSettingsWindow {
    ImGuiWindowFlags                 flags;
    VCBatGuiBuildSettingsDirectories directories;  
    VCBatGuiBuildSettingsPathLists   path_lists;
};

VCBatGuiBuildSettingsWindowPtr
vcbat_gui_build_settings_window_create_and_initialize();

void
vcbat_gui_build_settings_window_render();

#endif //VCBAT_GUI_HPP