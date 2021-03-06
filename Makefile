
##
## EPITECH PROJECT, 2018
## NanoTekSpice
## File description:
## NanoTekSpice
##

NAME	= nanotekspice

RM	= rm -f

CC	= g++

CFLAGS	= -I include -std=c++1z
CFLAGS	+= -Wall -Wextra -W -Wshadow


SRC	= src/main.cpp                          \
	src/Component/AComponent.cpp           \
	src/Component/Component4000.cpp      \
	src/Component/Component4001.cpp       \
	src/Component/Component4002.cpp      \
	src/Component/Component4011.cpp       \
	src/Component/Component4023.cpp      \
	src/Component/Component4025.cpp      \
	src/Component/Component4030.cpp       \
	src/Component/Component4069.cpp       \
	src/Component/Component4071.cpp       \
	src/Component/Component4081.cpp       \
	src/Component/ComponentClock.cpp      \
	src/Component/ComponentInput.cpp      \
	src/Component/ComponentOutput.cpp      \
	src/Component/ComponentTrue.cpp		\
	src/Component/ComponentFalse.cpp	\
	src/Gates.cpp                         \
	src/NanoPrompt.cpp                     \
	src/ComponentGenerator.cpp                     \
	src/Circuit/Circuit.cpp

OBJ	= $(SRC:.cpp=.o)

BOLD	= "\033[1m"

RED     = "\033[31m"

GREEN	= "\033[32m"

YELLOW	= "\033[33;1m"

RESET	= "\033[0m"

OKTEXT	= \r"$(BOLD)$(GREEN)"\342\234\224"$(RESET)"

KOTEXT	= \r"$(BOLD)$(RED)"\342\234\230"$(RESET)"

ARROW	= "$(BOLD)$(YELLOW)"\342\206\222"$(RESET)"

COND	= printf "$(OKTEXT)\n"

$(NAME): $(OBJ)
	@printf "\n$(KOTEXT) Binary generated : "$(BOLD)"$(NAME)"$(RESET)""
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS) && $(COND)

%.o: %.cpp
	@printf "$(KOTEXT) %s $(ARROW) %s" "$<" "$@"
	@$(CC) -o $@ $< -c $(CFLAGS) && $(COND)

all: $(NAME)

server:
	make -C src/Network/Server

clean:
	@printf "$(KOTEXT) Cleaning objects"
	@$(RM) $(OBJ) && $(COND)

fclean: clean
	@printf "$(KOTEXT) Cleaning binary"
	@$(RM) $(NAME) && $(COND)

re: fclean _newline all

_newline:
	@printf "\n"

.PHONY: all install uninstall clean fclean re _newline
