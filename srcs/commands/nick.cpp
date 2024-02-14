/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:26:40 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/14 17:38:53 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_irc.hpp"

void Server::nick(Client &client, std::vector<std::string> cmd) {
	if (cmd.size() < 2)
		return (dispLogs(ERR_NEEDMOREPARAMS(client.getNickname(), concatString(cmd)), client.getSocket()));
	if (cmd.size() > 2)
		return (dispLogs(ERR_TOOMUCHPARAMS(client.getNickname(), concatString(cmd)), client.getSocket()));
	if (client.getNickname() == cmd[1])
		return (dispLogs(ERR_SAMENICKNAME(client.getNickname()), client.getSocket()));
	if (!checkCharacters(cmd[1]))
		return (dispLogs(ERR_ERRONUSENICKNAME(client.getNickname(), cmd[1]), client.getSocket()));
	if (searchNameClient(cmd[1]))
		return (dispLogs(ERR_NICKNAMEINUSE(client.getNickname(), cmd[1]), client.getSocket()));
	if (!client.getUsername().empty() && client.getNickname().empty()) {
		client.setRegistered(true);
		dispLogs(RPL_WELCOME(client.getNickname()), client.getSocket());
	}
	client.setNickname(cmd[1]);
}