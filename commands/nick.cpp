/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:26:40 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/02 15:32:10 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

void Server::nick(Client &client, std::vector<std::string> cmd) {
	if (cmd.size() != 2 || cmd[1].empty())
		return (dispLogs(ERR_NEEDMOREPARAMS, client.getSocket(), NULL));
	if (client.getNickname() == cmd[1])
		return (dispLogs(ERR_SAMENICKNAME, client.getSocket(), NULL));
	if (checkCharacters(cmd[1]))
		return (dispLogs(ERR_ERRONEUSNICKNAME, client.getSocket(), NULL));
	if (searchNameClient(cmd[1]))
		return (dispLogs(ERR_NICKNAMEINUSE, client.getSocket(), NULL));
	if (!client.getUsername().empty() && client.getNickname().empty()) {
		client.setRegistered(true);
		dispLogs(RPL_WELCOME, client.getSocket(), NULL);
	}
	client.setNickname(cmd[1]);
}