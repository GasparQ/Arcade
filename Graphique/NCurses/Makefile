##
## Makefile for ncurses overload in /home/gaspar_q/rendu/semestre4/C++/cpp_arcade/Graphique/NCurses
##
## Made by Quentin Gasparotto
## Login   <gaspar_q@epitech.net>
##
## Started on  Thu Mar 10 15:53:59 2016 Quentin Gasparotto
## Last update Wed Mar 30 23:33:42 2016 Victor Gouet
##

NAME		=	../../lib/lib_arcade_ncurses.so

RM		=	rm -f

CC		=	g++

SRCS		=	src/Menu.cpp \
			src/NCurses.cpp \
			src/NCursesGraph.cpp \
			src/Window.cpp

OBJS		=	$(SRCS:.cpp=.o)

CPPFLAGS	=	-W -Wall -Werror -I ./include -I ../include -I ../../Commons/include -fPIC -I ./lib/include/ -g

LDFLAGS		=	-shared -L./lib -lncurses++ -lform -lform_g -lmenu -lmenu_g -lncurses -lncurses_g -lncurses++_g -lpanel -lpanel_g -L ../../Commons/ -l_arcade_commons -g

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

all:	$(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
