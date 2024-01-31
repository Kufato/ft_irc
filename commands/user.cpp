/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:26:40 by axcallet          #+#    #+#             */
/*   Updated: 2024/01/31 17:14:02 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

static bool	checkCharacters(std::string nickname) {
	std::string allowedChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_";
	
	if (nickname.find_first_not_of(allowedChars) != std::string::npos)
		return (false);
	return (true);
}

void Server::user(Client &client, std::vector<std::string> cmd) {
	// if (client.isRegistered() == true)
	// 	return (dispLogs(ERR_ALREADYREGISTRED, client.getSocket()));
	if (cmd.size() < 2 || cmd[1].empty())
		return (dispLogs(ERR_NEEDMOREPARAMS, client.getSocket()));
	if (cmd.size() > 2)
		return (dispLogs(ERR_TOOMANYPARAMS, client.getSocket()));
	if (checkCharacters(cmd[1]))
		return (dispLogs(ERR_ERRONEUSNICKNAME, client.getSocket()));
	if (searchNameClient(cmd[1]))
		return (dispLogs(ERR_NICKNAMEINUSE, client.getSocket()));
	if (!client.getNickname().empty() && client.getUsername().empty()) {
		client.setRegistered(true);
		dispLogs(RPL_WELCOME, client.getSocket());
	}
	client.setUsername(cmd[1]);
}