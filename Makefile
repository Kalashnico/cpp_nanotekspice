##
## Makefile for dante in /home/cutill-v/delivery/AI/dante/astar
##
## Made by Victor Cutillas
## Login   <victor.cutillas@epitech.eu>
##
## Started on  Tue Apr 11 01:03:10 2017 Victor Cutillas
## Last update Fri Jun  9 14:03:39 2017 Victor Cutillas
##

NAME	= nanotekspice

## MAN	= man/42sh.1.gz

RM	= rm -f

CC	= g++ -std=c++1z

CFLAGS	= -I include -std=c++1z
CFLAGS	+= -Wall -Wextra -W


SRC	= src/main.cpp                          \
      src/Component/DefaultComponent.cpp    \
      src/Component/Component4001.cpp       \
      src/Component/ComponentInput.cpp      \
      src/Component/ComponentOutput.cpp      \
      src/Gates.cpp                         \


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

install: all
	@printf "$(KOTEXT) Installing binary and man documentation"
	@cp $(NAME) /usr/bin && \
	cp $(MAN) /usr/share/man/man1/ && \
	$(COND)

uninstall:
	@printf "$(KOTEXT) Uninstalling binary and man documentation"
	@rm -f /usr/bin/$(NAME) && \
	rm -f /usr/share/man/man1/$(notdir $(MAN)) && \
	$(COND)

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
