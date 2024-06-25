#pragma once

#include "vcbat-core.hpp"

internal VCBatStringHandle
vcbat_string_empty() {

    //reserve an arena for the string
    VCBatMemoryArenaHandle arena = vcbat_memory_arena_reserve();
    VCBAT_ASSERT(arena);

    //allocate space for the string structure
    VCBatStringPtr string_ptr = 
        (VCBatStringPtr)vcbat_memory_arena_bytes_push(
            arena,
            sizeof(VCBatString)); 
    VCBAT_ASSERT(string_ptr);

    //set our string data
    string_ptr->arena_handle        = arena;
    string_ptr->string_data         = NULL;
    string_ptr->string_length_bytes = 0; 

    return(string_ptr);
}


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


internal void
vcbat_string_clear(
    VCBatStringHandle string_handle) {
    
    if (!string_handle) {
        return;
    }

    VCBatStringPtr string_ptr = (VCBatStringPtr)string_handle; 

    vcbat_memory_arena_bytes_pop(
        string_ptr->arena_handle,
        string_ptr->string_length_bytes);

    string_ptr->string_data         = NULL;
    string_ptr->string_length_bytes = 0;
}


internal void
vcbat_string_append(
          VCBatStringHandle string_handle,
    const char*             append_string_val) {

    if (!string_handle) {
        return;
    }

    //dereference our string
    VCBatStringPtr string_ptr = (VCBatStringPtr)string_handle;
    VCBatString    string     =  *string_ptr;

    //make sure there's an arena here
    VCBAT_ASSERT(string.arena_handle);

    //first, determine if there's a null character we need to remove
    //TODO: i think there always is...
    if (
        string.string_data              &&
        string.string_length_bytes >= 1 &&
        string.string_data[string.string_length_bytes - 1] == '\0') {

        string.string_length_bytes -= 1;
        vcbat_memory_arena_bytes_pop(
            string.arena_handle,            
            1);
    }

    //push our string onto the arena
    u64 append_string_length = strlen(append_string_val);

    memory append_string_memory = 
        vcbat_memory_arena_bytes_push(
            string.arena_handle,
            append_string_length);

    memmove(
        append_string_memory,
        append_string_val,
        append_string_length);

    //if this is the first string, just put it as the memory 
    if (!string.string_data) {
        string.string_data = append_string_memory; 
    }

    string.string_length_bytes += append_string_length;

    //write our string back to memory
    *string_ptr = string; 
}

internal void
vcbat_string_append_newline(
    VCBatStringHandle string_handle) {

    vcbat_string_append(
        string_handle,
        "\n");
}