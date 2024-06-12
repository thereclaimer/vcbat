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
