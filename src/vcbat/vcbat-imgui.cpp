#pragma once

#include "vcbat.hpp"

internal VCBatImGui
vcbat_imgui_create_and_initialize() {
    
    VCBatImGui vcbat_imgui = {0};
    
    ImGuiViewport* viewport = ImGui::GetMainViewport();

    //create our panels
    ImVec2 viewport_work_pos  = viewport->WorkPos;
    ImVec2 viewport_work_size = viewport->WorkSize; 
    ImVec2 viewport_center    = viewport->GetCenter(); 

    VCBatImGuiDockNodes dock_nodes = {0};

    //https://gist.github.com/AidanSun05/953f1048ffe5699800d2c92b88c36d9f

    // dock_nodes.dock_group = ImGui::GetID("dock_nodes");
    // ImGui::DockBuilderAddNode(dock_nodes.dock_group);


    return(vcbat_imgui);
};

static ImGuiTableFlags table_flags = 
    ImGuiTableFlags_ScrollY      | 
    ImGuiTableFlags_RowBg        | 
    ImGuiTableFlags_BordersOuter | 
    ImGuiTableFlags_BordersV     | 
    ImGuiTableFlags_Resizable    | 
    ImGuiTableFlags_Reorderable  | 
    ImGuiTableFlags_Hideable;

internal void
vcbat_imgui_cl_options_table(
    const char*        header_display_title,
    const char*        table_name,
    const char* const* flags,
    const char* const* descriptions,
    const u32          rows_count) {

    const float TEXT_BASE_WIDTH  = ImGui::CalcTextSize("A").x;
    const float TEXT_BASE_HEIGHT = ImGui::GetTextLineHeightWithSpacing();

    ImVec2 outer_size = ImVec2(0.0f, TEXT_BASE_HEIGHT * 8);

    if (ImGui::CollapsingHeader(header_display_title)) {

        b8 cl_options_table_begin = 
            ImGui::BeginTable(
                table_name,
                2,
                table_flags,
                outer_size);

        if (cl_options_table_begin) {

            ImGui::TableSetupScrollFreeze(0, 1); // Make top row always visible
            ImGui::TableSetupColumn("Flag",        ImGuiTableColumnFlags_None);
            ImGui::TableSetupColumn("Description", ImGuiTableColumnFlags_None);
            ImGui::TableHeadersRow();

            for (
                u32 row = 0;
                row < rows_count;
                ++row) {

                ImGui::TableNextRow();

                ImGui::TableSetColumnIndex(0); //FLAG
                ImGui::Text(flags[row]);

                ImGui::TableSetColumnIndex(1); //DESCRIPTION
                ImGui::Text(descriptions[row]);
            }

            ImGui::EndTable();
        }
    }    

}

