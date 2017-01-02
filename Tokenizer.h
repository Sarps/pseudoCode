#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>

#include "Token.h"
#include "Library.h"

using namespace std;

class Tokenizer
{
	public:
	Tokenizer(string data="");
	Token nextToken();
	void initialize(string data);
	Token peek();

	private:
	char current_char;
	bool nextChar();
	bool isId(string value);
	string processNumber();
	Token processWord();
	void stepBack();
	void skipComment();
	unsigned int pos, line, col;
	string data;
	stringstream error;
};
#endif
 //--- End of Tokenizer.h
