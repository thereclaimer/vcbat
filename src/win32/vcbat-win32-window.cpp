#pragma once

#include "vcbat-win32.hpp"

global VCBatWin32Window vcbat_win32_window;

internal void
vcbat_win32_window_process_events() {

    while (PeekMessage(&vcbat_win32_window.message, 0,0,0, PM_REMOVE)) {
        TranslateMessage(&vcbat_win32_window.message);
        DispatchMessage(&vcbat_win32_window.message);
    }
}

internal void
vcbat_win32_window_update() {

    //process window events
    vcbat_win32_window_process_events();

    //start new imgui frame
    vcbat_win32_imgui_frame_start();
}

internal void
vcbat_win32_window_render() {

    //render opengl
    vcbat_win32_opengl_render(
        vcbat_win32_window.window_width,
        vcbat_win32_window.window_height);

    //render the imgui frame
    vcbat_win32_imgui_frame_render();

    //swap buffers
    SwapBuffers(
        vcbat_win32_window.handle_device_context);
}

internal LRESULT
vcbat_win32_window_on_wm_size(
    WPARAM w_param,
    LPARAM l_param) {

    vcbat_win32_window.window_width  = LOWORD(l_param);
    vcbat_win32_window.window_height = HIWORD(w_param);

    return(0);
}

internal LRESULT
vcbat_win32_window_on_wm_quit(
    WPARAM w_param,
    LPARAM l_param) {

    vcbat_win32_window.quit = true;
    
    return(0);
}

internal LRESULT CALLBACK 
vcbat_win32_window_callback(
    HWND   window_handle,
    UINT   message,
    WPARAM w_param,
    LPARAM l_param) {
    
    LRESULT imgui_result = 
        vcbat_win32_imgui_window_callback(
            window_handle,
            message,
            w_param,
            l_param);

    if (imgui_result) {
        return(true);
    }

    func_vcbat_win32_on_wm_message wm_message_handler;

    switch (message) {

        case WM_SIZE: {
            wm_message_handler = vcbat_win32_window_on_wm_size;
        } break;

        case WM_CLOSE:
        case WM_QUIT:
        case WM_DESTROY: {
            wm_message_handler = vcbat_win32_window_on_wm_quit;
        } break;

        default: {

            LRESULT def_result = 
                DefWindowProc(
                    window_handle,
                    message,
                    w_param,
                    l_param);

            return(def_result);

        } break;
    }

    VCBAT_ASSERT(wm_message_handler);

    LRESULT result = 
        wm_message_handler(
            w_param,
            l_param);

    return(result);
}

internal VCBatWin32WindowPtr
vcbat_win32_window_create(
    HINSTANCE instance,
    s32       cmd_show) {

    vcbat_win32_window = {0};

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

    //initialize ImGui
    ImGuiContext* imgui_context = 
        vcbat_win32_imgui_initialize(window_handle);
    VCBAT_ASSERT(imgui_context);

    ShowWindow(
        window_handle,
        cmd_show);

    vcbat_win32_window.window_width          = VCBAT_WIN32_WINDOW_INITIAL_WIDTH;
    vcbat_win32_window.window_height         = VCBAT_WIN32_WINDOW_INITIAL_HEIGHT;
    vcbat_win32_window.handle_window         = window_handle;
    vcbat_win32_window.handle_device_context = device_context_handle;
    vcbat_win32_window.handle_opengl         = opengl_handle;
    vcbat_win32_window.quit                  = false;

    return(&vcbat_win32_window);
}


internal const VCBatWin32WindowRef 
vcbat_win32_window_get() {
    return(vcbat_win32_window);
}