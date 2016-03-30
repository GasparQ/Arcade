##
## Makefile for ncurses overload in /home/gaspar_q/rendu/semestre4/C++/cpp_arcade/Graphique/NCurses
##
## Made by Quentin Gasparotto
## Login   <gaspar_q@epitech.net>
##
## Started on  Thu Mar 10 15:53:59 2016 Quentin Gasparotto
## Last update Wed Mar 30 21:41:07 2016 Fernand Veyrier
##

NAME		=	../../lib/lib_arcade_opengl.so

RM		=	rm -f

CC		=	g++

SRCS		=	OpenGlGraph.cpp

OBJS		=	$(SRCS:.cpp=.o)

CPPFLAGS	=	-std=c++11 -W -Wall -Wextra -I ./include -I ../include -I ../../Commons/include -fPIC

#LDFLAGS		=	-lGL -lGLU -L ./libs/ -lglut -L../SDL2/build/.libs/ -lSDL2 -L../SDL2_mixer/ -lSDL_mixer -shared -L ../../Commons -l_arcade_commons
LDFLAGS		=	-lGL -lGLU -L ./libs/ -lglut -Wl,-rpath,./Graphique/SDL2_mixer -L ../SDL2_mixer -L ../SDL2 -lSDL2 -lSDL2_mixer ../SDL2_mixer/libfluidsynth.so.1 -shared -L ../../Commons -l_arcade_commons

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

all:	$(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
