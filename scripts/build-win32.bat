@echo off

@set cl_preprocessor= /D UNICODE /D _UNICODE
@set cl_flags=        /Zi /Fe:bin\VCBat.exe /Fd:bin\VCBat.pdb /Fo:bin\VCBat.obj
@set cl_includes=     /I .\src\
@set cl_source=       src\vcbat-win32.cpp
@set cl_linker=       /link
@set cl_libs=         user32.lib

call cl.exe %cl_preprocessor% %cl_flags% %cl_includes% %cl_source% %cl_linker% %cl_libs%