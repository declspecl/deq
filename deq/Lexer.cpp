#include "Lexer.h"

Lexer::Lexer()
	: tokens({})
	, source("")
	, offset(0)
{

}

Lexer::Lexer(std::vector<Token> tokens, const char* source, unsigned offset)
	: tokens(tokens)
	, source(source)
	, offset(offset)
{

}

bool Lexer::add_next_token()
{
	switch (this->source[this->offset])
	{
	case '\0':
		this->tokens.push_back(Token(TokenType::EOF_, this->offset, 1));
	case '(':
		this->tokens.push_back(Token(TokenType::L_PAREN, this->offset, 1));
	case ')':
		this->tokens.push_back(Token(TokenType::R_PAREN, this->offset, 1));
	case '[':
		this->tokens.push_back(Token(TokenType::L_SQUARE_BRACKET, this->offset, 1));
	case ']':
		this->tokens.push_back(Token(TokenType::R_SQUARE_BRACKET, this->offset, 1));
	case '{':
		this->tokens.push_back(Token(TokenType::L_CURLY_BRACKET, this->offset, 1));
	case '}':
		this->tokens.push_back(Token(TokenType::R_CURLY_BRACKET, this->offset, 1));
	case '<':
		if (this->source[this->offset + 1] == '=')
			this->tokens.push_back(Token(TokenType::L_ANGLED_BRACKET_EQUALS, this->offset, 2));
		else
			this->tokens.push_back(Token(TokenType::L_ANGLED_BRACKET, this->offset, 1));
	case '>':
		if (this->source[this->offset + 1] == '=')
			this->tokens.push_back(Token(TokenType::R_ANGLED_BRACKET_EQUALS, this->offset, 2));
		else
			this->tokens.push_back(Token(TokenType::R_ANGLED_BRACKET, this->offset, 1));
	case ',':
		this->tokens.push_back(Token(TokenType::COMMA, this->offset, 1));
	case '.':
		this->tokens.push_back(Token(TokenType::PERIOD, this->offset, 1));
	case ':':
		if (this->source[this->offset + 1] == ':')
			this->tokens.push_back(Token(TokenType::DOUBLE_COLON, this->offset, 2));
		else
			this->tokens.push_back(Token(TokenType::COLON, this->offset, 1));
	case ';':
		this->tokens.push_back(Token(TokenType::SEMICOLON, this->offset, 1));
	case '\'':
		if ((!Token::is_null_byte(this->source[this->offset + 1]) && (this->source[this->offset + 2] == '\'')))
			this->tokens.push_back(Token(TokenType::CHAR_LITERAL, this->offset, 3));
		else
		{
			ErrorManager::log("Unclosed character literal", ErrorLevel::ERROR);

			return false;
		}
	case '\"':
	{
		unsigned length = 1;

		while (!Token::is_null_byte(this->source[this->offset + length]) && this->source[this->offset + length] != '\"')
			length++;

		// TODO: handle error if encounters null byte before double quote

		this->tokens.push_back(Token(TokenType::STRING_LITERAL, this->offset, length + 1));
	}
	case '\\':
		this->tokens.push_back(Token(TokenType::BACK_SLASH, this->offset, 1));
	case '/':
		if (this->source[this->offset + 1] == '=')
			this->tokens.push_back(Token(TokenType::FORWARD_SLASH_EQUALS, this->offset, 2));
		else
			this->tokens.push_back(Token(TokenType::FORWARD_SLASH, this->offset, 1));
	case '|':
		if (this->source[this->offset + 1] == '|')
			this->tokens.push_back(Token(TokenType::DOUBLE_PIPE, this->offset, 2));
		else
			this->tokens.push_back(Token(TokenType::PIPE, this->offset, 1));
	case '!':
		if (this->source[this->offset + 1] == '=')
			this->tokens.push_back(Token(TokenType::EXCLAMATION_EQUALS, this->offset, 2));
		else
			this->tokens.push_back(Token(TokenType::EXCLAMATION_MARK, this->offset, 1));
	case '@':
		this->tokens.push_back(Token(TokenType::AT_SIGN, this->offset, 1));
	case '#':
		this->tokens.push_back(Token(TokenType::POUND_SIGN, this->offset, 1));
	case '$':
		this->tokens.push_back(Token(TokenType::DOLLAR_SIGN, this->offset, 1));
	case '%':
		this->tokens.push_back(Token(TokenType::PERCENT_SIGN, this->offset, 1));
	case '^':
		this->tokens.push_back(Token(TokenType::CARET, this->offset, 1));
	case '&':
		if (this->source[this->offset + 1] == '&')
			this->tokens.push_back(Token(TokenType::DOUBLE_AMPERSAND, this->offset, 2));
		else
			this->tokens.push_back(Token(TokenType::AMPERSAND, this->offset, 1));
	case '*':
		if (this->source[this->offset + 1] == '=')
			this->tokens.push_back(Token(TokenType::ASTERISK_EQUALS, this->offset, 2));
		else
			this->tokens.push_back(Token(TokenType::ASTERISK, this->offset, 1));
	case '+':
		if (this->source[this->offset + 1] == '=')
			this->tokens.push_back(Token(TokenType::PLUS_EQUALS, this->offset, 2));
		else
			this->tokens.push_back(Token(TokenType::PLUS, this->offset, 1));
	case '=':
		if (this->source[this->offset + 1] == '=')
			this->tokens.push_back(Token(TokenType::DOUBLE_EQUALS, this->offset, 2));
		else
			this->tokens.push_back(Token(TokenType::EQUALS, this->offset, 1));
	case '-':
		if (this->source[this->offset + 1] == '=')
			this->tokens.push_back(Token(TokenType::MINUS_EQUALS, this->offset, 2));
		else if (this->source[this->offset + 1] == '>')
			this->tokens.push_back(Token(TokenType::ARROW, this->offset, 2));
		else
			this->tokens.push_back(Token(TokenType::MINUS, this->offset, 1));
	case '_':
		this->tokens.push_back(Token(TokenType::UNDERSCORE, this->offset, 1));
	default:
		if (strncmp(this->source + this->offset, "if", 2) == 0)
			this->tokens.push_back(Token(TokenType::IF, this->offset, 2));
		else if (strncmp(this->source + this->offset, "else", 4) == 0)
			this->tokens.push_back(Token(TokenType::ELSE, this->offset, 4));
		else if (strncmp(this->source + this->offset, "for", 3) == 0)
			this->tokens.push_back(Token(TokenType::FOR, this->offset, 3));
		else if (strncmp(this->source + this->offset, "while", 5) == 0)
			this->tokens.push_back(Token(TokenType::WHILE, this->offset, 5));
		else if (strncmp(this->source + this->offset, "match", 5) == 0)
			this->tokens.push_back(Token(TokenType::MATCH, this->offset, 5));
		else if (strncmp(this->source + this->offset, "case", 4) == 0)
			this->tokens.push_back(Token(TokenType::CASE, this->offset, 4));
		else if (strncmp(this->source + this->offset, "let", 3) == 0)
			this->tokens.push_back(Token(TokenType::LET, this->offset, 3));
		else if (strncmp(this->source + this->offset, "mut", 3) == 0)
			this->tokens.push_back(Token(TokenType::MUT, this->offset, 3));
		else if (strncmp(this->source + this->offset, "fn", 2) == 0)
			this->tokens.push_back(Token(TokenType::FN, this->offset, 2));
		else if (strncmp(this->source + this->offset, "this", 4) == 0)
			this->tokens.push_back(Token(TokenType::THIS, this->offset, 4));
		else if (strncmp(this->source + this->offset, "return", 6) == 0)
			this->tokens.push_back(Token(TokenType::RETURN, this->offset, 6));
		else if (strncmp(this->source + this->offset, "null", 4) == 0)
			this->tokens.push_back(Token(TokenType::NULL_, this->offset, 4));
		else if (strncmp(this->source + this->offset, "i8", 2) == 0)
			this->tokens.push_back(Token(TokenType::I8, this->offset, 2));
		else if (strncmp(this->source + this->offset, "i16", 3) == 0)
			this->tokens.push_back(Token(TokenType::I16, this->offset, 3));
		else if (strncmp(this->source + this->offset, "i32", 3) == 0)
			this->tokens.push_back(Token(TokenType::I32, this->offset, 3));
		else if (strncmp(this->source + this->offset, "i64", 3) == 0)
			this->tokens.push_back(Token(TokenType::I64, this->offset, 3));
		else if (strncmp(this->source + this->offset, "u8", 2) == 0)
			this->tokens.push_back(Token(TokenType::U8, this->offset, 2));
		else if (strncmp(this->source + this->offset, "u16", 3) == 0)
			this->tokens.push_back(Token(TokenType::U16, this->offset, 3));
		else if (strncmp(this->source + this->offset, "u32", 3) == 0)
			this->tokens.push_back(Token(TokenType::U32, this->offset, 3));
		else if (strncmp(this->source + this->offset, "u64", 3) == 0)
			this->tokens.push_back(Token(TokenType::U64, this->offset, 3));
		else if (strncmp(this->source + this->offset, "f32", 3) == 0)
			this->tokens.push_back(Token(TokenType::F32, this->offset, 3));
		else if (strncmp(this->source + this->offset, "f64", 3) == 0)
			this->tokens.push_back(Token(TokenType::F64, this->offset, 3));
		else if (strncmp(this->source + this->offset, "string", 6) == 0)
			this->tokens.push_back(Token(TokenType::STRING, this->offset, 6));
		else if (strncmp(this->source + this->offset, "char", 4) == 0)
			this->tokens.push_back(Token(TokenType::CHAR, this->offset, 4));
		else if (strncmp(this->source + this->offset, "bool", 4) == 0)
			this->tokens.push_back(Token(TokenType::BOOL, this->offset, 4));
		else if (strncmp(this->source + this->offset, "void", 4) == 0)
			this->tokens.push_back(Token(TokenType::VOID, this->offset, 4));
		else if (strncmp(this->source + this->offset, "true", 4) == 0)
			this->tokens.push_back(Token(TokenType::TRUE_LITERAL, this->offset, 4));
		else if (strncmp(this->source + this->offset, "false", 5) == 0)
			this->tokens.push_back(Token(TokenType::FALSE_LITERAL, this->offset, 5));
		else
		{
			if (Token::is_letter(this->source[this->offset]) || Token::is_underscore(this->source[this->offset]))
			{
				unsigned length = 1;

				while (Token::is_letter(this->source[this->offset + length]) || Token::is_number(this->source[this->offset + length]) || Token::is_underscore(this->source[this->offset + length]))
					length++;

				this->tokens.push_back(Token(TokenType::IDENTIFIER, this->offset, length));
			}
			else if (Token::is_number(this->source[this->offset]))
			{
				unsigned length = 1;
				bool is_float = false;

				while (!Token::is_null_byte(this->source[this->offset + length]))
				{
					if (Token::is_number(this->source[this->offset + length]))
						length++;
					else if (Token::is_period(this->source[this->offset + length]))
					{
						is_float = true;

						// TODO: if already put a period, error (if (is_float) { ... })

						length++;
					}
					else
						break;
				}

				this->tokens.push_back(Token((is_float) ? TokenType::FLOAT_LITERAL : TokenType::INTEGER_LITERAL, this->offset, length));
			}
			else
				this->tokens.push_back(Token(TokenType::UNKNOWN, this->offset, 1));
		}
	}
}

bool Lexer::tokenize()
{
	const unsigned max_index = strlen(this->source);
	tokens.reserve(max_index / 3);

	this->offset = 0;

	while (this->offset < max_index)
	{
		if (Token::is_whitespace(this->source[this->offset]) || Token::is_tab(this->source[this->offset]))
		{
			this->offset++;

			continue;
		}
		else if (strncmp(this->source + this->offset, "//", 2) == 0)
		{
			while (!Token::is_newline(this->source[this->offset]) && !Token::is_null_byte(this->source[this->offset]))
				this->offset++;

			offset++;

			// TODO: is it possible for this to go on infinitely?

			continue;
		}
		else if (strncmp(this->source + this->offset, "/*", 2) == 0)
		{
			while (!Token::is_null_byte(this->source[this->offset]))
			{
				if (strncmp(this->source + this->offset, "*/", 2) == 0)
				{
					this->offset += 2;

					break;
				}
				else
					this->offset++;
			}

			// TOOD: need to handle error that its not closed

			// ErrorManager::log("Unclosed multi line comment starting ")

			continue;
		}
		else
		{
			this->add_next_token();

			this->offset += this->tokens[this->tokens.size() - 1].length;
		}
	}

	return true;
}