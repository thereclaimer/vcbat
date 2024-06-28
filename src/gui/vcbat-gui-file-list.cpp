#pragma once

#include "vcbat-gui.hpp"

internal VCBatGuiFileList
vcbat_gui_file_list_create(
    char* file_list_name) {

    VCBatGuiFileList file_list; 

    file_list.arena  = vcbat_memory_arena_reserve();
    file_list.count  = 0;
    file_list.index  = 0;
    file_list.memory = NULL;    
    file_list.name   = file_list_name;

    VCBAT_ASSERT(file_list.arena);
    
    return(file_list);
}

internal void
vcbat_gui_file_list_reset(
    VCBatGuiFileListRef file_list) {

    vcbat_memory_arena_clear(file_list.arena);
    file_list.count  = 0;
    file_list.index  = 0;
    file_list.memory = NULL;    
}

internal void
vcbat_gui_file_list_add(
          VCBatGuiFileListRef file_list_ref,
    const char*               file_path) {

    //verify string isn't null
    VCBAT_ASSERT(file_path);

    //verify string length
    u32 file_path_length = strlen(file_path);
    VCBAT_ASSERT(
        file_path_length > 0 &&
        file_path_length <= VCBAT_GUI_FILE_PATH_SIZE);

    //get memory block for our file path
    memory file_path_memory = 
        vcbat_memory_arena_bytes_push(
                file_list_ref.arena,
                VCBAT_GUI_FILE_PATH_SIZE);

    VCBAT_ASSERT(file_path_memory);

    //if this is our first path, just set the memory as the path
    if (!file_list_ref.memory) {
        file_list_ref.memory = file_path_memory;
    }

    strcpy(
        (char*)file_path_memory,
        file_path
    );

    ++file_list_ref.count;
}

internal void
vcbat_gui_file_list_remove(
    VCBatGuiFileListRef file_list_ref,
    u32                 file_path_index) {

    VCBAT_ASSERT(file_path_index < file_list_ref.count);

    //if we're removing the last string, just pop off the bytes
    //otherwise, we need to shift everything down
    if (file_path_index != file_list_ref.count - 1) {

        u64    destination_offset = file_path_index * VCBAT_GUI_BUILD_SETTINGS_DIRECTORY_STRING_SIZE; 
        u64    shift_size         = (file_list_ref.count - file_path_index - 1) * VCBAT_GUI_BUILD_SETTINGS_DIRECTORY_STRING_SIZE; 
        memory destination        = (memory)&file_list_ref.memory[destination_offset];
        memory source             = destination + VCBAT_GUI_BUILD_SETTINGS_DIRECTORY_STRING_SIZE;

        memmove(
            destination,
            source,
            shift_size
        );
    }

    //lastly, pop the bytes off and update the count 
    vcbat_memory_arena_bytes_pop(
        file_list_ref.arena,
        VCBAT_GUI_BUILD_SETTINGS_DIRECTORY_STRING_SIZE);

    --file_list_ref.count;
}

internal void
vcbat_gui_file_list_update(
          VCBatGuiFileListRef file_list_ref,
    const u32                 file_path_index,
    const char*               file_path_new) {

    VCBAT_ASSERT(
        file_path_index < file_list_ref.count &&
        file_list_ref.count > 0               &&
        file_path_new);

    u64 file_path_offset = file_path_index * VCBAT_GUI_FILE_PATH_SIZE;
    char* file_path_cstr = (char*)&file_list_ref.memory[file_path_offset];

    memset(
        file_path_cstr,
        0,
        VCBAT_GUI_FILE_PATH_SIZE);

    strcpy(
        file_path_cstr,
        file_path_new        
    );

}

internal const char*
vcbat_gui_file_list_cstr(
    VCBatGuiFileListRef file_list_ref,
    u32                 index) {

    VCBAT_ASSERT(index < file_list_ref.count);

    u32 file_path_offset = VCBAT_GUI_FILE_PATH_SIZE * index; 

    const char* file_path_cstr = 
        (char*)&file_list_ref.memory[file_path_offset];

    return(file_path_cstr);
}


internal const char*
vcbat_gui_file_list_cstr_begin(
    VCBatGuiFileListRef file_list_ref) {

    if (file_list_ref.count == 0) {
        return(NULL);
    }

    file_list_ref.index = 0;

    const char* file_path_cstr = (char*)file_list_ref.memory;

    return(file_path_cstr);
}

