#pragma once

#include "vcbat-memory.hpp"

global VCBatMemory vcbat_memory;

VCBatMemoryPtr
vcbat_memory_create_and_initialize() {

    vcbat_memory = {0};

    vcbat_memory.platform_memory            = vcbat_platform_api_memory_allocate(VCBAT_MEMORY_SIZE);
    vcbat_memory.platform_memory_size_bytes = VCBAT_MEMORY_SIZE;
    vcbat_memory.arenas_reserved            = NULL;
    vcbat_memory.arenas_available           = (VCBatMemoryArenaPtr)vcbat_memory.platform_memory;
    vcbat_memory.arenas_count_total         = VCBAT_MEMORY_SIZE / VCBAT_MEMORY_ARENA_SIZE_BYTES;

    VCBatMemoryArenaPtr arena_previous = vcbat_memory.arenas_available;
    arena_previous->previous   = NULL;
    arena_previous->bytes_used = 0;
    arena_previous->next       = NULL;
    arena_previous->memory     = vcbat_memory.platform_memory + sizeof(VCBatMemoryArena);

    VCBatMemoryArenaPtr arena_current  = NULL;
    memory              arena_offset   = vcbat_memory.platform_memory += VCBAT_MEMORY_ARENA_SIZE_BYTES;

    for (
        u64 arena_index = 1;
        arena_index < vcbat_memory.arenas_count_total - 1;
        ++arena_index) {

        //get the offset of the current arena
        arena_offset  += VCBAT_MEMORY_ARENA_SIZE_BYTES;
        arena_current  = (VCBatMemoryArenaPtr)arena_offset;

        //initialize the current arena
        arena_current->previous   = arena_previous;
        arena_current->bytes_used = 0;
        arena_current->next       = NULL;
        arena_current->memory     = arena_offset + sizeof(VCBatMemoryArena);

        //update the previous arena
        arena_previous->next = arena_current;
        arena_previous       = arena_current;
    }

    return(&vcbat_memory);
}