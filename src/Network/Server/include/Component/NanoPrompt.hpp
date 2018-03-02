//
// Created by Nicolas Guerin on 12/02/2018.
//

#ifndef NANOPROMPT_HPP
#define NANOPROMPT_HPP

#include <map>
#include <Circuit/Circuit.hpp>

class NanoPrompt {
	private:
		std::map<std::string, void (NanoPrompt::*)(std::string)> _cmd;
                parsing::Circuit _parser;

	public:
		NanoPrompt(const parsing::Circuit &parser);
		virtual ~NanoPrompt();

		void 	run();
		void	display(std::string string);
		void	assign(std::string string);
		void	simulate(std::string string);
		void	loop(std::string string);
		void	dump(std::string string);
		void	cat(std::string string);
};


#endif //NANOPROMPT_HPP
