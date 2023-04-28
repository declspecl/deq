#pragma once

#include "Token.h"
#include "ErrorManager.h"

#include <vector>
#include <string>

class Lexer
{
private:
	bool add_next_token(unsigned offset);

public:
	std::vector<Token> tokens;
	const char* source;

	Lexer(const char* source, std::vector<Token> tokens = {});

	bool tokenize();
};