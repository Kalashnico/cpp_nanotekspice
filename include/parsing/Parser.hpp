//m
// Created by Nicolas Guerin on 02/02/2018.
//

#ifndef PARSER_HPP
#define PARSER_HPP


#include "parsing/Token.hpp"

namespace parsing {
    struct Graph {
    token::Token    token;
    std::string value;
    std::vector<parsing::Graph> child;
    };

    class Parser {
    private:
        Graph   _graph;
        std::size_t     _cursor;
        Graph _tmpChild;

    public:
        //Constructor & Destructor
        Parser();
        virtual ~Parser();

        //Member Functions
        static std::string openFile(const std::string &fileName);
        void    createGraph(std::vector<token::Token> &token);
        void    parseCategory(std::vector<token::Token> &token);
        void    parseChipsets(std::vector<token::Token> &token);
        void    parseLinks(std::vector<token::Token> &token);

        //Getter & Setter
        const Graph &getGraph() const;
        const token::Token &getToken() const;
        size_t getCursor() const;
    };
}

#endif //PARSER_HPP
