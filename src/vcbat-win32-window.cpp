#pragma once

#include "vcbat.hpp"
#include "vcbat-win32.hpp"

global VCBatWin32Window win32_window;

LRESULT WINAPI 
vcbat_win32_window_callback(
    HWND   hWnd,
    UINT   msg,
    WPARAM wParam,
    LPARAM lParam) {
    
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
        case WM_SIZE: {

            if (wParam != SIZE_MINIMIZED) {
                g_Width =  LOWORD(lParam);
                g_Height = HIWORD(lParam);
            }

        } break;
            
            return 0;
        case WM_SYSCOMMAND:
            if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
                return 0;
            break;
        case WM_DESTROY:
            ::PostQuitMessage(0);
            return 0;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}

internal void
vcbat_win32_window_create(
    HINSTANCE           instance) {

    win32_window = {0};

    // Register the main window class.
    WNDCLASS window_class      = {0};
    window_class.style         = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    window_class.lpfnWndProc   = (WNDPROC)vcbat_win32_window_callback;
    window_class.hInstance     = instance;
    window_class.lpszClassName = "VCBatWindowClass";

    VCBAT_ASSERT(RegisterClass(&window_class));

    //create the window
    win32_window.win32_handle_window = 
        CreateWindowEx(
            0,
            window_class.lpszClassName,
            L"VCBat",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            VCBAT_WIN32_WINDOW_INITIAL_WIDTH,
            VCBAT_WIN32_WINDOW_INITIAL_HEIGHT,
            NULL,
            NULL,
            instance,
            NULL);

    VCBAT_ASSERT(win32_window.win32_handle_window);

    //get the device context
    win32_window.win32_handle_device_context = GetDC(win32_window.win32_handle_window);
    VCBAT_ASSERT(win32_window.win32_handle_device_context);

    //initialize opengl


    return(true);
}