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

internal void
vcbat_win32_platform_api_file_dialog(
    VCBatPlatformFileDialogOptions& options) {

    VCBatWin32WindowRef win32_window_ref = vcbat_win32_window_get();
    options.user_made_selection = false;

    //initialize the file dialog pointer
    IFileDialog* file_dialog_ptr = NULL;

    HRESULT result = 
        CoCreateInstance(
            CLSID_FileOpenDialog, 
            NULL, 
            CLSCTX_ALL, 
            IID_IFileDialog, 
            reinterpret_cast<void**>(&file_dialog_ptr));

    VCBAT_ASSERT(SUCCEEDED(result));

    //get the options
    DWORD win32_dialog_options;
    file_dialog_ptr->GetOptions(&win32_dialog_options);

    //set the options based on the arguments
    win32_dialog_options |= 
        options.dialog_type == VCBatPlatformFileDialogType_Directory
            ? FOS_PATHMUSTEXIST | FOS_PICKFOLDERS 
            : FOS_FILEMUSTEXIST;

    file_dialog_ptr->SetOptions(win32_dialog_options);

    //show the dialog
    result = file_dialog_ptr->Show(win32_window_ref.handle_window);
    if (!SUCCEEDED(result)) {
        return;
    }

    //get the selected item
    IShellItem* shell_item_ptr = NULL;
    result = file_dialog_ptr->GetResult(&shell_item_ptr);
    VCBAT_ASSERT(SUCCEEDED(result));

    //get the display name of the item
    LPWSTR display_name = NULL;
    result = shell_item_ptr->GetDisplayName(
        SIGDN_FILESYSPATH,
        &display_name);
    VCBAT_ASSERT(SUCCEEDED(result));

    //convert the display name to a const char
    int size_needed = 
        WideCharToMultiByte(
            CP_UTF8, 
            0, 
            display_name, 
            -1, 
            NULL, 
            0, 
            NULL, 
            NULL);
        
    VCBAT_ASSERT(size_needed < VCBAT_PLATFORM_FILE_DIALOG_PATH_LENGTH); 

    WideCharToMultiByte(
        CP_UTF8,
        0,
        display_name,
        -1,
        options.selected_path, 
        size_needed,
        NULL,
        NULL);

    //release the stuff we used
    CoTaskMemFree(display_name);
    shell_item_ptr->Release();
    file_dialog_ptr->Release();

    options.user_made_selection = true;
}