#pragma once

#include "vcbat-cl.hpp"

global VCBatCl vcbat_cl;

internal VCBatClPtr
vcbat_cl_create_and_initialize() {

    vcbat_cl = {0};

    vcbat_cl.script_variables.string_var_optimization    = vcbat_string_new(VCBAT_CL_STRING_OPTIMIZATIONS); 
    vcbat_cl.script_variables.string_var_code_generation = vcbat_string_new(VCBAT_CL_STRING_CODE_GENERATION); 
    vcbat_cl.script_variables.string_var_output_files    = vcbat_string_new(VCBAT_CL_STRING_OUTPUT_FILES); 
    vcbat_cl.script_variables.string_var_preprocessor    = vcbat_string_new(VCBAT_CL_STRING_PREPROCESSOR); 
    vcbat_cl.script_variables.string_var_header_modules  = vcbat_string_new(VCBAT_CL_STRING_HEADER_MODULES); 
    vcbat_cl.script_variables.string_var_language        = vcbat_string_new(VCBAT_CL_STRING_LANGUAGE); 
    vcbat_cl.script_variables.string_var_linking         = vcbat_string_new(VCBAT_CL_STRING_LINKING); 
    vcbat_cl.script_variables.string_var_miscellaneous   = vcbat_string_new(VCBAT_CL_STRING_MISCELLANEOUS); 
    vcbat_cl.script_variables.string_var_diagnostics     = vcbat_string_new(VCBAT_CL_STRING_DIAGNOSTICS); 
    vcbat_cl.script_variables.string_var_experimental    = vcbat_string_new(VCBAT_CL_STRING_EXPERIMENTAL); 
    vcbat_cl.script_variables.string_var_deprecated      = vcbat_string_new(VCBAT_CL_STRING_DEPRECATED); 

    return(&vcbat_cl);
}

const char*
vcbat_cl_build_script() {

    const char* vcbat_cl_script_variable_optimization    = vcbat_string_cstr(vcbat_cl.script_variables.string_var_optimization);
    const char* vcbat_cl_script_variable_code_generation = vcbat_string_cstr(vcbat_cl.script_variables.string_var_code_generation);
    const char* vcbat_cl_script_variable_output_files    = vcbat_string_cstr(vcbat_cl.script_variables.string_var_output_files);
    const char* vcbat_cl_script_variable_preprocessor    = vcbat_string_cstr(vcbat_cl.script_variables.string_var_preprocessor);
    const char* vcbat_cl_script_variable_header_modules  = vcbat_string_cstr(vcbat_cl.script_variables.string_var_header_modules);
    const char* vcbat_cl_script_variable_language        = vcbat_string_cstr(vcbat_cl.script_variables.string_var_language);
    const char* vcbat_cl_script_variable_linking         = vcbat_string_cstr(vcbat_cl.script_variables.string_var_linking);
    const char* vcbat_cl_script_variable_miscellaneous   = vcbat_string_cstr(vcbat_cl.script_variables.string_var_miscellaneous);
    const char* vcbat_cl_script_variable_diagnostics     = vcbat_string_cstr(vcbat_cl.script_variables.string_var_diagnostics);
    const char* vcbat_cl_script_variable_experimental    = vcbat_string_cstr(vcbat_cl.script_variables.string_var_experimental);
    const char* vcbat_cl_script_variable_deprecated      = vcbat_string_cstr(vcbat_cl.script_variables.string_var_deprecated);

    return(NULL);
}