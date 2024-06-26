#ifndef VCBAT_CORE_HPP
#define VCBAT_CORE_HPP

#include "vcbat.hpp"
#include "vcbat-memory.hpp"
#include "vcbat-cl-options.hpp"
#include "vcbat-gui.hpp"

//-------------------------------------------------
// TYPES
//-------------------------------------------------

//core
struct  VCBat; 
typedef VCBat* VCBatPtr; 
typedef VCBat& VCBatRef; 

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

const char* VCBAT_BUILD_SCRIPT_STRING_CL_CALL = 
"call cl.exe              ^\n"
"    %cl_preprocessor%    ^\n"
"    %cl_optimizations%   ^\n"
"    %cl_code_generation% ^\n"
"    %cl_output_files%    ^\n"
"    %cl_header_modules%  ^\n"
"    %cl_language%        ^\n"
"    %cl_miscellaneous%   ^\n"
"    %cl_diagnostics%     ^\n"
"    %cl_experimental%    ^\n"
"    %cl_deprecated%      ^\n"
"    %cl_linking%         ^";

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
vcbat_build_script_string();

#endif //VCBAT_CORE_HPP