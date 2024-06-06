#pragma once

#include "vcbat-win32.hpp"

#define WM_VCBAT_WINDOW (WM_USER+1)

internal b8
vcbat_win32_window_process_events(
    VCBatWin32WindowPtr window) {

    PostMessage(
        window->handle_window,
        WM_VCBAT_WINDOW,
        0,
        (LPARAM)window);

    while (PeekMessage(&window->message, 0,0,0, PM_REMOVE)) {

        switch(window->message.message) {

            case WM_CLOSE:
            case WM_QUIT:
            case WM_DESTROY: {
                return(false);
            } break;

            default: {
                TranslateMessage(&window->message);
                DispatchMessage(&window->message);
            } break;
        }
    }

    return(true);
}

internal b8
vcbat_win32_window_update_and_render(
    VCBatWin32WindowPtr window) {
    
    VCBAT_ASSERT(window);

    //process window events
    b8 result = vcbat_win32_window_process_events(window);
    if (!result) {
        return(false);
    }

    //render opengl
    vcbat_win32_opengl_render(
        window->window_width,
        window->window_height);

    //swap buffers
    SwapBuffers(window->handle_device_context);

    return(true);
}

internal bool
vcbat_win32_window_on_wm_size(
    VCBatWin32WindowPtr win32_window_ptr) {

    if (!win32_window_ptr) {
        return(true);
    }

    win32_window_ptr->window_width  = LOWORD(win32_window_ptr->message_param_l);
    win32_window_ptr->window_height = HIWORD(win32_window_ptr->message_param_l);

    return(true);
}

internal bool
vcbat_win32_window_on_wm_quit(
    VCBatWin32WindowPtr win32_window_ptr) {

    if (!win32_window_ptr) {
        return(true);
    }

    win32_window_ptr->quit = true; 

    return(true);
}

internal LRESULT CALLBACK 
vcbat_win32_window_callback(
    HWND   window_handle,
    UINT   message,
    WPARAM w_param,
    LPARAM l_param) {
    
    local VCBatWin32WindowPtr win32_window_ptr = NULL;

    if (win32_window_ptr) {
        win32_window_ptr->message_param_w = w_param;
        win32_window_ptr->message_param_l = l_param;
    }

    b8 result = true;

    switch (message) {

        case WM_VCBAT_WINDOW: {
            win32_window_ptr = (VCBatWin32WindowPtr)l_param;
        } break;

        case WM_SIZE: {
            result = vcbat_win32_window_on_wm_size(win32_window_ptr);
        } break;

        case WM_CLOSE:
        case WM_QUIT:
        case WM_DESTROY: {
            result = vcbat_win32_window_on_wm_quit(win32_window_ptr);
        } break;

        default: {
            result = 
                DefWindowProc(
                    window_handle,
                    message,
                    w_param,
                    l_param);
        } break;
    }

    return(result);
}

internal VCBatWin32Window
vcbat_win32_window_create(
    HINSTANCE instance,
    s32       cmd_show) {

    VCBatWin32Window window = {0};

    //define window class
    WNDCLASS window_class = {0};
    window_class.lpfnWndProc   = (WNDPROC)vcbat_win32_window_callback;
    window_class.hInstance     = instance;
    window_class.lpszClassName = L"VCBatWindowClass";
    window_class.style         = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;

    b8 window_class_registered = RegisterClass(&window_class);
    VCBAT_ASSERT(window_class_registered);

    //create the window handle
    HWND window_handle = 
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
    VCBAT_ASSERT(window_handle);

    //get the device context
    HDC device_context_handle = GetDC(window_handle);
    VCBAT_ASSERT(device_context_handle);

    //initialize opengl
    HGLRC opengl_handle =
        vcbat_win32_opengl_initialize(
            device_context_handle);
    VCBAT_ASSERT(opengl_handle);

    ShowWindow(
        window_handle,
        cmd_show);

    window.window_width          = VCBAT_WIN32_WINDOW_INITIAL_WIDTH;
    window.window_height         = VCBAT_WIN32_WINDOW_INITIAL_HEIGHT;
    window.handle_window         = window_handle;
    window.handle_device_context = device_context_handle;
    window.handle_opengl         = opengl_handle;
    window.quit                  = false;

    return(window);
}