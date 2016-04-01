##
## Makefile for sdl lib makefile in /home/gaspar_q/rendu/semestre4/C++/cpp_arcade/Graphique/SDL2
##
## Made by Quentin Gasparotto
## Login   <gaspar_q@epitech.net>
##
## Started on  Sun Mar 13 16:17:19 2016 Quentin Gasparotto
## Last update Fri Apr  1 17:32:47 2016 Fernand Veyrier
##

NAME		=	../../lib/lib_arcade_sdl2.so

CC		=	g++

RM		=	rm -f

SRC		=	src/SDLGraph.cpp

OBJ		=	$(SRC:.cpp=.o)

CPPFLAGS	=	-W -Wall -Wextra $(HEADER) -std=c++11 -fPIC -g

HEADER		=	-I./include -I ../../Commons/include

LDFLAGS		=	-L ./build/.libs/ -lSDL2 -lSDL2_ttf -shared -L ../../Commons -l_arcade_commons

## Necessary if using SDL_mixer
LDFLAGS	+=		-Wl,-rpath,./Graphique/SDL2_mixer -L ../SDL2_mixer -L ./ -lSDL2 -lSDL2_mixer ../SDL2_mixer/libfluidsynth.so.1


$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

all:	$(NAME)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all
