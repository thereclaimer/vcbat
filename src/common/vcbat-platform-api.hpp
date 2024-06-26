#ifndef VCBAT_PLATFORM_API
#define VCBAT_PLATFORM_API

#include "vcbat-types.hpp"

typedef memory 
(*func_vcbat_platform_memory_allocate)
(
    u64 size
);

typedef void 
(*func_vcbat_platform_memory_free)
(
    handle, 
    u64
);

typedef  u64 
(*func_vcbat_platform_file_size)
(
    handle file_path,
    b8     terminate
);

typedef handle
(*func_vcbat_platform_file_open)
(
    const wchar_t* file_path,
    b8             create_new
);

typedef void
(*func_vcbat_platform_file_close)
(
    handle file_handle
);

typedef void
(*func_vcbat_platform_file_write)
(
    handle file_handle,
    u64    offset,
    u64    allocated_buffer_size,
    memory allocated_buffer
);

typedef void
(*func_vcbat_platform_file_read)
(
    handle file_handle,
    u64    offset,
    u64    allocated_buffer_size,
    memory allocated_buffer,
    b8     terminate
);

#define VCBAT_PLATFORM_FILE_DIALOG_PATH_LENGTH 256

enum VCBatPlatformFileDialogType_ {
     VCBatPlatformFileDialogType_File      = 0,
     VCBatPlatformFileDialogType_Directory = 1
};

typedef u32 VCBatPlatformFileDialogType; 

struct VCBatPlatformFileDialogOptions {
    VCBatPlatformFileDialogType dialog_type;
    char*                       starting_directory;
    char                        selected_path[VCBAT_PLATFORM_FILE_DIALOG_PATH_LENGTH]; 
};

typedef void
(*func_vcbat_platform_file_dialog)(
    VCBatPlatformFileDialogOptions& options);

struct VCBatPlatformApi {
    func_vcbat_platform_memory_allocate memory_allocate;
    func_vcbat_platform_memory_free     memory_free;
    func_vcbat_platform_file_size       file_size;
    func_vcbat_platform_file_open       file_open;
    func_vcbat_platform_file_close      file_close;
    func_vcbat_platform_file_write      file_write;
    func_vcbat_platform_file_read       file_read;
    func_vcbat_platform_file_dialog     file_dialog;
};

global VCBatPlatformApi vcbat_platform_api;

#define vcbat_platform_api_memory_allocate vcbat_platform_api.memory_allocate
#define vcbat_platform_api_memory_free     vcbat_platform_api.memory_free
#define vcbat_platform_api_file_size       vcbat_platform_api.file_size
#define vcbat_platform_api_file_open       vcbat_platform_api.file_open
#define vcbat_platform_api_file_close      vcbat_platform_api.file_close
#define vcbat_platform_api_file_write      vcbat_platform_api.file_write
#define vcbat_platform_api_file_read       vcbat_platform_api.file_read
#define vcbat_platform_api_file_dialog     vcbat_platform_api.file_dialog

#endif //VCBAT_PLATFORM_API