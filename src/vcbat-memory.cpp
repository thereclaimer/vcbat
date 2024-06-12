#pragma once

#include "vcbat.hpp"

VCBatMemory
vcbat_memory_create_and_initialize() {

    VCBatMemory vcbat_memory = {0};

    //allocate the core memory
    u64 core_memory_size_bytes = VCBAT_MEMORY_MEGABYTES(1); 
    memory core_memory = vcbat_platform_api_memory_allocate(core_memory_size_bytes);
    VCBAT_ASSERT(core_memory);

    vcbat_memory.arenas                 = NULL;
    vcbat_memory.core_memory            = core_memory;
    vcbat_memory.core_memory_size_bytes = core_memory_size_bytes;

    return(vcbat_memory);
}