internal const char*
vcbat_gui_file_list_cstr_next(
    VCBatGuiFileListRef file_list_ref) {
    
    if (file_list_ref.index >= file_list_ref.count) {
        file_list_ref.index = file_list_ref.count - 1;
    }

    if (
        file_list_ref.count == 0 ||
        file_list_ref.index == file_list_ref.count - 1) {
        
        return(NULL);
    }

    ++file_list_ref.index;

    u64 file_path_offset = VCBAT_GUI_FILE_PATH_SIZE * file_list_ref.index; 

    const char* file_path_cstr = 
        (char*)&file_list_ref.memory[file_path_offset];

    return(file_path_cstr);
}

internal void
vbat_gui_file_list_render(
    VCBatGuiFileListRef file_list_ref) {

    //TODO: we dont have a way of removing duplicates, we should have a way to do that
    ImGui::SeparatorText(file_list_ref.name);

    char add_button_name[32] = {0};
    strcpy(add_button_name,"Add File##");
    strcat(add_button_name,file_list_ref.name);
    if (ImGui::Button(add_button_name)) {

        VCBatPlatformFileDialogOptions dialog_options;
        
        dialog_options.dialog_type        = VCBatPlatformFileDialogType_File;
        dialog_options.starting_directory = vcbat_build_settings_window.directories.working;

        vcbat_platform_api_file_dialog(dialog_options);        

        vcbat_gui_file_list_add(
            file_list_ref,
            dialog_options.selected_path
        );
    }

    //table columns 
    char column_name_text[32] = {0};
    char column_name_btn1[32] = {0};
    char column_name_btn2[32] = {0};

    strcpy(column_name_text,file_list_ref.name);
    strcpy(column_name_btn1,file_list_ref.name);
    strcpy(column_name_btn2,file_list_ref.name);

    strcat(column_name_text,"##text");
    strcat(column_name_btn1,"##btn1");
    strcat(column_name_btn2,"##btn2");

    //button names
    char button_1_name[512] = {0};
    char button_2_name[512] = {0};

    ImGuiTableFlags table_flags = 
        ImGuiTableFlags_RowBg;

    if (ImGui::BeginTable("Source Files",3,table_flags)) {

        u32 button_column_width = vcbat_gui_text_width_pixels("Browse");

        ImGui::TableSetupColumn(column_name_text, ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn(column_name_btn1, ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn(column_name_btn2, ImGuiTableColumnFlags_WidthStretch);

        std::atof

        ImGui::TableSetColumnWidth(1.button_column_width);
        ImGui::TableSetColumnWidth(2,);

        int row = 0;

        local char tmp_path[256];
        local s32  row_update_index = -1;

        char button_name_remove[512] = {0};
        char button_name_update[512] = {0};

        for (
            const char* file_path = vcbat_gui_file_list_cstr_begin(file_list_ref);
            file_path != NULL;
            file_path = vcbat_gui_file_list_cstr_next(file_list_ref)) {

            VCBAT_ASSERT(file_path);
            
            ImGui::TableNextRow();

            //current row is being updated
            if (row_update_index == -1) {

                //file path readonly
                ImGui::TableSetColumnIndex(0);
                ImGui::Text(file_path);

                //update
                ImGui::TableSetColumnIndex(1);
                
                strcpy(button_1_name,"Update##");
                strcat(button_1_name,file_list_ref.name);
                strcat(button_1_name,file_path);

                if (ImGui::Button(button_1_name)) {
                    
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

                strcpy(button_2_name,"Remove##");
                strcat(button_2_name,file_list_ref.name);
                strcat(button_2_name,file_path);
                if (ImGui::Button(button_2_name)) {
                    vcbat_gui_file_list_remove(file_list_ref,row);
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
                
                strcpy(button_1_name,"Save##");
                strcat(button_1_name,file_list_ref.name);
                strcat(button_1_name,file_path);
                
                if (ImGui::Button(button_1_name)) {
                    vcbat_gui_file_list_update(file_list_ref,row,tmp_path);
                    row_update_index = -1;
                }

                //remove
                ImGui::TableSetColumnIndex(2);

                strcpy(button_2_name,"Browse##");
                strcat(button_2_name,file_list_ref.name);
                strcat(button_2_name,file_path);
                if (ImGui::Button(button_2_name)) {

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
                        vcbat_gui_file_list_update(file_list_ref,row,tmp_path);
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

            memset(button_1_name,0,512);
            memset(button_2_name,0,512);

            row++;
        }

        ImGui::EndTable();
    }
}