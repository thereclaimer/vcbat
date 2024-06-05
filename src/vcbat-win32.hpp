#ifndef VCBAT_WIN32_HPP
#define VCBAT_WIN32_HPP

#include <Windows.h>
#include <GL/GL.h>
#include <tchar.h>

#include "vcbat.hpp"
#include "vcbat-imgui.hpp"

#define vcbat_win32_main WINAPI wWinMain

#define VCBAT_WIN32_WINDOW_INITIAL_WIDTH  1024
#define VCBAT_WIN32_WINDOW_INITIAL_HEIGHT 768

//-------------------------------------------------
// WINDOW
//-------------------------------------------------
 
struct VCBatWin32Window {
    u32           window_width;
    u32           window_height;
    u32           monitor_width;
    u32           monitor_height;
    MSG           message;
    HWND          handle_window;
    HDC           handle_device_context;
    HGLRC         handle_opengl;
};

typedef VCBatWin32Window* VCBatWin32WindowPtr;
typedef VCBatWin32Window& VCBatWin32WindowRef;

VCBatWin32Window
vcbat_win32_window_create(
    HINSTANCE instance,
    s32       cmd_show);

b8
vcbat_win32_window_update_and_render(
    VCBatWin32WindowPtr window);

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

#endif // VCBAT_WIN32_HPP