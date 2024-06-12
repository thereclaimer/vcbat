#pragma once

#include "vcbat.hpp"

internal VCBatImGui
vcbat_imgui_create_and_initialize() {
    
    VCBatImGui vcbat_imgui = {0};
    
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

    vcbat_imgui_cl_options_table("Optimization",   "cl_options_table_optimizations", VCBAT_CL_OPTIONS_FLAG_OPTIMIZATION,   VCBAT_CL_OPTIONS_DESCRIPTION_OPTIMIZATION,    VCBAT_CL_OPTIONS_COUNT_OPTIMIZATIONS);
    vcbat_imgui_cl_options_table("CodeGeneration", "cl_options_table_optimizations", VCBAT_CL_OPTIONS_FLAG_CODE_GENERATION,VCBAT_CL_OPTIONS_DESCRIPTION_CODE_GENERATION, VCBAT_CL_OPTIONS_COUNT_CODE_GENERATION);
    vcbat_imgui_cl_options_table("OutputFiles",    "cl_options_table_optimizations", VCBAT_CL_OPTIONS_FLAG_OUTPUT_FILES,   VCBAT_CL_OPTIONS_DESCRIPTION_OUTPUT_FILES,    VCBAT_CL_OPTIONS_COUNT_OUTPUT_FILES);
    vcbat_imgui_cl_options_table("Preprocessor",   "cl_options_table_optimizations", VCBAT_CL_OPTIONS_FLAG_PREPROCESSOR,   VCBAT_CL_OPTIONS_DESCRIPTION_PREPROCESSOR,    VCBAT_CL_OPTIONS_COUNT_PREPROCESSOR);
    vcbat_imgui_cl_options_table("HeaderModules",  "cl_options_table_optimizations", VCBAT_CL_OPTIONS_FLAG_HEADER_MODULES, VCBAT_CL_OPTIONS_DESCRIPTION_HEADER_MODULES,  VCBAT_CL_OPTIONS_COUNT_HEADER_MODULES);
    vcbat_imgui_cl_options_table("Language",       "cl_options_table_optimizations", VCBAT_CL_OPTIONS_FLAG_LANGUAGE,       VCBAT_CL_OPTIONS_DESCRIPTION_LANGUAGE,        VCBAT_CL_OPTIONS_COUNT_LANGUAGE);
    vcbat_imgui_cl_options_table("Linking",        "cl_options_table_optimizations", VCBAT_CL_OPTIONS_FLAG_LINKING,        VCBAT_CL_OPTIONS_DESCRIPTION_LINKING,         VCBAT_CL_OPTIONS_COUNT_LINKING);
    vcbat_imgui_cl_options_table("Miscellaneous",  "cl_options_table_optimizations", VCBAT_CL_OPTIONS_FLAG_MISCELLANEOUS,  VCBAT_CL_OPTIONS_DESCRIPTION_MISCELLANEOUS,   VCBAT_CL_OPTIONS_COUNT_MISCELLANEOUS);
    vcbat_imgui_cl_options_table("Diagnostics",    "cl_options_table_optimizations", VCBAT_CL_OPTIONS_FLAG_DIAGNOSTICS,    VCBAT_CL_OPTIONS_DESCRIPTION_DIAGNOSTICS,     VCBAT_CL_OPTIONS_COUNT_DIAGNOSTICS);
    vcbat_imgui_cl_options_table("Experimental",   "cl_options_table_optimizations", VCBAT_CL_OPTIONS_FLAG_EXPERIMENTAL,   VCBAT_CL_OPTIONS_DESCRIPTION_EXPERIMENTAL,    VCBAT_CL_OPTIONS_COUNT_EXPERIMENTAL);
    vcbat_imgui_cl_options_table("Deprecated",     "cl_options_table_optimizations", VCBAT_CL_OPTIONS_FLAG_DEPRECATED,     VCBAT_CL_OPTIONS_DESCRIPTION_DEPRECATED,      VCBAT_CL_OPTIONS_COUNT_DEPRECATED);

    ImGui::End();
}

internal void
vcbat_imgui_update(
    VCBatImGuiRef vcbat_imgui_ref) {

    ImGui::ShowDemoWindow(&vcbat_imgui_ref.show_demo_window);
    vcbat_imgui_cl_options(&vcbat_imgui_ref.show_cl_options);
}

