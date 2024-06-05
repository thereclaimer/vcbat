#ifndef VCBAT_WIN32_HPP
#define VCBAT_WIN32_HPP

#include <Windows.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif  //WIN32_LEAN_AND_MEAN

#include <pugixml/pugixml.hpp>

#include "vcbat.hpp"

#define vcbat_win32_main WINAPI wWinMain

#define VCBAT_WIN32_WINDOW_INITIAL_WIDTH  1024
#define VCBAT_WIN32_WINDOW_INITIAL_HEIGHT 768

//-------------------------------------------------
// WINDOW
//-------------------------------------------------

struct VCBatWin32Window {
    u32  window_width;
    u32  window_height;
    u32  monitor_width;
    u32  monitor_height;
    HWND win32_handle_window;
    HDC  win32_handle_device_context;
};

typedef VCBatWin32Window* VCBatWin32WindowPtr;
typedef VCBatWin32Window& VCBatWin32WindowRef;

b8
vcbat_win32_window_create(
    HINSTANCE           instance);

//-------------------------------------------------
// OPENGL
//-------------------------------------------------

HGLRC
vcbat_win32_opengl_initialize(
    HWND win32_handle_window,
    HDC  win32_handle_device_context);

#endif // VCBAT_WIN32_HPP