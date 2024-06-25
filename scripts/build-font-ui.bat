:: binary_to_compressed_c.exe [-base85] [-nocompress] [-nostatic] <inputfile> <symbolname>

@echo off

@set tool_path=       bin\BinaryToCompressedArray.exe

::arguments
@set arg_base85=      -base85
@set arg_nocompress=
@set arg_nostatic=
@set arg_input=       resources\\segoe-ui.ttf
@set arg_symbol=      vcbat_ui_font

::header file
@set header_file_path= src\\common\\vcbat-font-ui.hpp 
@set header_macro=VCBAT_FONT_UI_HPP     

@set build_font= %tool_path%      ^
                 %arg_base85%     ^
                 %arg_nocompress% ^
                 %arg_nostatic%   ^
                 %arg_input%      ^
                 %arg_symbol%


::delete existing header
del %header_file_path%

::write header
call echo #ifndef %header_macro%      >> %header_file_path%
call echo #define %header_macro%      >> %header_file_path%
call echo:                            >> %header_file_path%
call %build_font%                     >> %header_file_path%
call echo:                            >> %header_file_path%
call echo #endif //%header_file_path% >> %header_file_path%