#pragma once

#include "vcbat-gui.hpp"

global VCBatGuiBuildSettingsWindow vcbat_build_settings_window;

internal VCBatGuiBuildSettingsWindowPtr
vcbat_gui_build_settings_window_create_and_initialize() {

    vcbat_build_settings_window = {0};

    //directories
    VCBatGuiBuildSettingsDirectories& directories = vcbat_build_settings_window.directories;
    directories = {0};

    //path lists
    VCBatGuiBuildSettingsPathLists& path_lists = vcbat_build_settings_window.path_lists;
    path_lists.source_files        = vcbat_gui_file_list_create("Source Files"); 
    path_lists.include_directories = vcbat_gui_file_list_create("Include Directories"); 
    path_lists.lib_directories     = vcbat_gui_file_list_create("Lib Directories"); 
    path_lists.lib_files           = vcbat_gui_file_list_create("Lib Files"); 

    return(&vcbat_build_settings_window);
}

internal void
vcbat_gui_build_settings_directories() {

    ImGui::SeparatorText("Working Directory and Output");

    VCBatGuiBuildSettingsDirectories& directories = vcbat_build_settings_window.directories;

    //TODO: I hate how this looks. I'd like to swap the label text and the input, but doing the opposite of
    // how its being rendered is like fucking pulling teeth. Seriously, there are so many options for 
    // rendering UI elements except "Label Position -> Left/Right". Apparently thats in the 'too goddamn hard' box"

    //working directory
    if (ImGui::Button("Browse##WorkingDirectory")) {

        VCBatPlatformFileDialogOptions dialog_options;
        dialog_options.dialog_type = VCBatPlatformFileDialogType_Directory;

        vcbat_platform_api_file_dialog(dialog_options);
        
        strcpy(
            directories.working,
            dialog_options.selected_path);
    }


    ImGui::SameLine();
    ImGui::InputText("Working Directory", directories.working, VCBAT_GUI_BUILD_SETTINGS_DIRECTORY_STRING_SIZE);

    //output
    if (ImGui::Button("Browse##Output")) {
        
        VCBatPlatformFileDialogOptions dialog_options;
        dialog_options.dialog_type = VCBatPlatformFileDialogType_File;

        vcbat_platform_api_file_dialog(dialog_options);
        
        strcpy(
            directories.output,
            dialog_options.selected_path);        
    }
    
    ImGui::SameLine();
    ImGui::InputText("Output", directories.output, VCBAT_GUI_BUILD_SETTINGS_DIRECTORY_STRING_SIZE);
}

internal void
vcbat_gui_build_settings_source_files() {

    ImGui::SeparatorText("Source Files");

    VCBatGuiFileListRef source_file_list_ref = vcbat_build_settings_window.path_lists.source_files;

    if (source_file_list_ref.count == 0) {
        ImGui::Text("(No source files added)");
    }
    else {

        ImGuiTableFlags table_flags = 
            ImGuiTableFlags_RowBg;


        if (ImGui::BeginTable("Source Files",3,table_flags)) {

            ImGui::TableSetupColumn("path##souercefile", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("path##udpate",      ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("path##remove",      ImGuiTableColumnFlags_WidthFixed);

            int row = 0;

            local char tmp_path[256];
            local s32  row_update_index = -1;

            char button_name_remove[512];
            char button_name_update[512];

            for (
                const char* file_path = vcbat_gui_file_list_cstr_begin(source_file_list_ref);
                file_path != NULL;
                file_path = vcbat_gui_file_list_cstr_next(source_file_list_ref)) {

                ImGui::TableNextRow();

                //current row is being updated
                if (row_update_index == -1) {

                    //file path readonly
                    ImGui::TableSetColumnIndex(0);
                    ImGui::Text(file_path);

                    //update
                    ImGui::TableSetColumnIndex(1);
                    strcat(button_name_update,"Update##");
                    strcat(button_name_update,file_path);
                    if (ImGui::Button(button_name_update)) {
                        
                        //clear the tmp path 
                        memset(
                            tmp_path,
                            0,
                            256
                        );

                        //copy the file path to the tmp path
                        strcpy(
                            tmp_path,
                            file_path
                        );
                        row_update_index = row;
                    }

                    //remove
                    ImGui::TableSetColumnIndex(2);
                    strcat(button_name_remove,"Remove##");
                    strcat(button_name_remove,file_path);
                    if (ImGui::Button("Remove")) {
                        vcbat_gui_file_list_remove(source_file_list_ref,row);
                    }
                }

                //the current row is being updated
                else if (row_update_index == row) {

                    //file path input
                    ImGui::TableSetColumnIndex(0);
                    ImGui::InputText(
                        "##file_path_update",
                        tmp_path,
                        256);

                    //update
                    ImGui::TableSetColumnIndex(1);
                    if (ImGui::Button("Save##save_source")) {
                        vcbat_gui_file_list_update(source_file_list_ref,row,tmp_path);
                        row_update_index = -1;
                    }

                    //remove
                    ImGui::TableSetColumnIndex(2);
                    strcat(button_name_remove,"##browse_source");
                    strcat(button_name_remove,file_path);
                    if (ImGui::Button("Browse##browse_source")) {

                        VCBatPlatformFileDialogOptions dialog_options = {0};

                        dialog_options.dialog_type        = VCBatPlatformFileDialogType_File;
                        dialog_options.starting_directory = vcbat_build_settings_window.directories.working;

                        vcbat_platform_api_file_dialog(dialog_options);        

                        if (dialog_options.user_made_selection) {
                            
                            memset(
                                tmp_path,
                                0,
                                256);

                            strcpy(tmp_path,dialog_options.selected_path);
                            vcbat_gui_file_list_update(source_file_list_ref,row,tmp_path);
                            row_update_index = -1;
                        }

                    }
                }

                //a different row is being updated
                else {
                    
                    //file path readonly
                    ImGui::TableSetColumnIndex(0);
                    ImGui::Text(file_path);

                    //update
                    ImGui::TableSetColumnIndex(1);
                    //remove
                    ImGui::TableSetColumnIndex(2);
                }

                memset(button_name_remove,0,512);
                memset(button_name_update,0,512);

                row++;
            }

            ImGui::EndTable();
        }

    }

    if (ImGui::Button("Add Source File")) {

        VCBatPlatformFileDialogOptions dialog_options;
        
        dialog_options.dialog_type        = VCBatPlatformFileDialogType_File;
        dialog_options.starting_directory = vcbat_build_settings_window.directories.working;

        vcbat_platform_api_file_dialog(dialog_options);        

        vcbat_gui_file_list_add(
            source_file_list_ref,
            dialog_options.selected_path
        );
    }

}

internal void
vcbat_gui_build_settings_window_render() {

    ImGui::Begin(
        VCBAT_GUI_BUILD_SETTINGS_WINDOW_TITLE,
        NULL,
        vcbat_build_settings_window.flags);

    vcbat_gui_build_settings_directories();
    vcbat_gui_build_settings_source_files();

    ImGui::End();
}