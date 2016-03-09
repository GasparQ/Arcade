##
## Makefile for arcada makefile in /home/gaspar_q/rendu/semestre4/C++/cpp_arcade
##
## Made by Quentin Gasparotto
## Login   <gaspar_q@epitech.net>
##
## Started on  Wed Mar  9 17:39:39 2016 Quentin Gasparotto
## Last update Wed Mar  9 17:48:53 2016 Quentin Gasparotto
##

NAME		=	arcade

CC		=	g++

RM		=	rm -f

SRCS		=	Arcade.cpp \
			main.cpp

OBJS		=	$(SRCS:.cpp=.o)

CPPFLAGS	=	-W -Wall -Wextra -std=c++11 -I./Component/include/ -I./Vector/include/ -I./Game/include/ -I./Graphique/include/

LDFLAGS		= -ldl

$(NAME):	$(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

all:	$(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all
