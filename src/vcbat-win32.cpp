#pragma once

#include "vcbat-win32.hpp"

#include <pugixml/pugixml.cpp>

internal s32 
vcbat_win32_main(
	HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, 
	PWSTR     pCmdLine, 
	int       nCmdShow) {

	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file("..\\vctest\\vctest\\vctest.vcxproj");

	return(0);
}