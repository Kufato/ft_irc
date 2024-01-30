# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/24 11:26:17 by axcallet          #+#    #+#              #
#    Updated: 2024/01/30 11:02:00 by axcallet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

########## ARGUMENTS ##########

NAME		= ircserv
CC			= c++
CFLAGS		= -Wall -Werror -Wextra -std=c++98 -g3

########## SOURCES ##########

OBJ_DIR		= obj
OBJ			= $(SRC:.cpp=.o)
SRC			= main.cpp	\
			Client.cpp	\
			Server.cpp

########## RULES ##########

all: title $(NAME)

$(NAME): $(OBJ)
	@echo $(_GREEN)- Compiling $(OBJ) $(END)
	@$(CC) $(CFLAGS) $(OBJ) -o $@

%.o: %.cpp
	@echo $(_CYAN)- Compiling $<$(END)
	@$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@echo $(_YELLOW)- Cleaning $(OBJ)$(END)
	@rm -f $(OBJ)

fclean: clean
	@echo $(_RED)- Cleaning $(NAME)$(END)
	@rm -f $(NAME)

re: fclean all

title :
	@echo $(_RED)''
	@echo '             ________________________'
	@echo '             ____  _/__  __ \_  ____/'
	@echo '              __  / __  /_/ /  /'
	@echo '             __/ /  _  _, _// /___'
	@echo '             /___/  /_/ |_| \____/'
	@echo '              by Gauth and Axel'$(END)
	@echo ''

.PHONY: all fclean clean re

########## COLORS ##########

_END		="\033[0m"
_RED		="\033[0;31m"
_GREEN		="\033[0;32m"
_YELLOW		="\033[0;33m"
_CYAN		="\033[0;36m"
_PURPLE		="\033[0;35m"