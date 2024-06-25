#pragma once

#include "vcbat-win32.hpp"
 
internal ImGuiContext*
vcbat_win32_imgui_initialize(
    HWND win32_handle_window) {

    IMGUI_CHECKVERSION();

    ImGuiContext* imgui_context = ImGui::CreateContext();
    VCBAT_ASSERT(imgui_context);

    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();

    b8 impl_init_win32  = ImGui_ImplWin32_InitForOpenGL(win32_handle_window);
    b8 impl_init_opengl = ImGui_ImplOpenGL3_Init();

    VCBAT_ASSERT(
        impl_init_win32 &&
        impl_init_opengl);

    return(imgui_context);
}

void
vcbat_win32_imgui_frame_start() {
    
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}

void
vcbat_win32_imgui_frame_render() {

    ImGui::Render();

    ImDrawData* imgui_draw_data = ImGui::GetDrawData();
    VCBAT_ASSERT(imgui_draw_data);

    ImGui_ImplOpenGL3_RenderDrawData(imgui_draw_data);
}