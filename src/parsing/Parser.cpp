//
// Created by Nicolas Guerin on 02/02/2018.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include "Parser.hpp"

namespace parsing {
    /**
     * Constructor & Destructor
     */

    Parser::Parser() : _graph({{token::ROOT, ""}, {}}), _cursor(0)
    {

    }

    Parser::~Parser()
    {

    }

    /**
     * Member Functions
     */

    std::string Parser::openFile(const std::string &fileName)
    {
        std::ifstream file(fileName);
        std::stringstream buffer;

        if (file.good()) {
        buffer << file.rdbuf();
        }
        else
            throw std::invalid_argument("Error: File doesn't exist");
        file.close();
        return buffer.str();
    }

    void Parser::createGraph(std::vector<token::Token> &token)
    {
        while (token.at(_cursor).type != token::KW_EOF) {
            if (token.at(_cursor).type == token::P_HASHTAG)
                _cursor++;
            else if (token.at(_cursor).type == token::P_DOT)
                parseCategory(token);
        }
    }

    void Parser::parseCategory(std::vector<token::Token> &token)
    {
        _cursor++;
        _graph.child.push_back({token::CATEGORIE, "category", {}});
        if (token.at(_cursor).value == "chipsets") {
            parseChipsets(token);
        }
        else if (token.at(_cursor).value == "links") {
            parseLinks(token);
        }
        else
            throw std::invalid_argument("Error: Bad input");
    }

    void Parser::parseChipsets(std::vector<token::Token> &token) {

    }

    void Parser::parseLinks(std::vector<token::Token> &token) {

    }

    /**
     * Getter & Setter
     */

    const Graph &Parser::getGraph() const {
        return _graph;
    }

    const token::Token &Parser::getToken() const
    {
        return _graph.token;
    }

    size_t Parser::getCursor() const
    {
        return _cursor;
    }


}