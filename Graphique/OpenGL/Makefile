##
## Makefile for ncurses overload in /home/gaspar_q/rendu/semestre4/C++/cpp_arcade/Graphique/NCurses
##
## Made by Quentin Gasparotto
## Login   <gaspar_q@epitech.net>
##
## Started on  Thu Mar 10 15:53:59 2016 Quentin Gasparotto
## Last update Mon Mar 14 22:55:27 2016 Fernand Veyrier
##

NAME		=	../../lib/lib_arcade_opengl.so

RM		=	rm -f

CC		=	g++

SRCS		=	OpenGlGraph.cpp

OBJS		=	$(SRCS:.cpp=.o)

CPPFLAGS	=	-std=c++11 -W -Wall -Wextra -I ./include -I ../include -I ../../Commons/include -fPIC

LDFLAGS		=	-lGL -lGLU -L../SDL2/build/.libs/ -lSDL2 -shared -L ./libs/ -lglut -L ../../Commons -l_arcade_commons

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

all:	$(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
