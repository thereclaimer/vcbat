@echo off

@set cl_preprocessor= 
@set cl_flags=        /Fo:bin/BinaryToCompressedArray.obj
@set cl_includes=     
@set cl_src=          src/tools/binary-to-compressed-c.cpp
@set cl_link=         /link /out:bin/BinaryToCompressedArray.exe
@set cl_libs=         

call cl.exe       ^
%cl_preprocessor% ^
%cl_flags%        ^
%cl_includes%     ^
%cl_src%          ^
%cl_link%         ^
%cl_libs% 