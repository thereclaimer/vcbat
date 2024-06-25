#pragma once

#include "vcbat-string.hpp"

internal VCBatStringHandle
vcbat_string_new(
    const char* string_val) {

    //reserve an arena for the string
    VCBatMemoryArenaHandle arena = vcbat_memory_arena_reserve();
    VCBAT_ASSERT(arena);

    //allocate space for the string structure
    VCBatStringPtr string_ptr = 
        (VCBatStringPtr)vcbat_memory_arena_bytes_push(
            arena,
            sizeof(VCBatString)); 
    VCBAT_ASSERT(string_ptr);

    //allocate space for the string data
    u64 string_length_bytes = strlen(string_val);
    memory string_data = 
        vcbat_memory_arena_bytes_push(
            arena,
            string_length_bytes);
    VCBAT_ASSERT(string_data);

    //copy the string data
    memmove(
        string_data,
        string_val,
        string_length_bytes);

    //set our string data
    string_ptr->arena_handle        = arena;
    string_ptr->string_data         = string_data;
    string_ptr->string_length_bytes = string_length_bytes; 

    return(string_ptr);
}

internal void
vcbat_string_delete(
    VCBatStringPtr string) {

    if (!string) {
        return;
    }

    vcbat_memory_arena_release(string->arena_handle);
}

internal u64
vcbat_string_length(
    VCBatStringPtr string) {

    if(!string) {
        return(0);
    } 

    return(string->string_length_bytes);
}

internal const char*
vcbat_string_cstr(
    VCBatStringHandle string) {

    if (!string) {
        return(NULL);
    }

    VCBatStringPtr string_ptr = (VCBatStringPtr)string; 

    VCBAT_ASSERT(string_ptr->string_data);

    const char* cstr = (const char*)string_ptr->string_data;

    return(cstr);  
}