internal void
vcbat_imgui_cl_options(
    b8* open) {

    ImGui::Begin("CL Options",open);

    vcbat_imgui_cl_options_table("Optimization",    "cl_options_table_optimizations",  VCBAT_CL_OPTIONS_FLAG_OPTIMIZATION,   VCBAT_CL_OPTIONS_DESCRIPTION_OPTIMIZATION,    VCBAT_CL_OPTIONS_COUNT_OPTIMIZATIONS);
    vcbat_imgui_cl_options_table("Code Generation", "cl_options_table_codegeneration", VCBAT_CL_OPTIONS_FLAG_CODE_GENERATION,VCBAT_CL_OPTIONS_DESCRIPTION_CODE_GENERATION, VCBAT_CL_OPTIONS_COUNT_CODE_GENERATION);
    vcbat_imgui_cl_options_table("Output Files",    "cl_options_table_outputfiles",    VCBAT_CL_OPTIONS_FLAG_OUTPUT_FILES,   VCBAT_CL_OPTIONS_DESCRIPTION_OUTPUT_FILES,    VCBAT_CL_OPTIONS_COUNT_OUTPUT_FILES);
    vcbat_imgui_cl_options_table("Preprocessor",    "cl_options_table_preprocessor",   VCBAT_CL_OPTIONS_FLAG_PREPROCESSOR,   VCBAT_CL_OPTIONS_DESCRIPTION_PREPROCESSOR,    VCBAT_CL_OPTIONS_COUNT_PREPROCESSOR);
    vcbat_imgui_cl_options_table("Header Modules",  "cl_options_table_headermodules",  VCBAT_CL_OPTIONS_FLAG_HEADER_MODULES, VCBAT_CL_OPTIONS_DESCRIPTION_HEADER_MODULES,  VCBAT_CL_OPTIONS_COUNT_HEADER_MODULES);
    vcbat_imgui_cl_options_table("Language",        "cl_options_table_language",       VCBAT_CL_OPTIONS_FLAG_LANGUAGE,       VCBAT_CL_OPTIONS_DESCRIPTION_LANGUAGE,        VCBAT_CL_OPTIONS_COUNT_LANGUAGE);
    vcbat_imgui_cl_options_table("Linking",         "cl_options_table_linking",        VCBAT_CL_OPTIONS_FLAG_LINKING,        VCBAT_CL_OPTIONS_DESCRIPTION_LINKING,         VCBAT_CL_OPTIONS_COUNT_LINKING);
    vcbat_imgui_cl_options_table("Miscellaneous",   "cl_options_table_miscellaneous",  VCBAT_CL_OPTIONS_FLAG_MISCELLANEOUS,  VCBAT_CL_OPTIONS_DESCRIPTION_MISCELLANEOUS,   VCBAT_CL_OPTIONS_COUNT_MISCELLANEOUS);
    vcbat_imgui_cl_options_table("Diagnostics",     "cl_options_table_diagnostics",    VCBAT_CL_OPTIONS_FLAG_DIAGNOSTICS,    VCBAT_CL_OPTIONS_DESCRIPTION_DIAGNOSTICS,     VCBAT_CL_OPTIONS_COUNT_DIAGNOSTICS);
    vcbat_imgui_cl_options_table("Experimental",    "cl_options_table_experimental",   VCBAT_CL_OPTIONS_FLAG_EXPERIMENTAL,   VCBAT_CL_OPTIONS_DESCRIPTION_EXPERIMENTAL,    VCBAT_CL_OPTIONS_COUNT_EXPERIMENTAL);
    vcbat_imgui_cl_options_table("Deprecated",      "cl_options_table_deprecated",     VCBAT_CL_OPTIONS_FLAG_DEPRECATED,     VCBAT_CL_OPTIONS_DESCRIPTION_DEPRECATED,      VCBAT_CL_OPTIONS_COUNT_DEPRECATED);

    ImGui::End();
}

internal void
vcbat_imgui_menu_bar(
    VCBatImGuiMenuBarRef menu_bar_ref) {

    if (ImGui::BeginMainMenuBar()) {

        if (ImGui::BeginMenu("File")) {

            ImGui::MenuItem("Exit",NULL,&menu_bar_ref.menu_file_item_exit);

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View")) {

            ImGui::MenuItem("Demo",NULL,&menu_bar_ref.menu_view_item_demo);

            ImGui::EndMenu();
        }
    
        ImGui::BeginMenuBar();
    }
}

internal void
vcbat_imgui_update(
    VCBatImGuiRef vcbat_imgui_ref) {

    //first, make sure dockspace is enabled
    const ImGuiViewport*      viewport        = ImGui::GetMainViewport();
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    ImGui::DockSpaceOverViewport(
        viewport,
        dockspace_flags);

    //next, create the main window
    ImGuiWindowFlags main_window_flags = 
        ImGuiWindowFlags_MenuBar               | 
        ImGuiWindowFlags_NoDocking             |
        ImGuiWindowFlags_NoTitleBar            | 
        ImGuiWindowFlags_NoCollapse            | 
        ImGuiWindowFlags_NoResize              | 
        ImGuiWindowFlags_NoMove                |
        ImGuiWindowFlags_NoBringToFrontOnFocus | 
        ImGuiWindowFlags_NoNavFocus            |
        ImGuiWindowFlags_NoBackground;


    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

    ImGui::Begin("main window",&vcbat_imgui_ref.show_main_window,main_window_flags);

    vcbat_imgui_menu_bar(vcbat_imgui_ref.menu_bar);    

    vcbat_imgui_ref.show_demo_window = vcbat_imgui_ref.menu_bar.menu_view_item_demo;

    vcbat_imgui_cl_options(&vcbat_imgui_ref.show_cl_options);

    if (vcbat_imgui_ref.show_demo_window) {
        ImGui::ShowDemoWindow(&vcbat_imgui_ref.show_demo_window);
    }

    ImGui::End();

}

