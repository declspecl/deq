#include "Token.h"
#include "Lexer.h"

#include <vector>
#include <iostream>

int main(int argc, char** argv)
{
	if (argc < 2) // real time interpreter
	{
		std::cout << "This is the deq real time interpreter.\nInput code line by line and see it execute after each line. Type \"quit\" to quit.\n" << std::endl;

		while (true)
		{
			std::cout << ">> ";

			std::string user_input;

			std::getline(std::cin, user_input);

			if (user_input == "quit")
				break;

			Lexer lexer(user_input.c_str());

			bool had_error = lexer.tokenize();

			if (had_error)
				std::cout << "had error" << std::endl;

#ifdef _DEBUG
			std::cout << lexer.tokens.size() << " tokens found:" << std::endl;

			for (const Token& token : lexer.tokens)
				std::cout << token.to_string() << ": " << user_input.substr(token.offset, token.length) << std::endl;

			std::cout << std::endl;
#endif
		}
	}
	else if (argc == 2) // file interpreter
	{
		const char* target_file = argv[1];
	}
	else
	{
		std::cout << "[!] Error code 64: Too many arguments inputted. Usage: `deq` or `deq <scriptname>`" << std::endl;

		return 64;
	}

	return 0;
}