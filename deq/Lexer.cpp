#include "Lexer.h"

Lexer::Lexer(const char* source, std::vector<Token> tokens) noexcept
	: tokens(tokens)
	, source(source)
{

}

bool Lexer::add_next_token(unsigned offset)
{
	bool had_error = false;

	switch (this->source[offset])
	{
	/*
		single character tokens
	*/
	case '\0':
		this->tokens.push_back(Token(TokenType::EOF_, offset, 1));

		break;

	case '(':
		this->tokens.push_back(Token(TokenType::L_PAREN, offset, 1));

		break;

	case ')':
		this->tokens.push_back(Token(TokenType::R_PAREN, offset, 1));

		break;

	case '[':
		this->tokens.push_back(Token(TokenType::L_SQUARE_BRACKET, offset, 1));

		break;

	case ']':
		this->tokens.push_back(Token(TokenType::R_SQUARE_BRACKET, offset, 1));

		break;

	case '{':
		this->tokens.push_back(Token(TokenType::L_CURLY_BRACKET, offset, 1));

		break;

	case '}':
		this->tokens.push_back(Token(TokenType::R_CURLY_BRACKET, offset, 1));

		break;

	case '<':
		if (this->source[offset + 1] == '=')
			this->tokens.push_back(Token(TokenType::L_ANGLED_BRACKET_EQUALS, offset, 2));
		else
			this->tokens.push_back(Token(TokenType::L_ANGLED_BRACKET, offset, 1));

		break;

	case '>':
		if (this->source[offset + 1] == '=')
			this->tokens.push_back(Token(TokenType::R_ANGLED_BRACKET_EQUALS, offset, 2));
		else
			this->tokens.push_back(Token(TokenType::R_ANGLED_BRACKET, offset, 1));

		break;

	case ',':
		this->tokens.push_back(Token(TokenType::COMMA, offset, 1));

		break;

	case '.':
		this->tokens.push_back(Token(TokenType::PERIOD, offset, 1));

		break;

	case ':':
		if (this->source[offset + 1] == ':')
			this->tokens.push_back(Token(TokenType::DOUBLE_COLON, offset, 2));
		else
			this->tokens.push_back(Token(TokenType::COLON, offset, 1));

		break;

	case ';':
		this->tokens.push_back(Token(TokenType::SEMICOLON, offset, 1));

		break;

	case '\'':
		this->tokens.push_back(Token(TokenType::CHAR_LITERAL, offset, 3));

		if ((Token::is_null_byte(this->source[offset + 1]) || (this->source[offset + 2] != '\'')))
		{
			ErrorManager::log("Invalid character literal", ErrorLevel::ERROR);

			had_error = true;
		}

		break;

	case '\"':
	{
		unsigned length = 1;

		while (this->source[offset + length] != '\"')
		{
			if (Token::is_null_byte(this->source[offset + length]))
			{
				ErrorManager::log("Unclosed string literal", ErrorLevel::ERROR);

				had_error = true;

				break; // need to break out of while loop and trigger tokenizing the EOF
			}
			else
				length++;
		}

		this->tokens.push_back(Token(TokenType::STRING_LITERAL, offset, length + 1));

		break;
	}

	case '\\':
		this->tokens.push_back(Token(TokenType::BACK_SLASH, offset, 1));

		break;

	case '/':
		if (this->source[offset + 1] == '=')
			this->tokens.push_back(Token(TokenType::FORWARD_SLASH_EQUALS, offset, 2));
		else
			this->tokens.push_back(Token(TokenType::FORWARD_SLASH, offset, 1));

		break;

	case '|':
		if (this->source[offset + 1] == '|')
			this->tokens.push_back(Token(TokenType::DOUBLE_PIPE, offset, 2));
		else
			this->tokens.push_back(Token(TokenType::PIPE, offset, 1));

		break;

	case '!':
		if (this->source[offset + 1] == '=')
			this->tokens.push_back(Token(TokenType::EXCLAMATION_EQUALS, offset, 2));
		else
			this->tokens.push_back(Token(TokenType::EXCLAMATION_MARK, offset, 1));

		break;

	case '@':
		this->tokens.push_back(Token(TokenType::AT_SIGN, offset, 1));

		break;

	case '#':
		this->tokens.push_back(Token(TokenType::POUND_SIGN, offset, 1));

		break;

	case '$':
		this->tokens.push_back(Token(TokenType::DOLLAR_SIGN, offset, 1));

		break;

	case '%':
		this->tokens.push_back(Token(TokenType::PERCENT_SIGN, offset, 1));

		break;

	case '^':
		this->tokens.push_back(Token(TokenType::CARET, offset, 1));

		break;

	case '&':
		if (this->source[offset + 1] == '&')
			this->tokens.push_back(Token(TokenType::DOUBLE_AMPERSAND, offset, 2));
		else
			this->tokens.push_back(Token(TokenType::AMPERSAND, offset, 1));

		break;

	case '*':
		if (this->source[offset + 1] == '=')
			this->tokens.push_back(Token(TokenType::ASTERISK_EQUALS, offset, 2));
		else
			this->tokens.push_back(Token(TokenType::ASTERISK, offset, 1));

		break;

	case '+':
		if (this->source[offset + 1] == '=')
			this->tokens.push_back(Token(TokenType::PLUS_EQUALS, offset, 2));
		else
			this->tokens.push_back(Token(TokenType::PLUS, offset, 1));

		break;

	case '=':
		if (this->source[offset + 1] == '=')
			this->tokens.push_back(Token(TokenType::DOUBLE_EQUALS, offset, 2));
		else
			this->tokens.push_back(Token(TokenType::EQUALS, offset, 1));

		break;

	case '-':
		if (this->source[offset + 1] == '=')
			this->tokens.push_back(Token(TokenType::MINUS_EQUALS, offset, 2));
		else if (this->source[offset + 1] == '>')
			this->tokens.push_back(Token(TokenType::ARROW, offset, 2));
		else
			this->tokens.push_back(Token(TokenType::MINUS, offset, 1));

		break;

	case '_':
		this->tokens.push_back(Token(TokenType::UNDERSCORE, offset, 1));

		break;

	default:
		// identifiers and keywords
		if (Token::is_letter(this->source[offset]) || Token::is_underscore(this->source[offset]))
		{
			unsigned length = 1;

			while (Token::is_letter(this->source[offset + length]) || Token::is_number(this->source[offset + length]) || Token::is_underscore(this->source[offset + length]))
				length++;

			// max mulching and adding an identifier if it doesnt fully match a predefined keyword
			switch (length)
			{
			case 2:
				if (strncmp(this->source + offset, "if", 2) == 0)
					this->tokens.push_back(Token(TokenType::IF, offset, 2));
				else if (strncmp(this->source + offset, "fn", 2) == 0)
					this->tokens.push_back(Token(TokenType::FN, offset, 2));
				else if (strncmp(this->source + offset, "i8", 2) == 0)
					this->tokens.push_back(Token(TokenType::I8, offset, 2));
				else if (strncmp(this->source + offset, "u8", 2) == 0)
					this->tokens.push_back(Token(TokenType::U8, offset, 2));
				else
					this->tokens.push_back(Token(TokenType::IDENTIFIER, offset, length));

				break;

			case 3:
				if (strncmp(this->source + offset, "for", 3) == 0)
					this->tokens.push_back(Token(TokenType::FOR, offset, 3));
				else if (strncmp(this->source + offset, "let", 3) == 0)
					this->tokens.push_back(Token(TokenType::LET, offset, 3));
				else if (strncmp(this->source + offset, "mut", 3) == 0)
					this->tokens.push_back(Token(TokenType::MUT, offset, 3));
				else if (strncmp(this->source + offset, "i16", 3) == 0)
					this->tokens.push_back(Token(TokenType::I16, offset, 3));
				else if (strncmp(this->source + offset, "i32", 3) == 0)
					this->tokens.push_back(Token(TokenType::I32, offset, 3));
				else if (strncmp(this->source + offset, "i64", 3) == 0)
					this->tokens.push_back(Token(TokenType::I64, offset, 3));
				else if (strncmp(this->source + offset, "u16", 3) == 0)
					this->tokens.push_back(Token(TokenType::U16, offset, 3));
				else if (strncmp(this->source + offset, "u32", 3) == 0)
					this->tokens.push_back(Token(TokenType::U32, offset, 3));
				else if (strncmp(this->source + offset, "u64", 3) == 0)
					this->tokens.push_back(Token(TokenType::U64, offset, 3));
				else if (strncmp(this->source + offset, "f32", 3) == 0)
					this->tokens.push_back(Token(TokenType::F32, offset, 3));
				else if (strncmp(this->source + offset, "f64", 3) == 0)
					this->tokens.push_back(Token(TokenType::F64, offset, 3));
				else
					this->tokens.push_back(Token(TokenType::IDENTIFIER, offset, length));

				break;

			case 4:
				if (strncmp(this->source + offset, "else", 4) == 0)
					this->tokens.push_back(Token(TokenType::ELSE, offset, 4));
				else if (strncmp(this->source + offset, "case", 4) == 0)
					this->tokens.push_back(Token(TokenType::CASE, offset, 4));
				else if (strncmp(this->source + offset, "this", 4) == 0)
					this->tokens.push_back(Token(TokenType::THIS, offset, 4));
				else if (strncmp(this->source + offset, "null", 4) == 0)
					this->tokens.push_back(Token(TokenType::NULL_, offset, 4));
				else if (strncmp(this->source + offset, "char", 4) == 0)
					this->tokens.push_back(Token(TokenType::CHAR, offset, 4));
				else if (strncmp(this->source + offset, "bool", 4) == 0)
					this->tokens.push_back(Token(TokenType::BOOL, offset, 4));
				else if (strncmp(this->source + offset, "void", 4) == 0)
					this->tokens.push_back(Token(TokenType::VOID, offset, 4));
				else if (strncmp(this->source + offset, "true", 4) == 0)
					this->tokens.push_back(Token(TokenType::TRUE_LITERAL, offset, 4));
				else
					this->tokens.push_back(Token(TokenType::IDENTIFIER, offset, length));

				break;

			case 5:
				if (strncmp(this->source + offset, "while", 5) == 0)
					this->tokens.push_back(Token(TokenType::WHILE, offset, 5));
				else if (strncmp(this->source + offset, "class", 5) == 0)
					this->tokens.push_back(Token(TokenType::CLASS, offset, 5));
				else if (strncmp(this->source + offset, "match", 5) == 0)
					this->tokens.push_back(Token(TokenType::MATCH, offset, 5));
				else if (strncmp(this->source + offset, "false", 5) == 0)
					this->tokens.push_back(Token(TokenType::FALSE_LITERAL, offset, 5));
				else
					this->tokens.push_back(Token(TokenType::IDENTIFIER, offset, length));

				break;

			case 6:
				if (strncmp(this->source + offset, "public", 6) == 0)
					this->tokens.push_back(Token(TokenType::PUBLIC, offset, 6));
				else if (strncmp(this->source + offset, "static", 6) == 0)
					this->tokens.push_back(Token(TokenType::STATIC, offset, 6));
				else if (strncmp(this->source + offset, "return", 6) == 0)
					this->tokens.push_back(Token(TokenType::RETURN, offset, 6));
				else if (strncmp(this->source + offset, "string", 6) == 0)
					this->tokens.push_back(Token(TokenType::STRING, offset, 6));
				else
					this->tokens.push_back(Token(TokenType::IDENTIFIER, offset, length));

				break;

			case 7:
				if (strncmp(this->source + offset, "private", 7) == 0)
					this->tokens.push_back(Token(TokenType::PRIVATE, offset, 7));
				else
					this->tokens.push_back(Token(TokenType::IDENTIFIER, offset, length));

				break;

			case 9:
				if (strncmp(this->source + offset, "protected", 7) == 0)
					this->tokens.push_back(Token(TokenType::PROTECTED, offset, 9));
				else
					this->tokens.push_back(Token(TokenType::IDENTIFIER, offset, length));

				break;

			default:
				this->tokens.push_back(Token(TokenType::IDENTIFIER, offset, length));

				break;
			}
		}

		// number literal
		else if (Token::is_number(this->source[offset]))
		{
			unsigned length = 1;

			bool is_float = false;

			while (Token::is_number(this->source[offset + length]) || Token::is_period(this->source[offset + length]))
			{
				if (Token::is_period(this->source[offset + length]))
				{
					if (is_float)
					{
						ErrorManager::log("Two or more periods in the same number", ErrorLevel::ERROR);

						had_error = true;
					}
					else
						is_float = true;
				}

				length++;
			}

			this->tokens.push_back(Token((is_float) ? TokenType::FLOAT_LITERAL : TokenType::INTEGER_LITERAL, offset, length));
		}

		// unknown
		else
			this->tokens.push_back(Token(TokenType::UNKNOWN, offset, 1));

		break;
	}

	return had_error;
}

