#include "Lexer.h"

Token Lexer::find_next_token(const char* str, unsigned offset)
{
	switch (str[offset])
	{
	case '(':
		return Token(TokenType::L_PAREN, offset, 1);
	case ')':
		return Token(TokenType::R_PAREN, offset, 1);
	case '[':
		return Token(TokenType::L_SQUARE_BRACKET, offset, 1);
	case ']':
		return Token(TokenType::R_SQUARE_BRACKET, offset, 1);
	case '{':
		return Token(TokenType::L_CURLY_BRACKET, offset, 1);
	case '}':
		return Token(TokenType::R_CURLY_BRACKET, offset, 1);
	case '<':
		if (str[offset + 1] == '=')
			return Token(TokenType::L_ANGLED_BRACKET_EQUALS, offset, 2);
		else
			return Token(TokenType::L_ANGLED_BRACKET, offset, 1);
	case '>':
		if (str[offset + 1] == '=')
			return Token(TokenType::R_ANGLED_BRACKET_EQUALS, offset, 2);
		else
			return Token(TokenType::R_ANGLED_BRACKET, offset, 1);
	case ',':
		return Token(TokenType::COMMA, offset, 1);
	case '.':
		return Token(TokenType::PERIOD, offset, 1);
	case ':':
		if (str[offset + 1] == ':')
			return Token(TokenType::DOUBLE_COLON, offset, 2);
		else
			return Token(TokenType::COLON, offset, 1);
	case ';':
		return Token(TokenType::SEMICOLON, offset, 1);
	case '\'':
		if ((!Token::is_null_byte(str[offset + 1]) && (str[offset + 2] == '\'')))
			return Token(TokenType::CHAR_LITERAL, offset, 3);
		
		// else TODO: invalid character / single quote detected, error
	case '\"':
	{
		unsigned length = 1;

		while (!Token::is_null_byte(str[offset + length]) && str[offset + length] != '\"')
			length++;

		// TODO: handle error if encounters null byte before double quote

		return Token(TokenType::STRING_LITERAL, offset, length + 1);
	}
	case '\\':
		return Token(TokenType::BACK_SLASH, offset, 1);
	case '/':
		if (str[offset + 1] == '=')
			return Token(TokenType::FORWARD_SLASH_EQUALS, offset, 2);
		else
			return Token(TokenType::FORWARD_SLASH, offset, 1);
	case '|':
		if (str[offset + 1] == '|')
			return Token(TokenType::DOUBLE_PIPE, offset, 2);
		else
			return Token(TokenType::PIPE, offset, 1);
	case '!':
		if (str[offset + 1] == '=')
			return Token(TokenType::EXCLAMATION_EQUALS, offset, 2);
		else
			return Token(TokenType::EXCLAMATION_MARK, offset, 1);
	case '@':
		return Token(TokenType::AT_SIGN, offset, 1);
	case '#':
		return Token(TokenType::POUND_SIGN, offset, 1);
	case '$':
		return Token(TokenType::DOLLAR_SIGN, offset, 1);
	case '%':
		return Token(TokenType::PERCENT_SIGN, offset, 1);
	case '^':
		return Token(TokenType::CARET, offset, 1);
	case '&':
		if (str[offset + 1] == '&')
			return Token(TokenType::DOUBLE_AMPERSAND, offset, 2);
		else
			return Token(TokenType::AMPERSAND, offset, 1);
	case '*':
		if (str[offset + 1] == '=')
			return Token(TokenType::ASTERISK_EQUALS, offset, 2);
		else
			return Token(TokenType::ASTERISK, offset, 1);
	case '+':
		if (str[offset + 1] == '=')
			return Token(TokenType::PLUS_EQUALS, offset, 2);
		else
			return Token(TokenType::PLUS, offset, 1);
	case '=':
		if (str[offset + 1] == '=')
			return Token(TokenType::DOUBLE_EQUALS, offset, 2);
		else
			return Token(TokenType::EQUALS, offset, 1);
	case '-':
		if (str[offset + 1] == '=')
			return Token(TokenType::MINUS_EQUALS, offset, 2);
		else if (str[offset + 1] == '>')
			return Token(TokenType::ARROW, offset, 2);
		else
			return Token(TokenType::MINUS, offset, 1);
	case '_':
		return Token(TokenType::UNDERSCORE, offset, 1);
	default:
		if (strncmp(str + offset, "if", 2) == 0)
			return Token(TokenType::IF, offset, 2);
		else if (strncmp(str + offset, "else", 4) == 0)
			return Token(TokenType::ELSE, offset, 4);
		else if (strncmp(str + offset, "for", 3) == 0)
			return Token(TokenType::FOR, offset, 3);
		else if (strncmp(str + offset, "while", 5) == 0)
			return Token(TokenType::WHILE, offset, 5);
		else if (strncmp(str + offset, "match", 5) == 0)
			return Token(TokenType::MATCH, offset, 5);
		else if (strncmp(str + offset, "case", 4) == 0)
			return Token(TokenType::CASE, offset, 4);
		else if (strncmp(str + offset, "let", 3) == 0)
			return Token(TokenType::LET, offset, 3);
		else if (strncmp(str + offset, "fn", 2) == 0)
			return Token(TokenType::FN, offset, 2);
		else if (strncmp(str + offset, "this", 4) == 0)
			return Token(TokenType::THIS, offset, 4);
		else if (strncmp(str + offset, "return", 6) == 0)
			return Token(TokenType::RETURN, offset, 6);
		else if (strncmp(str + offset, "null", 4) == 0)
			return Token(TokenType::NULL_, offset, 4);
		else if (strncmp(str + offset, "i8", 2) == 0)
			return Token(TokenType::I8, offset, 2);
		else if (strncmp(str + offset, "i16", 3) == 0)
			return Token(TokenType::I16, offset, 3);
		else if (strncmp(str + offset, "i32", 3) == 0)
			return Token(TokenType::I32, offset, 3);
		else if (strncmp(str + offset, "i64", 3) == 0)
			return Token(TokenType::I64, offset, 3);
		else if (strncmp(str + offset, "u8", 2) == 0)
			return Token(TokenType::U8, offset, 2);
		else if (strncmp(str + offset, "u16", 3) == 0)
			return Token(TokenType::U16, offset, 3);
		else if (strncmp(str + offset, "u32", 3) == 0)
			return Token(TokenType::U32, offset, 3);
		else if (strncmp(str + offset, "u64", 3) == 0)
			return Token(TokenType::U64, offset, 3);
		else if (strncmp(str + offset, "f32", 3) == 0)
			return Token(TokenType::F32, offset, 3);
		else if (strncmp(str + offset, "f64", 3) == 0)
			return Token(TokenType::F64, offset, 3);
		else if (strncmp(str + offset, "string", 6) == 0)
			return Token(TokenType::STRING, offset, 6);
		else if (strncmp(str + offset, "char", 4) == 0)
			return Token(TokenType::CHAR, offset, 4);
		else if (strncmp(str + offset, "bool", 4) == 0)
			return Token(TokenType::BOOL, offset, 4);
		else if (strncmp(str + offset, "void", 4) == 0)
			return Token(TokenType::VOID, offset, 4);
		else if (strncmp(str + offset, "true", 4) == 0)
			return Token(TokenType::TRUE_LITERAL, offset, 4);
		else if (strncmp(str + offset, "false", 5) == 0)
			return Token(TokenType::FALSE_LITERAL, offset, 5);
		else
		{
			if (Token::is_letter(str[offset]) || Token::is_underscore(str[offset]))
			{
				unsigned length = 1;

				while (Token::is_letter(str[offset + length]) || Token::is_number(str[offset + length]) || Token::is_underscore(str[offset + length]))
					length++;

				return Token(TokenType::IDENTIFIER, offset, length);
			}
			else if (Token::is_number(str[offset]))
			{
				unsigned length = 1;
				bool is_float = false;

				while (!Token::is_null_byte(str[offset + length]))
				{
					if (Token::is_number(str[offset + length]))
						length++;
					else if (Token::is_period(str[offset + length]))
					{
						is_float = true;

						// TODO: if already put a period, error (if (is_float) { ... })

						length++;
					}
					else
						break;
				}

				return Token((is_float) ? TokenType::FLOAT_LITERAL : TokenType::INTEGER_LITERAL, offset, length);
			}
			else
				return Token(TokenType::UNKNOWN, offset, 1);
		}
	}
}

