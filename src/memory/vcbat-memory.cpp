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


internal void
vcbat_memory_info(
    VCBatMemoryInfoRef memory_info_ref) {
    
    //get the available arenas
    u64 arenas_available = 0;
    u64 memory_available = vcbat_memory.platform_memory_size_bytes;
    for (
        VCBatMemoryArenaPtr arena = vcbat_memory.arenas_available;
        arena != NULL && arena->next != NULL;
        arena = arena->next) {

        ++arenas_available;
        memory_available -= (sizeof(VCBatMemoryArena) + arena->bytes_used);
    }

    //get the reserved arenas
    u64 arenas_reserved = 0;
    u64 memory_used     = 0;
    for (
        VCBatMemoryArenaPtr arena = vcbat_memory.arenas_reserved;
        arena != NULL && arena->next != NULL;
        arena = arena->next) {

        ++arenas_reserved;
        memory_used += (sizeof(VCBatMemoryArena) + arena->bytes_used);
    }

    //fill out the info
    memory_info_ref.platform_memory           = vcbat_memory.platform_memory_size_bytes;
    memory_info_ref.arenas_total              = vcbat_memory.arenas_count_total;
    memory_info_ref.arenas_available          = arenas_available;
    memory_info_ref.arenas_reserved           = arenas_reserved;
    memory_info_ref.platform_memory_used      = memory_used;
    memory_info_ref.platform_memory_available = memory_available;
}