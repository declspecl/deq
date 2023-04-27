#pragma once

#include "Token.h"
#include "ErrorManager.h"

#include <vector>
#include <string>
#include <iostream>

class Lexer
{
private:
	bool add_next_token();

public:
	std::vector<Token> tokens;
	const char* source;
	unsigned offset;

	Lexer();
	Lexer(std::vector<Token> tokens, const char* source, unsigned offset);

	bool tokenize();
};