/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:26:40 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/08 14:50:55 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_irc.hpp"

void Server::user(Client &client, std::vector<std::string> cmd) {
	// if (client.isRegistered() == true)
	// 	return (dispLogs(ERR_ALREADYREGISTRED, client.getSocket()));
	if (cmd.size() < 2 || cmd[1].empty())
		return (dispLogs(ERR_NEEDMOREPARAMS, client.getSocket(), NULL));
	if (cmd.size() > 2)
		return (dispLogs(ERR_TOOMANYPARAMS, client.getSocket(), NULL));
	if (!checkCharacters(cmd[1]))
		return (dispLogs(ERR_ERRONEUSNICKNAME, client.getSocket(), NULL));
	if (clientExist(cmd[1]))
		return (dispLogs(ERR_NICKNAMEINUSE, client.getSocket(), NULL));
	if (!client.getNickname().empty() && client.getUsername().empty()) {
		client.setRegistered(true);
		dispLogs(RPL_WELCOME, client.getSocket(), NULL);
	}
	client.setUsername(cmd[1]);
}