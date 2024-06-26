#pragma once

#include "vcbat-gui.hpp"

internal VCBatGuiFileList
vcbat_gui_file_list_create(
    const char* file_list_name) {

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