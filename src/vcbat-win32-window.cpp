#pragma once

#include "vcbat-win32.hpp"

internal b8
vcbat_win32_window_update_and_render(
    VCBatWin32WindowRef window) {
    
    while (PeekMessage(&window.message, 0,0,0, PM_REMOVE)) {
        TranslateMessage(&window.message);
        DispatchMessage(&window.message);
    }

    return(true);
}

internal LRESULT CALLBACK 
vcbat_win32_window_callback(
    HWND   hwnd,
    UINT   uMsg,
    WPARAM wParam,
    LPARAM lParam) {
    
    LRESULT def_window_proc_result = 
        DefWindowProc(
            hwnd,
            uMsg,
            wParam,
            lParam);

    return(def_window_proc_result);
}

internal VCBatWin32Window
vcbat_win32_window_create(
    HINSTANCE instance,
    s32       cmd_show) {

    VCBatWin32Window window = {0};

    WNDCLASS window_class = {0};
    window_class.lpfnWndProc   = (WNDPROC)vcbat_win32_window_callback;
    window_class.hInstance     = instance;
    window_class.lpszClassName = L"VCBatWindowClass";
    window_class.style         = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;

    RegisterClass(&window_class);

    HWND window_handle = 
        CreateWindowEx(
            0,
            window_class.lpszClassName,
            L"VCBat", 
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
            NULL,
            NULL,
            instance,
            NULL);

    ShowWindow(
        window_handle,
        cmd_show);

    window.handle_window = window_handle;

    return(window);
}