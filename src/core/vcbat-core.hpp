#ifndef VCBAT_CORE_HPP
#define VCBAT_CORE_HPP

#include "vcbat.hpp"
#include "vcbat-cl-options.hpp"
#include "vcbat-gui.hpp"

//-------------------------------------------------
// TYPES
//-------------------------------------------------

//core
struct  VCBat; 
typedef VCBat* VCBatPtr; 
typedef VCBat& VCBatRef; 

//memory
struct  VCBatMemory;
typedef VCBatMemory* VCBatMemoryPtr;
typedef VCBatMemory& VCBatMemoryRef;

//arena
struct  VCBatMemoryArena;
typedef VCBatMemoryArena* VCBatMemoryArenaPtr;
typedef VCBatMemoryArena& VCBatMemoryArenaRef;
typedef handle            VCBatMemoryArenaHandle;

//script
struct  VCBatBuildScript;
typedef VCBatBuildScript* VCBatBuildScriptPtr;
typedef VCBatBuildScript& VCBatBuildScriptRef;

//-------------------------------------------------
// CORE
//-------------------------------------------------

struct VCBat {
    VCBatMemoryPtr      memory_ptr;
    VCBatGuiPtr         gui_ptr;
    VCBatBuildScriptPtr build_script_ptr;
};

VCBat
vcbat_create_and_initialize(
    VCBatPlatformApi platform_api);

b8
vcbat_update(
    VCBatRef vcbat_ref);


//-------------------------------------------------
// MEMORY
//-------------------------------------------------

//sizes
#define VCBAT_MEMORY_KILOBYTES(n) (n * 1024)
#define VCBAT_MEMORY_MEGABYTES(n) (VCBAT_MEMORY_KILOBYTES(n) * 1024)
#define VCBAT_MEMORY_GIGABYTES(n) (VCBAT_MEMORY_MEGABYTES(n) * 1024)

//arena
#define VCBAT_MEMORY_ARENA_SIZE_BYTES VCBAT_MEMORY_KILOBYTES(8)

struct VCBatMemoryArena {
    u64                 bytes_used;
    memory              memory;
    VCBatMemoryArenaPtr next;
    VCBatMemoryArenaPtr previous;
};

VCBatMemoryArenaHandle
vcbat_memory_arena_reserve();

void
vcbat_memory_arena_release(
    VCBatMemoryArenaHandle arena);

memory
vcbat_memory_arena_bytes_push(
    VCBatMemoryArenaHandle arena,
    u64                    size);

void
vcbat_memory_arena_bytes_pop(
    VCBatMemoryArenaHandle arena,
    u64                    size);

void    
vcbat_memory_arena_clear(
    VCBatMemoryArenaHandle arena);

u64
vcbat_memory_arena_space_available(
    VCBatMemoryArenaHandle arena);

u64
vcbat_memory_arena_space_used(
    VCBatMemoryArenaHandle arena);

#define VCBAT_MEMORY_SIZE VCBAT_MEMORY_MEGABYTES(128)

struct VCBatMemory {
    u64                 platform_memory_size_bytes;
    memory              platform_memory;
    u64                 arenas_count_total;
    VCBatMemoryArenaPtr arenas_reserved;
    VCBatMemoryArenaPtr arenas_available;
};

struct VCBatMemoryInfo {
    u64 arenas_total;
    u64 arenas_reserved;
    u64 arenas_available;
    u64 platform_memory;
    u64 platform_memory_available;
    u64 platform_memory_used;
};

typedef VCBatMemoryInfo* VCBatMemoryInfoPtr;
typedef VCBatMemoryInfo& VCBatMemoryInfoRef;

VCBatMemoryPtr
vcbat_memory_create_and_initialize();

void
vcbat_memory_info(
    VCBatMemoryInfoRef memory_info_ref);

//-------------------------------------------------
// STRING
//-------------------------------------------------

struct VCBatString {
    VCBatMemoryArenaHandle arena_handle;
    u64                    string_length_bytes;
    memory                 string_data;                 
};

typedef VCBatString* VCBatStringPtr; 
typedef VCBatString& VCBatStringRef; 
typedef handle       VCBatStringHandle;

VCBatStringHandle
vcbat_string_empty();

VCBatStringHandle
vcbat_string_new(
    const char* string_val);

void
vcbat_string_delete(
    VCBatStringHandle string_handle);

u64
vcbat_string_length(
    VCBatStringHandle string_handle);

