##
## Makefile for common lib makefile in /home/gaspar_q/rendu/semestre4/C++/cpp_arcade/Commons
##
## Made by Quentin Gasparotto
## Login   <gaspar_q@epitech.net>
##
## Started on  Sun Mar 13 17:06:59 2016 Quentin Gasparotto
## Last update Wed Mar 30 21:01:05 2016 Fernand Veyrier
##

NAME	=	lib_arcade_commons.a

CC	=	g++

RM	=	rm -f

SRCS	=	src/AComponent.cpp		\
		src/AnimationComponent.cpp	\
		src/GameComponent.cpp		\
		src/UIComponent.cpp		\
		src/HighScoreComponent.cpp	\
		src/LoadHighScore.cpp \
		src/DualTextComponent.cpp \
		Sound.cpp \
		AudioComponent.cpp

OBJS	=	$(SRCS:.cpp=.o)

CPPFLAGS	=	-W -Wall -Wextra -Wnon-virtual-dtor -std=c++11 -I ./include -fPIC -I ./HighScore/include/ -I ./
                #-L ./ -L ../Graphique/SDL2/build/.libs/ -lSDL2 -Wl,rpath,../Graphique/SDL2_mixer -L ../Graphique/SDL2_mixer/ -lSDL2_mixer


$(NAME):	$(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

all:	$(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all
