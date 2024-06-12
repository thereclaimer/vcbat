#pragma once

#include "vcbat.hpp"

internal VCBatMemory
vcbat_memory_create_and_initialize() {

    VCBatMemory vcbat_memory = {0};

    //allocate the core memory
    u64 core_memory_size_bytes = VCBAT_MEMORY_MEGABYTES(128); 
    memory core_memory = vcbat_platform_api_memory_allocate(core_memory_size_bytes);
    VCBAT_ASSERT(core_memory);

    vcbat_memory.arenas                 = NULL;
    vcbat_memory.core_memory            = core_memory;
    vcbat_memory.core_memory_size_bytes = core_memory_size_bytes;

    return(vcbat_memory);
}

internal u64
vcbat_memory_arenas_count(
    VCBatMemoryRef memory_ref) {

    u64 count_arenas = 0;

    for (
        VCBatMemoryArenaPtr arena_ptr = memory_ref.arenas;
        arena_ptr != NULL && arena_ptr->next != NULL;
        arena_ptr = arena_ptr->next) {

        ++count_arenas;
    }

    return(count_arenas);
}

internal VCBatMemoryArenaHandle
vcbat_memory_arena_push(
    VCBatMemoryRef memory_ref,
    u64            arena_size_bytes) {

    //make sure the arena isn't bigger than our max memory
    u64 arena_size_requirement = vcbat_memory_arena_size_requirement(arena_size_bytes);
    if (
        arena_size_requirement > memory_ref.core_memory_size_bytes ||
        arena_size_bytes == 0) {
        return(NULL);
    }

    VCBatMemoryArenaPtr new_arena_ptr = NULL;

    if (!memory_ref.arenas) {

        //our first arena, set it and we're done
        new_arena_ptr = 
            vcbat_memory_arena_from_existing_memory(
                memory_ref.core_memory,
                arena_size_bytes);

        VCBAT_ASSERT(new_arena_ptr);

        memory_ref.arenas = new_arena_ptr;

        return(new_arena_ptr);
    }

    //get to the end of the list, checking size as we go
    VCBatMemoryArenaPtr tail_arena_ptr        = NULL;
    u64                 memory_occupied_bytes = 0;

    for (
        VCBatMemoryArenaPtr current_arena_ptr = memory_ref.arenas;
        current_arena_ptr->next != NULL;
        current_arena_ptr = current_arena_ptr->next) {

        tail_arena_ptr = current_arena_ptr;
        memory_occupied_bytes += 
            vcbat_memory_arena_size_requirement(
                current_arena_ptr->memory_size_bytes);
    }

    //we should ALWAYS have a tail pointer here
    VCBAT_ASSERT(tail_arena_ptr);
    u64 new_memory_occupied_bytes = arena_size_requirement + memory_occupied_bytes;

    if (new_memory_occupied_bytes > memory_ref.core_memory_size_bytes) {
        return(NULL);
    }

    memory new_arena_memory_start = tail_arena_ptr->memory + tail_arena_ptr->memory_size_bytes;  

    new_arena_ptr = 
        vcbat_memory_arena_from_existing_memory(
            new_arena_memory_start,
            arena_size_bytes);

    VCBAT_ASSERT(new_arena_ptr);

    tail_arena_ptr->next = new_arena_ptr;

    return(new_arena_ptr);
}

internal memory
vcbat_memory_arena_memory_get(
    VCBatMemoryArenaHandle arena_handle,
    u64                    memory_offset,
    u64                    memory_size_bytes) {

    VCBatMemoryArenaPtr arena_ptr = (VCBatMemoryArenaPtr)arena_handle;

    if (
        arena_ptr == NULL ||
        memory_size_bytes) {
        
        return(NULL);
    }

    VCBatMemoryArena arena            = *arena_ptr;
    memory           requested_memory = NULL;

    u64 memory_ending_offset = memory_size_bytes + memory_offset;

    if (
        memory_size_bytes    > arena.memory_size_bytes ||
        memory_offset        > arena.memory_size_bytes ||
        memory_ending_offset > arena.memory_size_bytes) {

        return(NULL);
    }

    requested_memory = arena.memory + memory_offset;

    VCBAT_ASSERT(requested_memory);

    return(requested_memory);
}