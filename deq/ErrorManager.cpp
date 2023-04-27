#include "ErrorManager.h"

void ErrorManager::log(const char* message, ErrorLevel error_level)
{
	std::string message_prefix;

	switch (error_level)
	{
		case ErrorLevel::INFORMATION:
			message_prefix = "[*] INFO: ";
			break;
		case ErrorLevel::WARNING:
			message_prefix = "[-] WARNING: ";
			break;
		case ErrorLevel::ERROR:
			message_prefix = "[!] ERROR: ";
			break;
		default:
			message_prefix = "[?] UNKNOWN ERROR LEVEL: ";
			break;
	}

	std::cout << message_prefix << message << std::endl;
}