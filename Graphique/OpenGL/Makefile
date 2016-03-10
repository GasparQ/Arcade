##
## Makefile for  in /home/veyrie_f/rendu/CPE_2014_lemin/OpenLemin
##
## Made by fernand veyrier
## Login   <veyrie_f@epitech.net>
##
## Started on  Thu Apr 23 15:21:49 2015 fernand veyrier
## Last update Thu Mar 10 18:32:09 2016 Fernand Veyrier
##

CC		= g++

RM		= rm -f

NAME		= OpenArcade

SRCS		= main.cpp \
              Window.cpp

OBJS		= $(SRCS:.cpp=.o)

CPPFLAGS	= -I./include -I./lib -Wall -Wextra -W -std=c++11

LDFLAGS		= -lGL -lGLU -L../SDL2/build/.libs/ -lSDL2 # -lSDL -lSDL_sound -lSDL_mixer

$(NAME):	$(OBJS)

		$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

all:		$(NAME)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
