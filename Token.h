#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;

typedef enum token_type {
	UNKNOWN = -2,
	EOS,
	EOL,
	VERB,
	NOUN,
	NUMBER,
	COMMA,
	APOSTROPHE,
	DOT,
	PLUS,
	MINUS,
	MULTIPLY,
	DIVIDE,
	LPAREN,
	RPAREN,
	ID,
	ASSIGN
} token_type;

class Token {
	public:
	Token(token_type type=UNKNOWN , string value="");
	string value;
	token_type type;
	unsigned int line, col;

	private:

};

#endif
