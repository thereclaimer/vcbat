#pragma once

#include "vcbat-gui.hpp"

global VCBatGuiClOptions vcbat_gui_cl_options;

internal VCBatGuiClOptionsPtr
vcbat_gui_cl_options_create_and_initialize() {

    vcbat_gui_cl_options.table_flags =
        ImGuiTableFlags_ScrollY      | 
        ImGuiTableFlags_RowBg        | 
        ImGuiTableFlags_BordersOuter | 
        ImGuiTableFlags_BordersV     | 
        ImGuiTableFlags_Resizable    | 
        ImGuiTableFlags_Reorderable  | 
        ImGuiTableFlags_Hideable;

    return(&vcbat_gui_cl_options);
}

internal void
vcbat_imgui_cl_options_table(
    const VCBatGuiTextSizePixels& text_size_pixels,
    const char*                   header_display_title,
    const char*                   table_name,
    const char* const*            flags,
    const char* const*            descriptions,
    const u32                     rows_count) {

    ImVec2 outer_size = 
        ImVec2(
            0.0f,
            text_size_pixels.height * 8);

    if (ImGui::CollapsingHeader(header_display_title)) {

        ImGui::BeginTable(
            table_name,
            2,
            vcbat_gui_cl_options.table_flags,
            outer_size);

        ImGui::TableSetupScrollFreeze(0, 1); // Make top row always visible
        ImGui::TableSetupColumn("Flag",        ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn("Description", ImGuiTableColumnFlags_None);
        ImGui::TableHeadersRow();

        for (
            u32 row = 0;
            row < rows_count;
            ++row) {

            ImGui::TableNextRow();

            //flag
            ImGui::TableSetColumnIndex(VCBAT_GUI_CL_OPTIONS_TABLE_COLUMN_INDEX_FLAG); 
            ImGui::Text(flags[row]);

            //description
            ImGui::TableSetColumnIndex(VCBAT_GUI_CL_OPTIONS_TABLE_COLUMN_INDEX_DESCRIPTION);
            ImGui::Text(descriptions[row]);
        }

        ImGui::EndTable();
    }    
}

internal void
vcbat_gui_cl_options_render() {

    ImGui::Begin(VCBAT_GUI_CL_OPTIONS_TITLE);

    VCBatGuiTextSizePixels text_size_pixels = vcbat_gui_text_size_pixels();

    vcbat_imgui_cl_options_table(text_size_pixels, VCBAT_GUI_CL_OPTIONS_HEADER_OPTIMIZATION,    VCBAT_GUI_CL_OPTIONS_TABLE_OPTIMIZATION,    VCBAT_CL_OPTIONS_FLAG_OPTIMIZATION,   VCBAT_CL_OPTIONS_DESCRIPTION_OPTIMIZATION,    VCBAT_CL_OPTIONS_COUNT_OPTIMIZATIONS);
    vcbat_imgui_cl_options_table(text_size_pixels, VCBAT_GUI_CL_OPTIONS_HEADER_CODE_GENERATION, VCBAT_GUI_CL_OPTIONS_TABLE_CODE_GENERATION, VCBAT_CL_OPTIONS_FLAG_CODE_GENERATION,VCBAT_CL_OPTIONS_DESCRIPTION_CODE_GENERATION, VCBAT_CL_OPTIONS_COUNT_CODE_GENERATION);
    vcbat_imgui_cl_options_table(text_size_pixels, VCBAT_GUI_CL_OPTIONS_HEADER_OUTPUT_FILES,    VCBAT_GUI_CL_OPTIONS_TABLE_OUTPUT_FILES,    VCBAT_CL_OPTIONS_FLAG_OUTPUT_FILES,   VCBAT_CL_OPTIONS_DESCRIPTION_OUTPUT_FILES,    VCBAT_CL_OPTIONS_COUNT_OUTPUT_FILES);
    vcbat_imgui_cl_options_table(text_size_pixels, VCBAT_GUI_CL_OPTIONS_HEADER_PREPROCESSOR,    VCBAT_GUI_CL_OPTIONS_TABLE_PREPROCESSOR,    VCBAT_CL_OPTIONS_FLAG_PREPROCESSOR,   VCBAT_CL_OPTIONS_DESCRIPTION_PREPROCESSOR,    VCBAT_CL_OPTIONS_COUNT_PREPROCESSOR);
    vcbat_imgui_cl_options_table(text_size_pixels, VCBAT_GUI_CL_OPTIONS_HEADER_HEADER_MODULES,  VCBAT_GUI_CL_OPTIONS_TABLE_HEADER_MODULES,  VCBAT_CL_OPTIONS_FLAG_HEADER_MODULES, VCBAT_CL_OPTIONS_DESCRIPTION_HEADER_MODULES,  VCBAT_CL_OPTIONS_COUNT_HEADER_MODULES);
    vcbat_imgui_cl_options_table(text_size_pixels, VCBAT_GUI_CL_OPTIONS_HEADER_LANGUAGE,        VCBAT_GUI_CL_OPTIONS_TABLE_LANGUAGE,        VCBAT_CL_OPTIONS_FLAG_LANGUAGE,       VCBAT_CL_OPTIONS_DESCRIPTION_LANGUAGE,        VCBAT_CL_OPTIONS_COUNT_LANGUAGE);
    vcbat_imgui_cl_options_table(text_size_pixels, VCBAT_GUI_CL_OPTIONS_HEADER_LINKING,         VCBAT_GUI_CL_OPTIONS_TABLE_LINKING,         VCBAT_CL_OPTIONS_FLAG_LINKING,        VCBAT_CL_OPTIONS_DESCRIPTION_LINKING,         VCBAT_CL_OPTIONS_COUNT_LINKING);
    vcbat_imgui_cl_options_table(text_size_pixels, VCBAT_GUI_CL_OPTIONS_HEADER_MISCELLANEOUS,   VCBAT_GUI_CL_OPTIONS_TABLE_MISCELLANEOUS,   VCBAT_CL_OPTIONS_FLAG_MISCELLANEOUS,  VCBAT_CL_OPTIONS_DESCRIPTION_MISCELLANEOUS,   VCBAT_CL_OPTIONS_COUNT_MISCELLANEOUS);
    vcbat_imgui_cl_options_table(text_size_pixels, VCBAT_GUI_CL_OPTIONS_HEADER_DIAGNOSTICS,     VCBAT_GUI_CL_OPTIONS_TABLE_DIAGNOSTICS,     VCBAT_CL_OPTIONS_FLAG_DIAGNOSTICS,    VCBAT_CL_OPTIONS_DESCRIPTION_DIAGNOSTICS,     VCBAT_CL_OPTIONS_COUNT_DIAGNOSTICS);
    vcbat_imgui_cl_options_table(text_size_pixels, VCBAT_GUI_CL_OPTIONS_HEADER_EXPERIMENTAL,    VCBAT_GUI_CL_OPTIONS_TABLE_EXPERIMENTAL,    VCBAT_CL_OPTIONS_FLAG_EXPERIMENTAL,   VCBAT_CL_OPTIONS_DESCRIPTION_EXPERIMENTAL,    VCBAT_CL_OPTIONS_COUNT_EXPERIMENTAL);
    vcbat_imgui_cl_options_table(text_size_pixels, VCBAT_GUI_CL_OPTIONS_HEADER_DEPRECATED,      VCBAT_GUI_CL_OPTIONS_TABLE_DEPRECATED,      VCBAT_CL_OPTIONS_FLAG_DEPRECATED,     VCBAT_CL_OPTIONS_DESCRIPTION_DEPRECATED,      VCBAT_CL_OPTIONS_COUNT_DEPRECATED);

    ImGui::End();
}