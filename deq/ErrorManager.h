#pragma once

#include <iostream>

enum ErrorLevel
{
	INFORMATION,
	WARNING,
	ERROR
};

class ErrorManager
{
public:
	static void log(const char* message, ErrorLevel error_level);
};