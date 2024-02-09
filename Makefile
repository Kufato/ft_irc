# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/24 11:26:17 by axcallet          #+#    #+#              #
#    Updated: 2024/02/09 17:22:22 by axcallet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

########## ARGUMENTS ##########

NAME		= ircserv
CC			= c++
CFLAGS		= -Wall -Werror -Wextra -std=c++98 -g3
INC			= -I inc/

########## SOURCES ##########

OBJ_DIR		= obj
OBJ			= $(SRC:.cpp=.o)
SRC			= ./srcs/Channel.cpp			\
			./srcs/Client.cpp				\
			./srcs/main.cpp				\
			./srcs/Server.cpp				\
			./srcs/utils.cpp				\
			./srcs/signals.cpp				\
			./srcs/commands/help.cpp		\
			./srcs/commands/invite.cpp	\
			./srcs/commands/join.cpp		\
			./srcs/commands/kick.cpp		\
			./srcs/commands/mode.cpp		\
			./srcs/commands/nick.cpp		\
			./srcs/commands/pass.cpp		\
			./srcs/commands/privmsg.cpp	\
			./srcs/commands/topic.cpp		\
			./srcs/commands/user.cpp

########## RULES ##########

all: title $(NAME)

$(NAME): $(OBJ)
	@echo $(_GREEN)- Compiling $(OBJ) $(END)
	@$(CC) $(CFLAGS) $(INC) $(OBJ) -o $@

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
	@echo $(END)''
	@echo 'Voici notre Intrepide Rat Cuisto'
	@echo '⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡤⠖⠂⠀⠀⠀'
	@echo '⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣄⣮⣠⠦⠄⡀⠀⠀⠀⠀⠀⢀⣤⠟⣡⡴⠒⠈⠀⠀'
	@echo '⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⣿⡿⠛⠛⢷⣶⣮⢯⡿⣽⣦⣤⣜⡿⢿⠦⠀⠀⠀⠀⠀'
	@echo '⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣐⣿⣿⠀⣴⣦⢼⣼⣻⣿⣿⣿⣿⣿⡝⡼⢩⠆⠀⠀⠀⠀⠀'
	@echo '⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⠖⠶⠵⣪⣕⣺⣿⣿⣿⣧⣽⣾⣾⣶⣿⣿⣽⣿⣿⣿⣿⡖⠇⠊⣠⠀⠀⠀⠀'
	@echo '⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⢍⠢⡑⠤⣉⠥⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⠀⠀⡸⢡⡣⢤⣀⠄'
	@echo '⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠷⡼⣰⢢⣏⣿⣿⣿⣿⣿⣿⣿⣟⡿⠿⠛⠟⠁⠀⠀⢫⡜⠃⢈⢰⠛⣂⠄'
	@echo '⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢦⣿⣿⣿⣿⣿⣿⣿⣿⣮⣛⣡⡀⣀⠀⠀⢀⣸⣷⣬⠆⠉⠀⠀⠀'
	@echo '⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⣢⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣻⢷⣳⣛⣿⣿⡯⠃⠀⠀⠀⠀⠀'
	@echo '⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢢⣾⣿⣿⣿⣿⣿⣿⣿⢯⣟⣷⢯⢿⣹⣟⣾⣿⡿⢿⠑⠀⠀⠀⠀⠀⠀⠀'
	@echo '⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢂⣶⣿⣿⣿⣿⣿⣿⣿⣿⣯⣟⣿⢫⣟⣻⡞⣿⠻⠅⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀'
	@echo '⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡠⢳⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⢯⡧⢉⠆⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀'
	@echo '⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⢾⠁⡃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀'
	@echo '⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⣴⣿⣿⣿⣿⣿⣿⣿⣿⣯⡙⣿⣿⣿⡻⡯⡀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀'
	@echo '⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡎⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⢡⡇⣿⣯⡷⣣⠓⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀'
	@echo '⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣷⣿⣿⣿⣿⣿⣿⣿⣿⡿⣟⣿⡿⢯⡷⢳⢤⠏⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀'
	@echo '⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⣎⣿⣿⣿⣿⣿⣿⣿⡿⣟⢧⣿⣽⡳⣻⡅⢮⢗⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀'
	@echo '⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⡗⡯⣟⡼⣽⣓⢽⣜⣋⡜⠚⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀'
	@echo '⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⢹⣿⣿⣿⣿⣯⣯⢧⡿⢺⡿⣽⣞⣯⡽⣎⡝⠄⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀'
	@echo '⠀⠀⠀⡀⢀⠠⡄⣤⣴⣲⠶⠷⠿⣿⣿⣿⣿⣷⣻⣜⣹⣿⣿⣻⣾⣯⣿⣿⣿⠪⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀'
	@echo '⢴⡠⠵⠒⠚⠉⠉⠈⠁⠀⠀⠀⠐⠈⠻⣿⣿⣿⣿⣿⣿⡿⠳⠿⠿⠿⠿⣻⣉⣪⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀'
	@echo '⠁⠒⠡⠄⠐⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠊⠛⢭⣹⢆⣩⠀⠈⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀'
	@echo '              by Gauth, Bob and Axel'$(END)
	@echo ''

.PHONY: all fclean clean re

########## COLORS ##########

_END		="\033[0m"
_RED		="\033[0;31m"
_GREEN		="\033[0;32m"
_YELLOW		="\033[0;33m"
_CYAN		="\033[0;36m"
_PURPLE		="\033[0;35m"
