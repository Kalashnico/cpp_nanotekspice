#include <iostream>
<<<<<<< HEAD
#include "Component/Component4001.hpp"
#include "Component/ComponentInput.hpp"
#include "Component/ComponentOutput.hpp"

int main() {
	nts::Component4001 c1("c1");
	nts::ComponentInput in1("in1", nts::Tristate::FALSE);
	nts::ComponentInput in2("in2", nts::Tristate::TRUE);
	nts::ComponentInput in3("in3", nts::Tristate::FALSE);
	nts::ComponentInput in4("in4", nts::Tristate::FALSE);
	nts::ComponentOutput out("output");

	c1.setLink(1, in1, 1);
	c1.setLink(2, in2, 1);
	c1.setLink(4, in3, 1);
	c1.setLink(5, in4, 1);

	c1.setLink(3, c1, 8);
	c1.setLink(6, c1, 9);

	out.setLink(1, c1, 10);
	out.compute();
//	c1.dump();
//	in1.dump();
//	in2.dump();
//	in3.dump();
//	in4.dump();
//	c1.dump();
//	out.dump();
	return 0;
=======
#include <histedit.h>
#include "parsing/Token.hpp"
#include "parsing/Parser.hpp"

int main() {
    token::TokenList tokenList;
    std::string buffer;

    buffer = parsing::Parser::openFile("and.nts");

    tokenList.Tokenizer(buffer);

    std::vector<token::Token> token = tokenList.getList();
    for (auto i : token) {
        printf("%s\n", i.value.c_str());
    }
    return 0;
>>>>>>> e833dcbd4c6014a02d0e81e96da17d845aadcdb6
}