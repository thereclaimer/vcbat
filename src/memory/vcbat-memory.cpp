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

internal VCBatMemoryArenaHandle
vcbat_memory_arena_reserve() {

    if (!vcbat_memory.arenas_available) {
        return(NULL);
    }

    //get the first of the available arenas and set the next one as the new first available
    VCBatMemoryArenaPtr reserved_arena = vcbat_memory.arenas_available;     
    vcbat_memory.arenas_available      = reserved_arena->next;

    //put this new arena at the front of the reserved arenas
    reserved_arena->previous     = NULL;
    reserved_arena->next         = vcbat_memory.arenas_reserved;
    vcbat_memory.arenas_reserved = reserved_arena;

    //reset the reserved arena
    reserved_arena->bytes_used = 0;
    memset(
        reserved_arena->memory,
        0,
        VCBAT_MEMORY_ARENA_SIZE_BYTES - sizeof(VCBatMemoryArena));

    return(reserved_arena);      
}

internal void
vcbat_memory_arena_release(
    VCBatMemoryArenaPtr arena) {

    VCBatMemoryArenaPtr arena_ptr = (VCBatMemoryArenaPtr)arena; 

    if (!arena_ptr) {
        return;
    }

    VCBatMemoryArenaPtr arena_previous = arena_ptr->previous;
    VCBatMemoryArenaPtr arena_next     = arena_ptr->next;

    if (arena_previous) {
        arena_previous->next = arena_next;
    }

    if (arena_next) {
        arena_next->previous = arena_previous;
    }

    arena_ptr->previous           = NULL;
    arena_ptr->next               = vcbat_memory.arenas_available;
    vcbat_memory.arenas_available = arena_ptr;
}

internal memory
vcbat_memory_arena_bytes_push(
    VCBatMemoryArenaHandle arena,
    u64                    size) {

    VCBatMemoryArenaPtr arena_ptr = (VCBatMemoryArenaPtr)arena; 

    if (!arena_ptr) {
        return(NULL);
    }

    u64 max_space = VCBAT_MEMORY_ARENA_SIZE_BYTES - sizeof(VCBatMemoryArena);
    u64 new_size  = arena_ptr->bytes_used + size;

    if (new_size >= max_space) {
        return(NULL);
    }

    VCBAT_ASSERT(arena_ptr->memory);

    memory allocation     = &arena_ptr->memory[arena_ptr->bytes_used];
    arena_ptr->bytes_used = new_size;

    return(allocation);
}

internal void
vcbat_memory_arena_bytes_pop(
    VCBatMemoryArenaPtr arena,
    u64                 size) {

    VCBatMemoryArenaPtr arena_ptr = (VCBatMemoryArenaPtr)arena; 

    if (!arena_ptr) {
        return;
    }

    VCBAT_ASSERT(arena_ptr->memory);

    if (arena_ptr->bytes_used < size) {
        arena_ptr->bytes_used = 0;
        return;
    }

    arena_ptr->bytes_used -= size;
}

internal void    
vcbat_memory_arena_clear(
    VCBatMemoryArenaPtr arena) {
    
    VCBatMemoryArenaPtr arena_ptr = (VCBatMemoryArenaPtr)arena; 

    if (!arena_ptr) {
        return;
    }

    VCBAT_ASSERT(arena_ptr->memory);

    memset(
        arena_ptr->memory,
        0,
        VCBAT_MEMORY_ARENA_SIZE_BYTES - sizeof(VCBatMemoryArena));

    arena_ptr->bytes_used = 0;
}

internal u64
vcbat_memory_arena_space_available(
    VCBatMemoryArenaPtr arena) {

    VCBatMemoryArenaPtr arena_ptr = (VCBatMemoryArenaPtr)arena; 

    if (!arena_ptr) {
        return(0);
    }    

    u64 max_space       = VCBAT_MEMORY_ARENA_SIZE_BYTES - sizeof(VCBatMemoryArena);
    u64 space_available = max_space - arena_ptr->bytes_used;     

    return(space_available);
}

internal u64
vcbat_memory_arena_space_used(
    VCBatMemoryArenaPtr arena) {

    VCBatMemoryArenaPtr arena_ptr = (VCBatMemoryArenaPtr)arena; 

    if (!arena_ptr) {
        return(0);
    }

    u64 space_used = sizeof(VCBatMemoryArena) + arena_ptr->bytes_used;

    return(space_used);
}