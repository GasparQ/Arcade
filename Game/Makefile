##
## Makefile for games makefile in /home/gaspar_q/rendu/semestre4/C++/cpp_arcade/Game
##
## Made by Quentin Gasparotto
## Login   <gaspar_q@epitech.net>
##
## Started on  Thu Mar 10 16:28:26 2016 Quentin Gasparotto
## Last update Thu Mar 10 18:25:26 2016 Quentin Gasparotto
##

CC	=	g++

RM	=	rm -f

PREFIX	=	../games/lib_arcade_

COMMON	=	../Vector/src/Vector2.cpp \
		../Component/src/AComponent.cpp \
		../Component/src/GameComponent.cpp \
		../Component/src/UIComponent.cpp \

SNAKE	=	$(PREFIX)snake.so

SNAKESRCS	=	$(COMMON) \
			src/Snake.cpp

SNAKEOBJS	=	$(SNAKESRCS:.cpp=.o)

CPPFLAGS	=	-W -Wall -Wextra -fPIC \
			-I ./include/ \
			-I ../Vector/include \
			-I ../Component/include/

LDFLAGS		=	-shared

$(SNAKE):	$(SNAKEOBJS)
	$(CC) -o $(SNAKE) $(SNAKEOBJS) $(LDFLAGS)

all:	$(SNAKE)

clean:
	$(RM) $(SNAKEOBJS)

fclean:	clean
	$(RM) $(SNAKE)

re:	fclean all
