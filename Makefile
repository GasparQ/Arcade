##
## Makefile for arcada makefile in /home/gaspar_q/rendu/semestre4/C++/cpp_arcade
##
## Made by Quentin Gasparotto
## Login   <gaspar_q@epitech.net>
##
## Started on  Wed Mar  9 17:39:39 2016 Quentin Gasparotto
## Last update Thu Mar 17 19:21:13 2016 Quentin Gasparotto
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
			-I./Commons/include/ \
			-g

LDFLAGS		= -ldl -L ./Commons -l_arcade_commons

$(NAME):	$(OBJS) libs games
	@echo -e "\e[32m====Arcade====\e[0m"
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

libs:
	@echo -e "\e[32m====LIBS====\e[0m"
	mkdir -p $(LIBDIR)
	make -C ./Commons/
	make -C ./Graphique/NCurses/
	make -C ./Graphique/OpenGL/
	make -C ./Graphique/SDL2/

games:
	@echo -e "\e[32m====GAMES====\e[0m"
	mkdir -p $(GAMESDIR)
	make -C ./Game/

all:	$(NAME)

clean:
	$(RM) $(OBJS)
	make clean -C ./Commons/
	make clean -C ./Game/
	make clean -C ./Graphique/NCurses/
	make clean -C ./Graphique/OpenGL/
	make clean -C ./Graphique/SDL2/

fclean:	clean
	$(RM) $(NAME)
	make fclean -C ./Game/
	make fclean -C ./Commons/
	make fclean -C ./Graphique/NCurses/
	make fclean -C ./Graphique/OpenGL
	make fclean -C ./Graphique/SDL2/

re:	fclean all

.PHONY:	all clean fclean re games libs
