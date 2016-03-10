##
## Makefile for ncurses overload in /home/gaspar_q/rendu/semestre4/C++/cpp_arcade/Graphique/NCurses
##
## Made by Quentin Gasparotto
## Login   <gaspar_q@epitech.net>
##
## Started on  Thu Mar 10 15:53:59 2016 Quentin Gasparotto
## Last update Thu Mar 10 16:09:54 2016 Quentin Gasparotto
##

NAME		=	../../lib/lib_arcade_ncurses.so

RM		=	rm -f

CC		=	g++

SRCS		=	src/Menu.cpp \
			src/NCurses.cpp \
			src/NCursesGraph.cpp \
			src/Window.cpp \
			../../Vector/src/Vector2.cpp \
			../../Component/src/AComponent.cpp \
			../../Component/src/GameComponent.cpp \
			../../Component/src/UIComponent.cpp

OBJS		=	$(SRCS:.cpp=.o)

CPPFLAGS	=	-W -Wall -Werror -I ./include -I ../include -I ../../Vector/include -I ../../Component/include -fPIC

LDFLAGS		=	-lncurses -shared

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

all:	$(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
