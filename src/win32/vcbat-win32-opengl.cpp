#pragma once

#include "vcbat-win32.hpp"

internal HGLRC
vcbat_win32_opengl_initialize(
    HDC  win32_handle_device_context) {

    //set our preferred format descriptor
    PIXELFORMATDESCRIPTOR preferred_format_descriptor = {0};
    preferred_format_descriptor.nSize      = sizeof(preferred_format_descriptor);
    preferred_format_descriptor.nVersion   = 1;
    preferred_format_descriptor.dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    preferred_format_descriptor.iPixelType = PFD_TYPE_RGBA;
    preferred_format_descriptor.cColorBits = 32;

    //query for the closest format descriptor
    const s32 chosen_format_descriptor = 
        ChoosePixelFormat(
            win32_handle_device_context,
            &preferred_format_descriptor);

    VCBAT_ASSERT(chosen_format_descriptor);

    //set the chosen pixel format
    b8 pixel_format_is_set = 
        SetPixelFormat(
            win32_handle_device_context,
            chosen_format_descriptor,
            &preferred_format_descriptor);
    VCBAT_ASSERT(pixel_format_is_set);

    //create the opengl context
    HGLRC win32_handle_opengl = wglCreateContext(win32_handle_device_context);
    VCBAT_ASSERT(win32_handle_opengl);

    //make the new opengl context current
    b8 context_is_current = 
        wglMakeCurrent(
            win32_handle_device_context,
            win32_handle_opengl);
    VCBAT_ASSERT(context_is_current);

    //set the clear color
    glClearColor(
        0.1569f, 
        0.1569f,
        0.1569f,
        1.0000f);

    return(win32_handle_opengl);
}

internal void
vcbat_win32_opengl_render(
    u32 window_width,
    u32 window_height) {

    glViewport(
        0,
        0,
        window_width,
        window_height);

    glClear(GL_COLOR_BUFFER_BIT);
}