##
## Makefile for arcada makefile in /home/gaspar_q/rendu/semestre4/C++/cpp_arcade
##
## Made by Quentin Gasparotto
## Login   <gaspar_q@epitech.net>
##
## Started on  Wed Mar  9 17:39:39 2016 Quentin Gasparotto
## Last update Thu Mar 10 17:35:55 2016 Quentin Gasparotto
##

NAME		=	arcade

LIBDIR		=	./lib

GAMESDIR	=	./games

CC		=	g++

RM		=	rm -f

SRCS		=	Arcade.cpp \
			main.cpp

OBJS		=	$(SRCS:.cpp=.o)

CPPFLAGS	=	-W -Wall -Wextra -std=c++11 \
			-I./Component/include/ \
			-I./Vector/include/ \
			-I./Game/include/ \
			-I./Graphique/include/ \
			-g

LDFLAGS		= -ldl

$(NAME):	$(OBJS) libs games
	@echo -e "\e[32m====Arcade====\e[0m"
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

libs:
	@echo -e "\e[32m====LIBS====\e[0m"
	mkdir -p $(LIBDIR)
	make re -C ./Graphique/NCurses/

games:
	@echo -e "\e[32m====GAMES====\e[0m"
	mkdir -p $(GAMESDIR)
	make re -C ./Game/

all:	$(NAME)

clean:
	$(RM) $(OBJS)
	make clean -C ./Game/
	make clean -C ./Graphique/NCurses/

fclean:	clean
	$(RM) $(NAME)
	make fclean -C ./Game/
	make fclean -C ./Graphique/NCurses/

re:	fclean all

.PHONY:	all clean fclean re games libs
