/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:26:40 by axcallet          #+#    #+#             */
/*   Updated: 2024/03/11 19:14:34 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_irc.hpp"

void Server::nick(Client &client, std::vector<std::string> cmd) {
	if (checkFormat(cmd, client, 2, 2))
		return ;
	if (cmd[1] == "bot")
		return (dispLogs(ERR_BOTNICK(client.getNickname()), client.getSocket()));
	if (client.getNickname() == cmd[1])
		return (dispLogs(ERR_SAMENICKNAME(client.getNickname()), client.getSocket()));
	if (!checkCharacters(cmd[1]))
		return (dispLogs(ERR_ERRONUSENICKNAME(client.getNickname(), cmd[1]), client.getSocket()));
	if (searchNameClient(cmd[1]))
		return (dispLogs(ERR_NICKNAMEINUSE(client.getNickname(), cmd[1]), client.getSocket()));
	std::string tmpnick = client.getNickname();
	client.setNickname(cmd[1]);
	if (client.isRegistered()) {
		dispLogs(RPL_WELCOME(client.getNickname()), client.getSocket());
		for (std::map<std::string, Channel *>::iterator it = this->_listChannels.begin(); it != this->_listChannels.end(); it++) {
				std::vector<std::pair<Client *, bool> >::iterator member = it->second->findMember(client.getNickname());
				if (member != it->second->getMembers().end())
				{
					it->second->sendToAll(RPL_PART(tmpnick, it->second->getName()));
					dispLogs(RPL_JOIN(client.getNickname(), it->second->getName()), client.getSocket());
					it->second->sendToAll(it->second->namReplyMsg(client));
				}
			}
		return ;
	}
	if (!client.getUsername().empty() && !client.getNickname().empty()) {
		client.setRegistered(true);
		dispLogs(RPL_WELCOME(client.getNickname()), client.getSocket());
	}
}