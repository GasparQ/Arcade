##
## Makefile for common lib makefile in /home/gaspar_q/rendu/semestre4/C++/cpp_arcade/Commons
##
## Made by Quentin Gasparotto
## Login   <gaspar_q@epitech.net>
##
## Started on  Sun Mar 13 17:06:59 2016 Quentin Gasparotto
## Last update Sun Mar 13 17:52:21 2016 Quentin Gasparotto
##

NAME	=	lib_arcade_commons.a

CC	=	g++

RM	=	rm -f

SRCS	=	src/AComponent.cpp	\
		src/GameComponent.cpp	\
		src/UIComponent.cpp	\
		src/Vector2.cpp \
		HighScore/src/LoadHighScore.cpp

OBJS	=	$(SRCS:.cpp=.o)

CPPFLAGS	=	-W -Wall -Wextra -std=c++11 -I ./include -fPIC -I ./HighScore/include/

$(NAME):	$(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

all:	$(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all
