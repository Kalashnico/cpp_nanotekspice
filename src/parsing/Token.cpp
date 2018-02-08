//
// Created by Nicolas Guerin on 02/02/2018.
//

#include "Token.hpp"
#include "Parser.hpp"


namespace token {
/**
 * Constructor & Destructor
 */

    TokenList::TokenList() : _list(), _cursor(0)
    {
    }

    TokenList::~TokenList()
    {
    }

/**
 * Member Functions
 */

    void TokenList::Tokenizer(const std::string &buffer)
    {
        std::string tmpValue = "";

        while (_cursor < buffer.size()) {
            if (std::isspace(buffer.at(_cursor))) {
                _cursor++;
            }
            else if (buffer.at(_cursor) == '#') {
                while (buffer.at(_cursor) != '\n') {
                    _cursor++;
                }
                this->_list.push_back({P_HASHTAG, "#"});
                _cursor++;
            }

            else if (buffer.at(_cursor) == '.') {
                this->_list.push_back({token::P_DOT, "."});
                _cursor++;
                if (!isalpha(buffer.at(_cursor)))
                    throw std::invalid_argument("Error: File format isn't good");
                while (isalpha(buffer.at(_cursor))) {
                    tmpValue += buffer.at(_cursor);
                    _cursor++;
                }
                this->_list.push_back({token::KW_ID, tmpValue});
            }

            else if (buffer.at(_cursor) == ':') {
                this->_list.push_back({token::P_COLON, ":"});
                _cursor++;
            }

            else if (isalpha(buffer.at(_cursor))) {
                while (isalpha(buffer.at(_cursor))) {
                    tmpValue += buffer.at(_cursor);
                    _cursor++;
                }
                if (isGate(tmpValue).type != token::UNDEFINED) {
                    this->_list.push_back(isGate(tmpValue));
                }
                else if (isDeclaration(tmpValue).type != token::UNDEFINED) {
                    this->_list.push_back(isDeclaration(tmpValue));
                }
                else
                    this->_list.push_back({KW_ID, tmpValue});
            }
            else if (isdigit(buffer.at(_cursor))) {
                while (_cursor < buffer.size() && isdigit(buffer.at(_cursor))) {
                    tmpValue += buffer.at(_cursor);
                    _cursor++;
                }
                if (getLastToken() == token::P_COLON) {
                    this->_list.push_back({token::V_NUMBER, tmpValue});
                }
                else
                    this->_list.push_back({token::KW_ID, tmpValue});
            }
            else
                _cursor++;
            tmpValue.clear();
        }
        this->_list.push_back({KW_EOF, "eof"});
    }

    token::Token TokenList::isGate(const std::string &str)
    {

        //TODO Transformer en std::array

        if (str == "and")
            return {token::G_AND, "and"};
        else if (str == "nand")
            return {token::G_NAND, "nand"};
        else if (str == "or")
            return {token::G_OR, "or"};
        else if (str == "nor")
            return {token::G_NOR, "nor"};
        else if (str == "xand")
            return {token::G_XAND, "xand"};
        else if (str == "inverter")
            return {token::G_INVERTER, "inverter"};
        else
            return {token::UNDEFINED, ""};
    }


    token::Token TokenList::isDeclaration(const std::string &str) {
        if (str == "input")
            return {token::KW_INPUT, "input"};
        else if (str == "output")
            return {token::KW_OUTPUT, "output"};
        else
            return {token::UNDEFINED, ""};
    }

    token::TokenType TokenList::getLastToken() {
        return _list.at(_list.size() - 1).type;
    }

/**
 * Getter
 */
    const std::vector<token::Token> &TokenList::getList() const {
        return _list;
    }

}