const char*
vcbat_string_cstr(
    VCBatStringHandle string_handle);

void
vcbat_string_clear(
    VCBatStringHandle string_handle);

void
vcbat_string_append(
    VCBatStringHandle string_handle,
    const char*       append_string_val);

void
vcbat_string_append_newline(
    VCBatStringHandle string_handle);

//-------------------------------------------------
// BUILD SCRIPT
//-------------------------------------------------

const char* VCBAT_BUILD_SCRIPT_STRING_OPTIMIZATIONS   = "@set cl_optimizations=";
const char* VCBAT_BUILD_SCRIPT_STRING_CODE_GENERATION = "@set cl_code_generation=";
const char* VCBAT_BUILD_SCRIPT_STRING_OUTPUT_FILES    = "@set cl_output_files=";
const char* VCBAT_BUILD_SCRIPT_STRING_PREPROCESSOR    = "@set cl_preprocessor=";
const char* VCBAT_BUILD_SCRIPT_STRING_HEADER_MODULES  = "@set cl_header_modules=";
const char* VCBAT_BUILD_SCRIPT_STRING_LANGUAGE        = "@set cl_language=";
const char* VCBAT_BUILD_SCRIPT_STRING_LINKING         = "@set cl_linking=";
const char* VCBAT_BUILD_SCRIPT_STRING_MISCELLANEOUS   = "@set cl_miscellaneous=";
const char* VCBAT_BUILD_SCRIPT_STRING_DIAGNOSTICS     = "@set cl_diagnostics=";
const char* VCBAT_BUILD_SCRIPT_STRING_EXPERIMENTAL    = "@set cl_experimental=";
const char* VCBAT_BUILD_SCRIPT_STRING_DEPRECATED      = "@set cl_deprecated=";

struct VCBatBuildScriptArg {
    VCBatMemoryArenaHandle arena;
    VcBatClOption          cl_option;
    VCBatStringHandle      cl_arg_string;    
};

typedef VCBatBuildScriptArg* VCBatBuildScriptArgPtr;
typedef VCBatBuildScriptArg& VCBatBuildScriptArgRef;

struct VCBatBuildScriptArgs {
    VCBatBuildScriptArgPtr optimization[VCBAT_CL_OPTIONS_COUNT_OPTIMIZATIONS];
    VCBatBuildScriptArgPtr code_generation[VCBAT_CL_OPTIONS_COUNT_CODE_GENERATION];
    VCBatBuildScriptArgPtr output_files[VCBAT_CL_OPTIONS_COUNT_OUTPUT_FILES];
    VCBatBuildScriptArgPtr preprocessor[VCBAT_CL_OPTIONS_COUNT_PREPROCESSOR];
    VCBatBuildScriptArgPtr header_modules[VCBAT_CL_OPTIONS_COUNT_HEADER_MODULES];
    VCBatBuildScriptArgPtr language[VCBAT_CL_OPTIONS_COUNT_LANGUAGE];
    VCBatBuildScriptArgPtr linking[VCBAT_CL_OPTIONS_COUNT_LINKING];
    VCBatBuildScriptArgPtr miscellaneous[VCBAT_CL_OPTIONS_COUNT_MISCELLANEOUS];
    VCBatBuildScriptArgPtr diagnostics[VCBAT_CL_OPTIONS_COUNT_DIAGNOSTICS];
    VCBatBuildScriptArgPtr experimental[VCBAT_CL_OPTIONS_COUNT_EXPERIMENTAL];
    VCBatBuildScriptArgPtr deprecated[VCBAT_CL_OPTIONS_COUNT_DEPRECATED];
};

struct VCBatBuildScriptVars {
    VCBatStringHandle optimization;
    VCBatStringHandle code_generation;
    VCBatStringHandle output_files;
    VCBatStringHandle preprocessor;
    VCBatStringHandle header_modules;
    VCBatStringHandle language;
    VCBatStringHandle linking;
    VCBatStringHandle miscellaneous;
    VCBatStringHandle diagnostics;
    VCBatStringHandle experimental;
    VCBatStringHandle deprecated;
};

struct VCBatBuildScript {
    VCBatStringHandle    script_string;
    VCBatBuildScriptArgs args;
    VCBatBuildScriptVars variables;
};

VCBatBuildScriptPtr
vcbat_build_script_create_and_initialize();

const char*
vcbat_build_script_build_script();

#endif //VCBAT_CORE_HPP