/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:26:45 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/01 10:27:23 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

std::string Server::help(void) {
	return ("Here is the list of all available commands :\n \
			PASS : use it when you need to log and enter the password\n \
			NICK : set a new NickName\n \
			USER : set a new UserName\n \
			KICK : eject a client from the channel\n \
			INVITE : invite a client to a channel\n \
			TOPIC : change or view the channel topic\n \
			PRIVMSG : send a private message\n \
			JOIN : joins a channel\n \
			MODE : change the channel's mode\n 	\
			i: set/remove invite only channel\n 	\
			t: set/remove the restrictions of the TOPIC command to channel operators\n 	\
			k: set/remove the channel key (password)\n 	\
			o: give/take channel operator privilege\n 	\
			l: set/remove the user limit to channel\n");
}