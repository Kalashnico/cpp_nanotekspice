//
// Created by Nicolas Guerin on 02/02/2018.
//

#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <vector>

namespace token {
    enum TokenType {
        UNDEFINED,

        //For Graph
        ROOT,
        CATEGORIE,
        DECLARATION,
        ASSIGNATION,

        //For Lexer
        KW_EOF,
        KW_ID,
        KW_INPUT,
        KW_OUTPUT,
        G_AND,
        G_OR,
        G_NAND,
        G_NOR,
        G_XAND,
        G_INVERTER,
        P_DOT,
        P_HASHTAG,
        P_COLON,
        V_NUMBER,
    };

    struct Token {
        TokenType type;
        std::string value;
    };

    class TokenList {
    private:
        std::vector<token::Token>   _list;
        std::size_t                 _cursor;

    public:
        //Constructor & Destructor
        TokenList();
        virtual ~TokenList();

        //Member Function
        void    Tokenizer(const std::string &buffer);
        token::Token    isGate(const std::string &str);
        token::Token    isDeclaration(const std::string &str);
        token::TokenType   getLastToken();
        //Getter & Setter
        const std::vector<token::Token> &getList() const;
    };
}

#endif //TOKEN_HPP
