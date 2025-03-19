##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## make
##

SRC		= 	$(wildcard src/*.cpp)

NAME 	=	plazza

all: $(NAME)

$(NAME):	$(SRC)
	g++ $(SRC) -o $(NAME) -g

clean:
	rm -f *#
	rm -f *~

fclean: clean
	rm -f $(NAME)
	rm -f coding-style-reports.log

re:	fclean all
