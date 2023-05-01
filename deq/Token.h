#pragma once

#include <string>

enum TokenType
{
	// symbol tokens
	L_PAREN, R_PAREN,
	L_SQUARE_BRACKET, R_SQUARE_BRACKET,
	L_CURLY_BRACKET, R_CURLY_BRACKET,
	L_ANGLED_BRACKET, R_ANGLED_BRACKET, L_ANGLED_BRACKET_EQUALS, R_ANGLED_BRACKET_EQUALS,

	COMMA, PERIOD,
	COLON, DOUBLE_COLON, SEMICOLON,
	// SINGLE_QUOTE, DOUBLE_QUOTE,
	BACK_SLASH, FORWARD_SLASH, FORWARD_SLASH_EQUALS, PIPE, DOUBLE_PIPE,

	EXCLAMATION_MARK, EXCLAMATION_EQUALS,
	AT_SIGN,
	POUND_SIGN,
	DOLLAR_SIGN,
	PERCENT_SIGN,
	CARET,
	AMPERSAND,
	DOUBLE_AMPERSAND,
	ASTERISK, ASTERISK_EQUALS,
	PLUS, PLUS_EQUALS,
	EQUALS, DOUBLE_EQUALS,
	MINUS, MINUS_EQUALS, ARROW,
	UNDERSCORE,

	// keywords
	IF, ELSE, FOR, WHILE,
	CLASS, PUBLIC, PRIVATE, PROTECTED, STATIC,
	MATCH, CASE,
	LET, MUT, FN,
	THIS,
	RETURN,
	NULL_,

	// types
	I8, I16, I32, I64,
	U8, U16, U32, U64,
	F32, F64,
	STRING, CHAR,
	BOOL,
	VOID,

	// literals
	IDENTIFIER,
	INTEGER_LITERAL,
	FLOAT_LITERAL,
	STRING_LITERAL,
	CHAR_LITERAL,
	TRUE_LITERAL, FALSE_LITERAL,

	// misc
	UNKNOWN,
	IGNORE_INVALID,
	EOF_
};

class Token
{
public:
	TokenType type;

	unsigned offset;
	unsigned length;

	Token(TokenType type, unsigned offset, unsigned length) noexcept;

	std::string to_string() const;

	static inline bool is_letter(char character) { return (character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z'); }
	static inline bool is_number(char character) { return character >= '0' && character <= '9'; };
	static inline bool is_underscore(char character) { return character == '_'; }
	static inline bool is_whitespace(char character) { return character == ' '; }
	static inline bool is_period(char character) { return character == '.'; }
	static inline bool is_null_byte(char character) { return character == '\0'; }
	static inline bool is_newline(char character) { return character == '\n'; }
	static inline bool is_tab(char character) { return character == '\t'; }
};