std::vector<Token> Lexer::tokenize(const char* str)
{
	std::vector<Token> tokens;
	tokens.reserve(strlen(str) / 3);

	unsigned offset = 0;

	while (!Token::is_null_byte(str[offset]))
	{
		printf("offset: %d\n", offset);

		if (Token::is_whitespace(str[offset]))
		{
			offset++;

			continue;
		}
		else if (strncmp(str + offset, "//", 2) == 0)
		{
			while (!Token::is_newline(str[offset]) && !Token::is_null_byte(str[offset]))
				offset++;

			// TODO: is it possible for this to go on infinitely?

			continue;
		}
		else if (strncmp(str + offset, "/*", 2) == 0)
		{
			std::cout << "found */" << std::endl;
			while (!Token::is_null_byte(str[offset]))
			{
				if (strncmp(str + offset, "*/", 2) == 0)
				{
					offset += 2;

					break;
				}
				else
					offset++;
			}

			// TOOD: need to handle error that its not closed

			continue;
		}
		else
		{

			Token next_token = Lexer::find_next_token(str, offset);

			tokens.push_back(next_token);

			offset += next_token.length;
		}
	}

	return tokens;
}

std::vector<Token> Lexer::tokenize(std::string str)
{
	return Lexer::tokenize(str.c_str());
}