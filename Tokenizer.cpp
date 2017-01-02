#include "Tokenizer.h"

Tokenizer::Tokenizer(string data):
 data(data), pos(0), line(1), col(0), current_char(0)
 {

 }

 void Tokenizer::initialize(string data) {
 	this->data = data;
 	pos = line = col = current_char = 0;
 }

 bool Tokenizer::nextChar()
 {
 	if ( pos >= data.length() ) {
 		return false;
 	}
 	current_char = data[pos];
 	pos++;
 	col++;
 	return true;
 }

 Token Tokenizer::nextToken()
 {
 	Token temp;
 	while ( nextChar() ) {
 		temp.col = col;
 		if ( isspace(current_char) ) {
 			continue;
 		}
 		else if ( isalpha(current_char) ) {
 			return processWord();
 		}
 		else if ( isdigit(current_char) ) {
 			temp.value = processNumber();
 			temp.type = NUMBER;
 			temp.line = line;
 		}
 		else {
 			switch (current_char) {
 				case '-':
 				temp.type = MINUS;
 				break;
 				case '+':
 				temp.type = PLUS;
 				break;
 				case '*':
 				temp.type = MULTIPLY;
 				break;
 				case '/':
 				temp.type = DIVIDE;
 				break;
 				case ',':
 				temp.type = COMMA;
 				break;
 				case '\'':
 				temp.type = APOSTROPHE;
 				break;
 				case '.':
 				temp.type = DOT;
 				break;
 				case '\n':
 				line++;
 				col = 0;
 				continue;
 				break;
 				case '(':
 				temp.type = LPAREN;
 				break;
 				case ')':
 				temp.type = RPAREN;
 				break;
 				case '=':
 				temp.type = ASSIGN;
 				break;
 				case '{':
 				skipComment();
 				continue;
 				break;
 				default:
                error << "Error @ " << line <<"," << col << ": Unknown character, " << current_char;
 				throw error.str().c_str();
 				break;
 			}
 			temp.value = current_char;
 		}
 		return temp;
 	}
 	temp.type = EOS;
 	return temp;
 }

 Token Tokenizer::peek() {
 	unsigned int tpos = pos, tcol = col, tline = line;
 	Token temp = nextToken();
 	pos = tpos;
 	col = tcol;
 	line = tline;
 	return temp;
 }

 Token Tokenizer::processWord()
 {
 	Token temp;
 	temp.line = line;
 	temp.col = col;
 	do {
 		if ( isdigit(current_char) || isalpha(current_char) ) {
 		temp.value += current_char;
 		}
 		else {
 			stepBack();
 			if ( isId(temp.value)) {
 				temp.type = ID;
 			}
 			return temp;
 		}
 	} while ( nextChar() );
 }

 bool Tokenizer::isId(string value){
 	return true;
 }

 string Tokenizer::processNumber()
 {
 	bool rhs = false, just_dotted;
 	string temp = "";
 	if ( current_char == '+' || current_char == '-' ) {
 		temp += current_char;
 		nextChar();
 	}
 	do {
 		if ( isdigit(current_char) ) {
 			 just_dotted = false;
 			temp += current_char;
 		}
 		else if ( !rhs && current_char=='.' ) {
 			rhs = true;
 			just_dotted = true;
 			temp += current_char;
 		}
 		else if ( just_dotted ) {
 			stepBack();
 			temp.erase( temp.end()-1 );
 			stepBack();
 			return temp;
 		}
 		else {
 			stepBack();
 			return temp;
 		}
 	} while ( nextChar() );
 }

 void Tokenizer::skipComment() {
 	do {
 		if ( current_char == '}' ) {
 			//nextChar();
 			break;
 		}
 		else if ( current_char == '\n' ) {
 			line++;
 		}
 	} while ( nextChar() );
 }

void Tokenizer::stepBack()
  {
 	pos--;
 	col--;
  }
