##
## Makefile for common lib makefile in /home/gaspar_q/rendu/semestre4/C++/cpp_arcade/Commons
##
## Made by Quentin Gasparotto
## Login   <gaspar_q@epitech.net>
##
## Started on  Sun Mar 13 17:06:59 2016 Quentin Gasparotto
## Last update Fri Mar 18 14:06:31 2016 Victor Gouet
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
		Astar.cpp \
		Chrono.cpp

OBJS	=	$(SRCS:.cpp=.o)

CPPFLAGS	=	-W -Wall -Wextra -std=c++11 -I ./include -fPIC -I ./HighScore/include/ -I ./

$(NAME):	$(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

all:	$(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all
