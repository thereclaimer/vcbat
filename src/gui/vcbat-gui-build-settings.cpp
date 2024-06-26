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

    VCBatGuiBuildSettingsDirectories& directories = vcbat_build_settings_window.directories;

    //TODO: I hate how this looks. I'd like to swap the label text and the input, but doing the opposite of
    // how its being rendered is like fucking pulling teeth. Seriously, there are so many options for 
    // rendering UI elements except "Label Position -> Left/Right". Apparently thats in the 'too goddamn hard' box"

    //working directory
    if (ImGui::Button("Browse")) {

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
    ImGui::Button("Browse");
    ImGui::SameLine();
    ImGui::InputText("Output", directories.output, VCBAT_GUI_BUILD_SETTINGS_DIRECTORY_STRING_SIZE);
}

internal void
vcbat_gui_build_settings_window_render() {

    ImGui::Begin(
        VCBAT_GUI_BUILD_SETTINGS_WINDOW_TITLE,
        NULL,
        vcbat_build_settings_window.flags);

    vcbat_gui_build_settings_directories();

    ImGui::End();
}