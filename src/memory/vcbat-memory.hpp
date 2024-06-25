#ifndef VCBAT_MEMORY_HPP
#define VCBAT_MEMORY_HPP

#include "vcbat.hpp"

//-------------------------------------------------
// TYPES
//-------------------------------------------------

//sizes
#define VCBAT_MEMORY_KILOBYTES(n) (n * 1024)
#define VCBAT_MEMORY_MEGABYTES(n) (VCBAT_MEMORY_KILOBYTES(n) * 1024)
#define VCBAT_MEMORY_GIGABYTES(n) (VCBAT_MEMORY_MEGABYTES(n) * 1024)


//memory
struct  VCBatMemory;
typedef VCBatMemory* VCBatMemoryPtr;
typedef VCBatMemory& VCBatMemoryRef;

//arena

#define VCBAT_MEMORY_ARENA_SIZE_BYTES VCBAT_MEMORY_KILOBYTES(8)

struct  VCBatMemoryArena;
typedef VCBatMemoryArena* VCBatMemoryArenaPtr;
typedef VCBatMemoryArena& VCBatMemoryArenaRef;
typedef handle            VCBatMemoryArenaHandle;

//-------------------------------------------------
// ARENA
//-------------------------------------------------

struct VCBatMemoryArena {
    u64                 bytes_used;
    memory              memory;
    VCBatMemoryArenaPtr next;
    VCBatMemoryArenaPtr previous;
};

VCBatMemoryArenaHandle
vcbat_memory_arena_reserve();

void
vcbat_memory_arena_release(
    VCBatMemoryArenaHandle arena);

memory
vcbat_memory_arena_bytes_push(
    VCBatMemoryArenaHandle arena,
    u64                    size);

void
vcbat_memory_arena_bytes_pop(
    VCBatMemoryArenaHandle arena,
    u64                    size);

void    
vcbat_memory_arena_clear(
    VCBatMemoryArenaHandle arena);

u64
vcbat_memory_arena_space_available(
    VCBatMemoryArenaHandle arena);

u64
vcbat_memory_arena_space_used(
    VCBatMemoryArenaHandle arena);
    

//-------------------------------------------------
// MEMORY
//-------------------------------------------------

#define VCBAT_MEMORY_SIZE VCBAT_MEMORY_MEGABYTES(128)

struct VCBatMemory {
    u64                 platform_memory_size_bytes;
    memory              platform_memory;
    u64                 arenas_count_total;
    VCBatMemoryArenaPtr arenas_reserved;
    VCBatMemoryArenaPtr arenas_available;
};

struct VCBatMemoryInfo {
    u64 arenas_total;
    u64 arenas_reserved;
    u64 arenas_available;
    u64 platform_memory;
    u64 platform_memory_available;
    u64 platform_memory_used;
};

typedef VCBatMemoryInfo* VCBatMemoryInfoPtr;
typedef VCBatMemoryInfo& VCBatMemoryInfoRef;

VCBatMemoryPtr
vcbat_memory_create_and_initialize();

void
vcbat_memory_info(
    VCBatMemoryInfoRef memory_info_ref);


#endif //VCBAT_MEMORY_HPP