bool Lexer::tokenize()
{
	const size_t max_index = strlen(this->source) + 1;
	tokens.reserve(max_index / 3);

	unsigned offset = 0;

	bool had_error = false;

	while (offset < max_index)
	{
		// skip spaces. newlines, and tabs
		if (Token::is_whitespace(this->source[offset]) || Token::is_tab(this->source[offset]) || Token::is_newline(this->source[offset]))
		{
			offset++;
		}

		// skip single line comments
		else if (strncmp(this->source + offset, "//", 2) == 0)
		{
			while (!Token::is_newline(this->source[offset]) && !Token::is_null_byte(this->source[offset]))
				offset++;

			offset++;

			// TODO: is it possible for this to go on infinitely?
		}

		// skip multi line comments
		else if (strncmp(this->source + offset, "/*", 2) == 0)
		{
			bool closing_found = false;

			while (!Token::is_null_byte(this->source[offset]))
			{
				if (strncmp(this->source + offset, "*/", 2) == 0)
				{
					offset += 2;

					closing_found = true;

					break;
				}
				else
					offset++;
			}

			if (Token::is_null_byte(this->source[offset]) && !closing_found)
			{
				ErrorManager::log("Unclosed multi line comment", ErrorLevel::ERROR);

				had_error = true;
			}
		}

		// if not any of above, tokenize
		else
		{
			if (this->add_next_token(offset))
				had_error = true;

			offset += this->tokens[this->tokens.size() - 1].length;
		}
	}

	return had_error;
}
