#ifndef VCBAT_HPP
#define VCBAT_HPP

#include "vcbat-types.hpp"
#include "vcbat-platform-api.hpp"
#include "vcbat-dependencies.hpp"
#include "vcbat-cl-options.hpp"

//-------------------------------------------------
// IMGUI
//-------------------------------------------------

struct VCBatImGui {
    b8 show_demo_window;
    b8 show_cl_options;
};

typedef VCBatImGui& VCBatImGuiRef;

VCBatImGui
vcbat_imgui_create_and_initialize();

void
vcbat_imgui_update(
    VCBatImGuiRef vcbat_imgui_ref);

//-------------------------------------------------
// MEMORY
//-------------------------------------------------

#define VCBAT_MEMORY_KILOBYTES(n) (n * 1024)
#define VCBAT_MEMORY_MEGABYTES(n) (VCBAT_MEMORY_KILOBYTES(n) * 1024)
#define VCBAT_MEMORY_GIGABYTES(n) (VCBAT_MEMORY_MEGABYTES(n) * 1024)

struct  VCBatMemoryArena;
typedef VCBatMemoryArena* VCBatMemoryArenaPtr;
typedef VCBatMemoryArena& VCBatMemoryArenaRef;
typedef void*             VCBatMemoryArenaHandle;

struct VCBatMemoryArena {
    u64                 memory_size_bytes;
    memory              memory;
    VCBatMemoryArenaPtr next;
};


struct  VCBatMemory;
typedef VCBatMemory* VCBatMemoryPtr;
typedef VCBatMemory& VCBatMemoryRef;

struct VCBatMemory {
    u64                 core_memory_size_bytes;
    memory              core_memory;
    VCBatMemoryArenaPtr arenas;
};

VCBatMemory
vcbat_memory_create_and_initialize();

u64
vcbat_memory_arenas_count(
    VCBatMemoryRef memory_ref);

VCBatMemoryArenaHandle
vcbat_memory_arena_push(
    VCBatMemoryRef memory_ref,
    u64            arena_size_bytes);

memory
vcbat_memory_arena_memory_get(
    VCBatMemoryArenaHandle arena_handle,
    u64                    memory_offset,
    u64                    memory_size_bytes);

inline u64
vcbat_memory_arena_size_requirement(
    u64 arena_size_bytes) {

    u64 arena_size_requirement = 
        sizeof(VCBatMemoryArena) + arena_size_bytes;

    return(arena_size_requirement);
}

inline VCBatMemoryArenaPtr 
vcbat_memory_arena_from_existing_memory(
    memory arena_memory_start,
    u64    arena_size_bytes) {

    VCBAT_ASSERT(
        arena_memory_start && 
        arena_size_bytes > 0);

    VCBatMemoryArenaPtr new_arena_ptr = (VCBatMemoryArenaPtr)arena_memory_start;
    new_arena_ptr->memory_size_bytes = arena_size_bytes;
    new_arena_ptr->memory            = arena_memory_start + sizeof(VCBatMemoryArena);
    new_arena_ptr->next              = NULL;

    memset(
        new_arena_ptr->memory,
        0,
        arena_size_bytes);

    return(new_arena_ptr);
}

//-------------------------------------------------
// STRING
//-------------------------------------------------

#define VCBAT_STRING_MEMORY_SIZE_BYTES VCBAT_MEMORY_KILOBYTES(64)
#define VCBAT_STRING_MAX_SIZE_BYTES    256
#define VCBAT_STRING_MAX_COUNT         (VCBAT_STRING_MEMORY_SIZE_BYTES / VCBAT_STRING_MAX_SIZE_BYTES) 
#define VCBAT_STRING_INVALID           -1

typedef s64 VCBatStringHandle;

struct VCBatString {
    u64   string_buffer_length_bytes;
    char* string_buffer;
};

typedef VCBatString* VCBatStringPtr;
typedef VCBatString& VCBatStringRef;

struct VCBatStringAllocator {
    VCBatMemoryArenaHandle arena_handle;
};

typedef VCBatStringAllocator* VCBatStringAllocatorPtr; 
typedef VCBatStringAllocator& VCBatStringAllocatorRef;

struct VCBatStringManager {
    VCBatStringAllocator string_allocator;
    VCBatString          string_array[VCBAT_STRING_MAX_COUNT];
};  

typedef VCBatStringManager* VCBatStringManagerPtr;
typedef VCBatStringManager& VCBatStringManagerRef;

VCBatStringManager
vcbat_string_manager_create_and_initialize(
    VCBatMemoryRef memory_ref);

inline b8
vcbat_string_valid(
    const VCBatStringHandle string_handle) {

    b8 string_valid = 
        string_handle >= 0 ||
        string_handle < VCBAT_STRING_MAX_COUNT;

    return(string_valid);
}

VCBatStringHandle
vcbat_string_new(
          VCBatStringManagerRef string_manager_ref,
    const char*                 string_val);

void
vcbat_string_delete(
          VCBatStringManagerRef string_manager_ref,
    const VCBatStringHandle     string_handle);

u64
vcbat_string_length(
          VCBatStringManagerRef string_manager_ref,
    const VCBatStringHandle     string_handle);

const char*
vcbat_string_c_str(
          VCBatStringManagerRef string_manager_ref,
    const VCBatStringHandle     string_handle);

//-------------------------------------------------
// CORE
//-------------------------------------------------

struct VCBat{
    VCBatImGui         imgui;
    VCBatMemory        memory;
    VCBatStringManager string_manager;
};

typedef VCBat& VCBatRef;

VCBat
vcbat_create_and_initialize(
    VCBatPlatformApi platform_api);

void
vcbat_update(
    VCBatRef vcbat_ref);


#endif //VCBAT_HPP