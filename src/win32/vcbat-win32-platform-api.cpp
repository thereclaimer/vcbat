#pragma once

#include "vcbat-win32.hpp"

VCBatPlatformApi
vcbat_win32_platform_api_create_and_init() {

    VCBatPlatformApi platform_api = {0};

    platform_api.memory_allocate = vcbat_win32_platform_api_allocate_memory;
    platform_api.memory_free     = vcbat_win32_platform_api_free_memory;
    platform_api.file_size       = vcbat_win32_platform_api_file_size_bytes;
    platform_api.file_open       = vcbat_win32_platform_api_file_open;
    platform_api.file_close      = vcbat_win32_platform_api_file_close;
    platform_api.file_read       = vcbat_win32_platform_api_file_read;
    platform_api.file_write      = vcbat_win32_platform_api_file_write;
    platform_api.file_dialog     = vcbat_win32_platform_api_file_dialog;
    
    return(platform_api);
}

u64 bytes_read;

void CALLBACK
vcbat_win32_platform_api_file_io_completion_routine(
    DWORD        error_code,
    DWORD        bytes_transferred,
    LPOVERLAPPED lpOverlapped) {
        
    bytes_read = bytes_transferred;
}

internal u64
vcbat_win32_platform_api_file_size_bytes(
    HANDLE file_handle,
    b8     terminate) {

    //get the initial file size
    u64 file_size = 
        (file_handle == INVALID_HANDLE_VALUE)
        ? 0
        : GetFileSize(file_handle, NULL);

    //if we dont care about termination, we're done
    if (!terminate) {
        return(file_size);
    }

    //if we do care, get the last byte
    OVERLAPPED overlapped = {0};

    overlapped.Offset = file_size - 1;
    u8 last_byte;
    bool read_result = 
        ReadFileEx(
            file_handle,
            &last_byte,
            1,
            &overlapped,
            vcbat_win32_platform_api_file_io_completion_routine
        );

    //if its not terminated, account for a null terminator
    file_size += last_byte == '\0' ? 0 : 1;

    return(file_size);
}

internal HANDLE
vcbat_win32_platform_api_file_open(
    const wchar_t* file_path,
          b8       create_new) {

    HANDLE file_handle = 
        CreateFile(
            file_path,
            (GENERIC_READ | GENERIC_WRITE),
            (FILE_SHARE_READ | FILE_SHARE_WRITE),
            NULL,
            create_new ? CREATE_ALWAYS : OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
            NULL
    );

    return (file_handle == INVALID_HANDLE_VALUE)
        ? NULL
        : file_handle;
}

internal void
vcbat_win32_platform_api_file_close(
    HANDLE file_handle) {

    CloseHandle(file_handle);
}


internal void
vcbat_win32_platform_api_file_read(
    HANDLE file_handle,
    u64    offset,
    u64    allocated_buffer_size,
    memory allocated_buffer,
    b8     terminate) {

    VCBAT_ASSERT(file_handle);
    VCBAT_ASSERT(allocated_buffer);

    OVERLAPPED overlapped = {0};

    overlapped.Offset = offset;

    u64 adjusted_size   = terminate ? allocated_buffer_size - 1 : allocated_buffer_size;
    u64 last_byte_index = adjusted_size - 1;

    bool read_result = 
        ReadFileEx(
            file_handle,
            allocated_buffer,
            adjusted_size,
            &overlapped,
            vcbat_win32_platform_api_file_io_completion_routine
    );

    DWORD error = GetLastError();
    
    if (!terminate || allocated_buffer[last_byte_index] == '\0') {
        return;
    }

    allocated_buffer[last_byte_index] = '\0';
}

internal void
vcbat_win32_platform_api_file_write(
    handle file_handle,
    u64    allocated_buffer_size,
    u64    offset,
    memory allocated_buffer) {

    OVERLAPPED overlapped = {0};

    overlapped.Offset = offset;

    bool read_result = WriteFileEx(
        file_handle,
        allocated_buffer,
        allocated_buffer_size,
        &overlapped,
        vcbat_win32_platform_api_file_io_completion_routine
    );
}

internal memory
vcbat_win32_platform_api_allocate_memory(u64 size) {

    memory mem = (memory)VirtualAlloc(0,size,MEM_COMMIT,PAGE_READWRITE);

    return(mem);
}

internal void
vcbat_win32_platform_api_free_memory(handle memory, u64 size) {

    VirtualFree(memory,size,MEM_RELEASE);
}

internal int CALLBACK
vcbat_win32_platform_api_browse_dialog_callback(
    HWND   hwnd, 
    UINT   msg, 
    LPARAM l_param, 
    LPARAM l_data) {

    if (msg == BFFM_INITIALIZED) {
        SendMessage(
            hwnd, 
            BFFM_SETSELECTION, 
            TRUE, 
            l_data);
    }

    return(0);
}

internal void
vcbat_win32_platform_api_file_dialog(
    VCBatPlatformFileDialogOptions& options) {

    VCBatWin32WindowRef win32_window_ref = vcbat_win32_window_get();
    switch(options.dialog_type) {
        
        case VCBatPlatformFileDialogType_File: {

            OPENFILENAMEA open_file_name = {0};
            open_file_name.lStructSize     = sizeof(OPENFILENAME);
            open_file_name.hwndOwner       = win32_window_ref.handle_window;
            open_file_name.lpstrFile       = options.selected_path;
            open_file_name.lpstrFile[0]    = '\0';
            open_file_name.nMaxFile        = VCBAT_PLATFORM_FILE_DIALOG_PATH_LENGTH;
            open_file_name.lpstrFilter     = "All\0*.*\0Text\0*.TXT\0";
            open_file_name.nFilterIndex    = 1;
            open_file_name.lpstrFileTitle  = NULL;
            open_file_name.nMaxFileTitle   = 0;
            open_file_name.lpstrInitialDir = NULL;
            open_file_name.Flags           = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

            bool path_selected = GetOpenFileNameA(&open_file_name);
            if (path_selected) {
                
            }

        } break;

        case VCBatPlatformFileDialogType_Directory: {

            BROWSEINFOA browse_info = {0};
            browse_info.ulFlags     = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
            browse_info.lpszTitle   = "Select a folder";
            browse_info.lpfn        = vcbat_win32_platform_api_browse_dialog_callback;
            browse_info.lParam      = (LPARAM)options.selected_path;

            LPITEMIDLIST item_list = SHBrowseForFolderA(&browse_info);
            if (item_list) {

                SHGetPathFromIDListA(item_list, options.selected_path);
                CoTaskMemFree(item_list);
            }

        } break;
    }



    
}