#pragma once

#include "vcbat-core.hpp"

global VCBatBuildScript vcbat_build_script;

internal VCBatBuildScriptPtr
vcbat_build_script_create_and_initialize() {

    vcbat_build_script = {0};

    vcbat_build_script.script_string = vcbat_string_empty();

    vcbat_build_script.variables.optimization    = vcbat_string_new(VCBAT_BUILD_SCRIPT_STRING_OPTIMIZATIONS); 
    vcbat_build_script.variables.code_generation = vcbat_string_new(VCBAT_BUILD_SCRIPT_STRING_CODE_GENERATION); 
    vcbat_build_script.variables.output_files    = vcbat_string_new(VCBAT_BUILD_SCRIPT_STRING_OUTPUT_FILES); 
    vcbat_build_script.variables.preprocessor    = vcbat_string_new(VCBAT_BUILD_SCRIPT_STRING_PREPROCESSOR); 
    vcbat_build_script.variables.header_modules  = vcbat_string_new(VCBAT_BUILD_SCRIPT_STRING_HEADER_MODULES); 
    vcbat_build_script.variables.language        = vcbat_string_new(VCBAT_BUILD_SCRIPT_STRING_LANGUAGE); 
    vcbat_build_script.variables.linking         = vcbat_string_new(VCBAT_BUILD_SCRIPT_STRING_LINKING); 
    vcbat_build_script.variables.miscellaneous   = vcbat_string_new(VCBAT_BUILD_SCRIPT_STRING_MISCELLANEOUS); 
    vcbat_build_script.variables.diagnostics     = vcbat_string_new(VCBAT_BUILD_SCRIPT_STRING_DIAGNOSTICS); 
    vcbat_build_script.variables.experimental    = vcbat_string_new(VCBAT_BUILD_SCRIPT_STRING_EXPERIMENTAL); 
    vcbat_build_script.variables.deprecated      = vcbat_string_new(VCBAT_BUILD_SCRIPT_STRING_DEPRECATED); 

    return(&vcbat_build_script);
}

const char*
vcbat_build_script_string() {

    vcbat_string_clear(vcbat_build_script.script_string);

    const char* vcbat_build_script_variable_optimization    = vcbat_string_cstr(vcbat_build_script.variables.optimization);
    const char* vcbat_build_script_variable_code_generation = vcbat_string_cstr(vcbat_build_script.variables.code_generation);
    const char* vcbat_build_script_variable_output_files    = vcbat_string_cstr(vcbat_build_script.variables.output_files);
    const char* vcbat_build_script_variable_preprocessor    = vcbat_string_cstr(vcbat_build_script.variables.preprocessor);
    const char* vcbat_build_script_variable_header_modules  = vcbat_string_cstr(vcbat_build_script.variables.header_modules);
    const char* vcbat_build_script_variable_language        = vcbat_string_cstr(vcbat_build_script.variables.language);
    const char* vcbat_build_script_variable_linking         = vcbat_string_cstr(vcbat_build_script.variables.linking);
    const char* vcbat_build_script_variable_miscellaneous   = vcbat_string_cstr(vcbat_build_script.variables.miscellaneous);
    const char* vcbat_build_script_variable_diagnostics     = vcbat_string_cstr(vcbat_build_script.variables.diagnostics);
    const char* vcbat_build_script_variable_experimental    = vcbat_string_cstr(vcbat_build_script.variables.experimental);
    const char* vcbat_build_script_variable_deprecated      = vcbat_string_cstr(vcbat_build_script.variables.deprecated);

    vcbat_string_append(vcbat_build_script.script_string, vcbat_build_script_variable_optimization);
    vcbat_string_append(vcbat_build_script.script_string, "\n\n");
    vcbat_string_append(vcbat_build_script.script_string, vcbat_build_script_variable_code_generation);
    vcbat_string_append(vcbat_build_script.script_string, "\n\n");
    vcbat_string_append(vcbat_build_script.script_string, vcbat_build_script_variable_output_files);
    vcbat_string_append(vcbat_build_script.script_string, "\n\n");
    vcbat_string_append(vcbat_build_script.script_string, vcbat_build_script_variable_preprocessor);
    vcbat_string_append(vcbat_build_script.script_string, "\n\n");
    vcbat_string_append(vcbat_build_script.script_string, vcbat_build_script_variable_header_modules);
    vcbat_string_append(vcbat_build_script.script_string, "\n\n");
    vcbat_string_append(vcbat_build_script.script_string, vcbat_build_script_variable_language);
    vcbat_string_append(vcbat_build_script.script_string, "\n\n");
    vcbat_string_append(vcbat_build_script.script_string, vcbat_build_script_variable_linking);
    vcbat_string_append(vcbat_build_script.script_string, "\n\n");
    vcbat_string_append(vcbat_build_script.script_string, vcbat_build_script_variable_miscellaneous);
    vcbat_string_append(vcbat_build_script.script_string, "\n\n");
    vcbat_string_append(vcbat_build_script.script_string, vcbat_build_script_variable_diagnostics);
    vcbat_string_append(vcbat_build_script.script_string, "\n\n");
    vcbat_string_append(vcbat_build_script.script_string, vcbat_build_script_variable_experimental);
    vcbat_string_append(vcbat_build_script.script_string, "\n\n");
    vcbat_string_append(vcbat_build_script.script_string, vcbat_build_script_variable_deprecated);
    vcbat_string_append(vcbat_build_script.script_string, "\n\n");
    vcbat_string_append(vcbat_build_script.script_string, VCBAT_BUILD_SCRIPT_STRING_CL_CALL);


    const char* script_string = vcbat_string_cstr(vcbat_build_script.script_string);

    return(script_string);
}