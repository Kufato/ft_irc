/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:26:40 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/01 15:45:08 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

void Server::nick(Client &client, std::vector<std::string> cmd) {
	if (cmd.size() != 2 || cmd[1].empty())
		return (dispLogs(ERR_NEEDMOREPARAMS, client.getSocket()));
	if (client.getNickname() == cmd[1])
		return (dispLogs(ERR_SAMENICKNAME, client.getSocket()));
	if (checkCharacters(cmd[1]))
		return (dispLogs(ERR_ERRONEUSNICKNAME, client.getSocket()));
	if (searchNameClient(cmd[1]))
		return (dispLogs(ERR_NICKNAMEINUSE, client.getSocket()));
	if (!client.getUsername().empty() && client.getNickname().empty()) {
		client.setRegistered(true);
		dispLogs(RPL_WELCOME, client.getSocket());
	}
	client.setNickname(cmd[1]);
}