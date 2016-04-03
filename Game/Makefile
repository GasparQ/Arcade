##
## Makefile for games makefile in /home/gaspar_q/rendu/semestre4/C++/cpp_arcade/Game
##
## Made by Quentin Gasparotto
## Login   <gaspar_q@epitech.net>
##
## Started on  Thu Mar 10 16:28:26 2016 Quentin Gasparotto
## Last update Sun Apr  3 11:41:24 2016 Victor Gouet
##

CC	=	g++

RM	=	rm -f

PREFIX	=	../games/lib_arcade_

SNAKE	=	$(PREFIX)snake.so

PACMAN	=	$(PREFIX)pacman.so

CENTIPEDE	=	$(PREFIX)centipede.so

SNAKESRCS	=	src/Snake.cpp

SNAKEOBJS	=	$(SNAKESRCS:.cpp=.o)

CENTIPEDESRCS	=	src/USSEnterprise.cpp \
			src/Centipede.cpp \
			src/CentipedeGame.cpp \

CENTIPEDEOBJS	=	$(CENTIPEDESRCS:.cpp=.o)

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

## Necessary if using SDL_mixer
#LDFLAGS	+=	-Wl,-rpath,./Graphique/SDL2_mixer -L ../Graphique/SDL2_mixer -L ../SDL2 -lSDL2 -lSDL2_mixer ../Graphique/SDL2_mixer/libfluidsynth.so.1

all:	$(SNAKE) $(PACMAN) $(CENTIPEDE)

$(SNAKE):	$(SNAKEOBJS)
	$(CC) -o $(SNAKE) $(SNAKEOBJS) $(LDFLAGS)

$(PACMAN):	$(PACMANOBJS)
	$(CC) -o $(PACMAN) $(PACMANOBJS) $(LDFLAGS)

$(CENTIPEDE):	$(CENTIPEDEOBJS)
	$(CC) -o $(CENTIPEDE) $(CENTIPEDEOBJS) $(LDFLAGS)

clean:
	$(RM) $(SNAKEOBJS)
	$(RM) $(PACMANOBJS)
	$(RM) $(CENTIPEDEOBJS)

fclean:	clean
	$(RM) $(SNAKE)
	$(RM) $(PACMAN)
	$(RM) $(CENTIPEDE)

re:	fclean all
