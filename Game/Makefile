##
## Makefile for games makefile in /home/gaspar_q/rendu/semestre4/C++/cpp_arcade/Game
##
## Made by Quentin Gasparotto
## Login   <gaspar_q@epitech.net>
##
## Started on  Thu Mar 10 16:28:26 2016 Quentin Gasparotto
## Last update Thu Mar 17 20:32:49 2016 Victor Gouet
##

CC	=	g++ -g

RM	=	rm -f

PREFIX	=	../games/lib_arcade_

SNAKE	=	$(PREFIX)snake.so

PACMAN	=	$(PREFIX)pacman.so

SNAKESRCS	=	src/Snake.cpp

SNAKEOBJS	=	$(SNAKESRCS:.cpp=.o)

PACMANSRCS	=	src/Pacman.cpp		\
			src/PacmanCharacter.cpp	\
			src/Ghost.cpp		\
			src/PacmanGame.cpp

PACMANOBJS	=	$(PACMANSRCS:.cpp=.o)

CPPFLAGS	=	-W -Wall -Wextra -fPIC -shared --std=c++11 \
			-I ./include/ \
			-I ../../Commons/include \
			-Wl,--no-undefined

LDFLAGS		=	-shared -Wl,--no-undefined -L ../Commons/ -l_arcade_commons

all:	$(SNAKE) $(PACMAN)

$(SNAKE):	$(SNAKEOBJS)
	$(CC) -o $(SNAKE) $(SNAKEOBJS) $(LDFLAGS)

$(PACMAN):	$(PACMANOBJS)
	$(CC) -o $(PACMAN) $(PACMANOBJS) $(LDFLAGS)

clean:
	$(RM) $(SNAKEOBJS)
	$(RM) $(PACMANOBJS)

fclean:	clean
	$(RM) $(SNAKE)
	$(RM) $(PACMAN)

re:	fclean all
