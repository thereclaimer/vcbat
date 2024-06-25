#ifndef VCBAT_CL_HPP
#define VCBAT_CL_HPP

#include "vcbat-types.hpp"
#include "vcbat-cl-options.hpp"
#include "vcbat-string.hpp"
#include "vcbat-memory.hpp"

const char* VCBAT_CL_STRING_OPTIMIZATIONS   = "@set cl_optimizations=";
const char* VCBAT_CL_STRING_CODE_GENERATION = "@set cl_code_generation=";
const char* VCBAT_CL_STRING_OUTPUT_FILES    = "@set cl_output_files=";
const char* VCBAT_CL_STRING_PREPROCESSOR    = "@set cl_preprocessor=";
const char* VCBAT_CL_STRING_HEADER_MODULES  = "@set cl_header_modules=";
const char* VCBAT_CL_STRING_LANGUAGE        = "@set cl_language=";
const char* VCBAT_CL_STRING_LINKING         = "@set cl_linking=";
const char* VCBAT_CL_STRING_MISCELLANEOUS   = "@set cl_miscellaneous=";
const char* VCBAT_CL_STRING_DIAGNOSTICS     = "@set cl_diagnostics=";
const char* VCBAT_CL_STRING_EXPERIMENTAL    = "@set cl_experimental=";
const char* VCBAT_CL_STRING_DEPRECATED      = "@set cl_deprecated=";

struct VCBatClArg {
    VCBatMemoryArenaHandle arena;
    VcBatClOption          cl_option;
    VCBatStringHandle      cl_arg_string;    
};

typedef VCBatClArg* VCBatClArgPtr;
typedef VCBatClArg& VCBatClArgRef;

struct VCBatClArgs {
    VCBatClArgPtr args_optimization[VCBAT_CL_OPTIONS_COUNT_OPTIMIZATIONS];
    VCBatClArgPtr args_code_generation[VCBAT_CL_OPTIONS_COUNT_CODE_GENERATION];
    VCBatClArgPtr args_output_files[VCBAT_CL_OPTIONS_COUNT_OUTPUT_FILES];
    VCBatClArgPtr args_preprocessor[VCBAT_CL_OPTIONS_COUNT_PREPROCESSOR];
    VCBatClArgPtr args_header_modules[VCBAT_CL_OPTIONS_COUNT_HEADER_MODULES];
    VCBatClArgPtr args_language[VCBAT_CL_OPTIONS_COUNT_LANGUAGE];
    VCBatClArgPtr args_linking[VCBAT_CL_OPTIONS_COUNT_LINKING];
    VCBatClArgPtr args_miscellaneous[VCBAT_CL_OPTIONS_COUNT_MISCELLANEOUS];
    VCBatClArgPtr args_diagnostics[VCBAT_CL_OPTIONS_COUNT_DIAGNOSTICS];
    VCBatClArgPtr args_experimental[VCBAT_CL_OPTIONS_COUNT_EXPERIMENTAL];
    VCBatClArgPtr args_deprecated[VCBAT_CL_OPTIONS_COUNT_DEPRECATED];
};

struct VCBatClScriptVars {
    VCBatStringHandle string_var_optimization;
    VCBatStringHandle string_var_code_generation;
    VCBatStringHandle string_var_output_files;
    VCBatStringHandle string_var_preprocessor;
    VCBatStringHandle string_var_header_modules;
    VCBatStringHandle string_var_language;
    VCBatStringHandle string_var_linking;
    VCBatStringHandle string_var_miscellaneous;
    VCBatStringHandle string_var_diagnostics;
    VCBatStringHandle string_var_experimental;
    VCBatStringHandle string_var_deprecated;
};

struct VCBatCl {
    VCBatClArgs       args;
    VCBatClScriptVars script_variables;
};

typedef VCBatCl* VCBatClPtr;
typedef VCBatCl& VCBatClRef;

VCBatClPtr
vcbat_cl_create_and_initialize();

const char*
vcbat_cl_build_script();

#endif //VCBAT_CL_HPP