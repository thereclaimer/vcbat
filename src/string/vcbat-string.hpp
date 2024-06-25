#ifndef VCBAT_STRING_HPP
#define VCBAT_STRING_HPP

#include "vcbat.hpp"
#include "vcbat-memory.hpp"

struct VCBatString {
    VCBatMemoryArenaHandle arena_handle;
    u64                    string_length_bytes;
    memory                 string_data;                 
};

typedef VCBatString* VCBatStringPtr; 
typedef VCBatString& VCBatStringRef; 
typedef handle       VCBatStringHandle;

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

#endif //VCBAT_STRING_HPP