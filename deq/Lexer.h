#pragma once

#include "Token.h"

#include <vector>
#include <string>

class Lexer
{
private:
	static Token find_next_token(const char* str, unsigned offset);

public:
	static std::vector<Token> tokenize(const char* str);
	static std::vector<Token> tokenize(std::string str);
};