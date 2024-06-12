#ifndef VCBAT_TYPES_HPP
#define VCBAT_TYPES_HPP

#include <cstdint>

#define internal static
#define local    static
#define global   static
#define external extern "C" __declspec(dllexport)
#define api      extern "C" __declspec(dllimport)
#define null     0

#define VCBAT_ASSERT(condition) if(!(condition)) *((int*)(NULL)) = 1
#define VCBAT_NOP()   VCBAT_ASSERT(true)
#define VCBAT_PANIC() VCBAT_ASSERT(false)

#ifdef __GNUC__
#define PACK( __Declaration__ ) __Declaration__ __attribute__((__packed__))
#endif

#ifdef _MSC_VER
#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop))
#endif

typedef int8_t   s8;
typedef int16_t  s16;
typedef int32_t  s32;
typedef int64_t  s64;

typedef s8*      s8p;
typedef s16*     s16p;
typedef s32*     s32p;
typedef s64*     s64p;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef  u8*     u8p;
typedef  u16*    u16p;
typedef  u32*    u32p;
typedef  u64*    u64p;

typedef float    f32;
typedef double   f64;

typedef f32*     f32p;
typedef f64*     f64p;

typedef bool     b8;
typedef b8*      b8p;

typedef void*    handle;

typedef u8       byte;
typedef byte*    memory;


#endif //VCBAT_TYPES_HPP