#pragma once

#include "vcbat.hpp"
#include "vcbat-win32.hpp"

internal HGLRC
vcbat_win32_opengl_initialize(
    HWND win32_handle_window,
    HDC  win32_handle_device_context) {

    //describe our desired pixel format
    PIXELFORMATDESCRIPTOR desired_pixel_format = { 0 };
    desired_pixel_format.nSize      = sizeof(desired_pixel_format);
    desired_pixel_format.nVersion   = 1;
    desired_pixel_format.dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    desired_pixel_format.iPixelType = PFD_TYPE_RGBA;
    desired_pixel_format.cColorBits = 32;

    //query for a pixel format closest to our desired one
    s32 chosen_pixel_format = 
        ChoosePixelFormat(
            win32_handle_device_context,
            &desired_pixel_format);

    VCBAT_ASSERT(chosen_pixel_format);

    //set the pixel format
    b8 pixel_format_set = 
        SetPixelFormat(
            win32_handle_device_context,
            chosen_pixel_format,
            &desired_pixel_format);

    VCBAT_ASSERT(pixel_format_set);

    //create the opengl context
    HGLRC win32_handle_opengl = wglCreateContext(win32_handle_device_context);
    VCBAT_ASSERT(win32_handle_opengl);

    return(win32_handle_opengl);
}