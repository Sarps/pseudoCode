#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

#include "Tokenizer.h"
#include "Library.h"
#include "ASTNodes.h"

using namespace std;

class Parser : public Tokenizer, public Library
{
    public:
        Parser(string data);
        ~Parser();
        void expr();
        ASTNode* calc();
        ASTNode* term();
        ASTNode* program();
        ASTNode* note_section();
        ASTNode* main_section();
        ASTNode* topic_section();
        ASTNode* verb_list();
        ASTNode* noun_list();
        ASTNode* block();
        ASTNode* compound();
        vector<ASTNode*> statement_list();
        ASTNode* statement();
        ASTNode* assignment();
        Var* variable();
        ASTNode* factor();
        float number();

    protected:
        void loadSections(string data);
        void match(token_type type);
        void matchID(lib_type type);
        bool peekID(lib_type type);

    private:
    Token current_token;
     vector<string> sections;
};

#endif // PARSER_H
