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

//-------------------------------------------------
// ARENA
//-------------------------------------------------

struct VCBatMemoryArena {
    u64                 bytes_used;
    memory              memory;
    VCBatMemoryArenaPtr next;
    VCBatMemoryArenaPtr previous;
};

VCBatMemoryArena
vcbat_memory_arena_reserve();

void
vcbat_memory_arena_release();

memory
vcbat_memory_arena_bytes_push(
    u64 size);

void
vcbat_memory_arena_bytes_pop(
    u64 size);

void    
vcbat_memory_arena_clear();

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

VCBatMemoryPtr
vcbat_memory_create_and_initialize();

#endif //VCBAT_MEMORY_HPP