#pragma once

#include <string.h>

#include "vcbat.hpp"

internal VCBatStringManager
vcbat_string_manager_create_and_initialize(
    VCBatMemoryRef memory_ref) {

    //initialize the string memory
    VCBatMemoryArenaHandle string_memory_arena = 
        vcbat_memory_arena_push(
            memory_ref,
            VCBAT_STRING_MEMORY_SIZE_BYTES
        );

    VCBAT_ASSERT(string_memory_arena);

    VCBatStringAllocator string_allocator = {0};
    string_allocator.arena_handle = string_memory_arena;

    //initialize the manager
    VCBatStringManager string_manager = {0};
    string_manager.string_allocator = string_allocator;

    return(string_manager);
}

//TODO: for now, only strings of size 256 are supported
//we should be able to support strings of any size, consisting of
//256 byte blocks

internal VCBatStringHandle
vcbat_string_new(
          VCBatStringManagerRef string_manager_ref,
    const char*                 string_val) {

    u64 string_length = strlen(string_val);
    if (
        string_length == 0 || 
        string_length > VCBAT_STRING_MAX_SIZE_BYTES) {

        return(VCBAT_STRING_INVALID);
    }

    VCBatStringAllocatorRef string_allocator_ref = string_manager_ref.string_allocator;
    VCBatStringHandle       string_handle        = VCBAT_STRING_INVALID;

    auto string_array = string_manager_ref.string_array;
    VCBatStringPtr current_string_ptr = NULL;

    for (
        u64 string_index = 0;
        string_index < VCBAT_STRING_MAX_COUNT;
        ++string_index) {

        current_string_ptr = &string_array[string_index];
        if (!current_string_ptr->string_buffer) {
            string_handle = string_index;
        }
    }

    if (string_handle == VCBAT_STRING_INVALID) {
        return(VCBAT_STRING_INVALID);
    }

    VCBAT_ASSERT(current_string_ptr);

    u64 string_memory_offset = VCBAT_STRING_MAX_SIZE_BYTES * string_handle;

    char* string_memory =
        (char*)vcbat_memory_arena_memory_get(
            string_allocator_ref.arena_handle,
            string_memory_offset,
            VCBAT_STRING_MAX_SIZE_BYTES);

    VCBAT_ASSERT(string_memory);

    strcpy(
        string_memory,
        string_val);

    current_string_ptr->string_buffer_length_bytes = string_length;
    current_string_ptr->string_buffer              = string_memory;

    return(string_handle);
}

internal void
vcbat_string_delete(
          VCBatStringManagerRef string_manager_ref,
    const VCBatStringHandle     string_handle) {

    //dont bother if the string handle is invalid
    b8 string_valid = vcbat_string_valid(string_handle);
    if (!string_valid) {
        return;
    }

    //get the string
    VCBatString string = 
     string_manager_ref.string_array[string_handle];

    //if its already null, we're done
    if (!string.string_buffer) {
        return;
    }

    //zero and null the string
    memset(
        string.string_buffer,
        0,
        string.string_buffer_length_bytes);

    string.string_buffer              = NULL;
    string.string_buffer_length_bytes = 0;

    //write the string back
    string_manager_ref.string_array[string_handle] = string;
}

internal u64
vcbat_string_length(
          VCBatStringManagerRef string_manager_ref,
    const VCBatStringHandle     string_handle) {

    //dont bother if the string handle is invalid
    b8 string_valid = vcbat_string_valid(string_handle);
    if (!string_valid) {
        return(0);
    }

    //get the string
    VCBatString string = string_manager_ref.string_array[string_handle];

    //if its already null, we're done
    if (!string.string_buffer) {
        return(0);
    }

    u64 string_length = string.string_buffer_length_bytes;

    return(string_length);
}

const char*
vcbat_string_c_str(
          VCBatStringManagerRef string_manager_ref,
    const VCBatStringHandle     string_handle) {

    //dont bother if the string handle is invalid
    b8 string_valid = vcbat_string_valid(string_handle);
    if (!string_valid) {
        return(NULL);
    }

    //get the string
    VCBatString string = string_manager_ref.string_array[string_handle];

    //if its already null, we're done
    if (!string.string_buffer) {
        return(NULL);
    }

    const char* c_str = string.string_buffer;

    VCBAT_ASSERT(c_str);

    return(c_str);
}