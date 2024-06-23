@echo off

@set cl_preprocessor= /D UNICODE ^
                      /D _UNICODE

@set cl_flags=        /MD               ^
                      /utf-8            ^
                      /Zi               ^
                      /Fe:bin\VCBat.exe ^
                      /Fd:bin\VCBat.pdb ^
                      /Fo:bin\VCBat.obj

@set cl_includes=     /I src\       ^
                      /I src\cl     ^
                      /I src\win32  ^
                      /I src\gui    ^
                      /I src\common ^
                      /I src\memory ^
                      /I vcpkg_installed\x64-windows\include

@set cl_source=       src\vcbat-src.cpp

@set cl_linker=       /link ^
                      /LIBPATH:vcpkg_installed\x64-windows\lib

@set cl_libs=         user32.lib   ^
                      opengl32.lib ^
                      gdi32.lib    ^
                      imgui.lib

call cl.exe           ^
    %cl_preprocessor% ^
    %cl_flags%        ^
    %cl_includes%     ^
    %cl_source%       ^
    %cl_linker%       ^
    %cl_libs%