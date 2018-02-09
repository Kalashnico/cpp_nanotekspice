#include <iostream>
#include "parsing/Token.hpp"
#include "parsing/Parser.hpp"

int main() {
    token::TokenList tokenList;
    std::string buffer;

    buffer = parsing::Parser::openFile("test");

    tokenList.Tokenizer(buffer);

    std::vector<token::Token> token = tokenList.getList();
    for (auto i : token) {
        printf("%s\n", i.value.c_str());
    }
    return 0;
}
