/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:26:40 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/12 14:32:09 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_irc.hpp"

void Server::user(Client &client, std::vector<std::string> cmd) {
	if (client.isRegistered() == true)
		return (dispLogs(ERR_ALREADYREGISTERED(client.getNickname()), client.getSocket()));
	if (cmd.size() < 2)
		return (dispLogs(ERR_NEEDMOREPARAMS(client.getNickname(), concatString(cmd)), client.getSocket()));
	if (cmd.size() > 2)
		return (dispLogs(ERR_TOOMUCHPARAMS(client.getNickname(), concatString(cmd)), client.getSocket()));
	if (!checkCharacters(cmd[1]))
		return (dispLogs(ERR_BADCHAR(client.getNickname(), cmd[1]), client.getSocket()));
	if (clientExist(cmd[1]))
		return (dispLogs(ERR_ERRONUSEUSERNAME(client.getNickname(), cmd[1]), client.getSocket()));
	if (!client.getNickname().empty() && client.getUsername().empty()) {
		client.setRegistered(true);
		dispLogs(RPL_WELCOME(client.getNickname()), client.getSocket());
	}
	client.setUsername(cmd[1]);
}