#include "Parser.h"

Parser::Parser(string data) {
	loadSections(data);
	initialize(sections[0]);
	current_token = nextToken();
}

Parser::~Parser() {
	sections.clear();
}

void Parser::match(token_type type) {
    cout << current_token.value << current_token.type << " - " << type;
	if ( current_token.type == type ) {
		current_token = nextToken();
	}
	else {
		throw "Syntax Erroooooor";
	}
}

void Parser::matchID(lib_type type) {
    string value = current_token.value;
    match(ID);
    if ( find (terms[type].begin(), terms[type].end(), value) == terms[type].end() ) {
        throw "Owura, ad3n, 3de3n as3m";
    }
}

bool Parser::peekID(lib_type type) {
    if ( current_token.type != ID ) {
		return false;
	}
    if ( find (terms[type].begin(), terms[type].end(), current_token.value) == terms[type].end() ) {
        return false;
    }
    return true;
}

void Parser::expr() {
	ASTNode* root = program();
	if ( current_token.type != EOS ) {
		throw "Bossu, mistake w) ending part h) wate.";
	}
	root->parse();
	Memory::print();
}

ASTNode* Parser::calc() {
	ASTNode* node = term();
	while (current_token.type != EOS ) {
		Token op = current_token;
		if ( current_token.type == PLUS) {
			match(PLUS);
		}
		else if ( current_token.type == MINUS) {
			match(MINUS);
		}
		else {
			return node;
		}
		node = new BinOp(node, op, term());
	}
	return node;
}

ASTNode* Parser::term() {
	ASTNode* node = factor();
	while ( current_token.type == MULTIPLY || current_token.type == DIVIDE ) {
		Token op = current_token;
		if ( current_token.type == MULTIPLY ) {
			match(MULTIPLY);
		}
		else {
			match(DIVIDE);
		}
		node = new BinOp(node, op, factor());
	}
	return node;
}

ASTNode* Parser::program() {
	ASTNode *node = compound();
	return node;
}

ASTNode* Parser::compound() {
    matchID(START);
    Compound* results = new Compound;
    results->children = statement_list();
    matchID(END);
    return results;
}

vector<ASTNode*> Parser::statement_list(){
	vector<ASTNode*> results;
	results.push_back (statement());
	while ( current_token.type == DOT ) {
		match(DOT);
		results.push_back (statement());
	}
	/*if ( current_token.type == ID ) {
		throw "Owura, ad3n wo glasses ayera anaa ?";
	}*/
	return results;
}

ASTNode* Parser::statement(){
	if ( current_token.type == ID ) {
        if (peekID(END)) {
            return new Empty;
        }
		return assignment();
	}
	else {
		return new Empty;
	}
}

ASTNode* Parser::assignment(){
	Var* node = variable();
	Token token = current_token;
	match( ASSIGN );
    return new Assign ( node , token, calc());
}

Var* Parser::variable(){
	Var* node = new Var(current_token );
	match( ID);
	return node;
}

ASTNode* Parser::factor() {
	if ( current_token.type == PLUS) {
		Token op = current_token;
		match(PLUS);
		return new UnOp(op, factor());
	}
	else if ( current_token.type == MINUS) {
		Token op = current_token;
		match(MINUS);
		return new UnOp(op, factor());
	}
	else if ( current_token.type == NUMBER ) {
		Token left = current_token;
		match(NUMBER);
		return new Num(left);
	}
	else if ( current_token.type == LPAREN ) {
		match(LPAREN);
		ASTNode* result = calc();
		match(RPAREN);
		return result;
	}
	else {
		return variable();
	}
}

void Parser::loadSections(string data){
	size_t len = data.length();
	string temp;
	for ( unsigned int i =0; i<len; i++) {
		if ( data[i] == '\t' ) {
			sections.push_back(temp);
			temp.clear();
			continue;
		}
		temp += data[i];
	}
	sections.push_back(temp);
}
