#ifndef VCBAT_WIN32_HPP
#define VCBAT_WIN32_HPP

#include <Windows.h>
#include <GL/GL.h>
#include <tchar.h>
#include <shlobj_core.h> 

#include "vcbat.hpp"
#include "vcbat-core.hpp"

#define vcbat_win32_main WINAPI wWinMain

#define VCBAT_WIN32_WINDOW_INITIAL_WIDTH  1920
#define VCBAT_WIN32_WINDOW_INITIAL_HEIGHT 1080

//-------------------------------------------------
// WINDOW
//-------------------------------------------------
 
struct VCBatWin32Window {
    u32           window_width;
    u32           window_height;
    u32           monitor_width;
    u32           monitor_height;
    MSG           message;
    WPARAM        message_param_w;
    LPARAM        message_param_l;
    HWND          handle_window;
    HDC           handle_device_context;
    HGLRC         handle_opengl;
    ImGuiContext* imgui_context;
    b8            quit;
};

typedef VCBatWin32Window* VCBatWin32WindowPtr;
typedef VCBatWin32Window& VCBatWin32WindowRef;

VCBatWin32WindowPtr
vcbat_win32_window_create(
    HINSTANCE instance,
    s32       cmd_show);

void 
vcbat_win32_window_update();

void
vcbat_win32_window_render();

const VCBatWin32WindowRef 
vcbat_win32_window_get();

typedef LRESULT
(*func_vcbat_win32_on_wm_message)(
    WPARAM w_param,
    LPARAM l_param);

//-------------------------------------------------
// PLATFORM API
//-------------------------------------------------

VCBatPlatformApi
vcbat_win32_platform_api_create_and_init();

memory
vcbat_win32_platform_api_allocate_memory(
    u64 size);

void
vcbat_win32_platform_api_free_memory(
    handle memory,
    u64 size);

u64
vcbat_win32_platform_api_file_size_bytes(
    HANDLE file_handle,
    b8     terminate);

HANDLE
vcbat_win32_platform_api_file_open(
    const wchar_t* file_path,
          b8       create_new);

void
vcbat_win32_platform_api_file_close(
    HANDLE file_handle);

void
vcbat_win32_platform_api_file_read(
    HANDLE file_handle,
    u64    offset,
    u64    allocated_buffer_size,
    memory allocated_buffer,
    b8     terminate);

void
vcbat_win32_platform_api_file_write(
    handle file_handle,
    u64    allocated_buffer_size,
    u64    offset,
    memory allocated_buffer);

void
vcbat_win32_platform_api_file_dialog(
    VCBatPlatformFileDialogOptions& options);

//-------------------------------------------------
// OPENGL
//-------------------------------------------------
 
HGLRC
vcbat_win32_opengl_initialize(
    HDC win32_handle_device_context);

void
vcbat_win32_opengl_render(
    u32 window_width,
    u32 window_height);

//-------------------------------------------------
// IMGUI
//-------------------------------------------------
 
extern IMGUI_IMPL_API LRESULT 
ImGui_ImplWin32_WndProcHandler(
    HWND   hWnd, 
    UINT   msg, 
    WPARAM wParam, 
    LPARAM lParam);

#define vcbat_win32_imgui_window_callback ImGui_ImplWin32_WndProcHandler

ImGuiContext*
vcbat_win32_imgui_initialize(
    HWND win32_handle_window);

void
vcbat_win32_imgui_frame_start();

void
vcbat_win32_imgui_frame_render();

#endif // VCBAT_WIN32_HPP