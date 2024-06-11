#ifndef VCBAT_HPP
#define VCBAT_HPP

#include "vcbat-types.hpp"
#include "vcbat-platform-api.hpp"
#include "vcbat-dependencies.hpp"

//-------------------------------------------------
// IMGUI
//-------------------------------------------------

struct VCBatImGui {
    b8 show_demo_window;
};

typedef VCBatImGui& VCBatImGuiRef;

VCBatImGui
vcbat_imgui_create_and_initialize();

void
vcbat_imgui_update(
    VCBatImGuiRef vcbat_imgui_ref);


//-------------------------------------------------
// CORE
//-------------------------------------------------

struct VCBat{
    VCBatImGui imgui;
};

typedef VCBat& VCBatRef;

VCBat
vcbat_create_and_initialize(
    VCBatPlatformApi platform_api);

void
vcbat_update(
    VCBatRef vcbat_ref);



//-------------------------------------------------
// MEMORY
//-------------------------------------------------

#define VCBAT_MEMORY_KILOBYTES(n) (n * 1024)
#define VCBAT_MEMORY_MEGABYTES(n) (VCBAT_MEMORY_KILOBYTES(n) * 1024)
#define VCBAT_MEMORY_GIGABYTES(n) (VCBAT_MEMORY_MEGABYTES(n) * 1024)

struct VCBatMemoryArena {
    u64               arena_memory_size_bytes;
    memory            arena_memory;
    VCBatMemoryArena* next;
};


struct VCBatMemory {
    u64    core_memory_size_bytes;
    memory core_memory;
    VCBatMemoryArena arenas;
};

typedef VCBatMemory* VCBatMemoryPtr;
typedef VCBatMemory& VCBatMemoryRef;

VCBatMemory
vcbat_memory_create_and_init();


#endif //VCBAT_HPP