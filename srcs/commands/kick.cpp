/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:21:42 by axcallet          #+#    #+#             */
/*   Updated: 2024/03/22 09:37:00 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_irc.hpp"

void	Server::kick(Client &client, std::vector<std::string> cmd) {
	if (checkFormat(cmd, client, 3, 4))
		return ;
	std::map<std::string, Channel *>::iterator	channel = this->_listChannels.find(cmd[1]);
	if (channel == this->_listChannels.end())
		return (dispLogs(ERR_NOSUCHCHANNEL(client.getNickname(), cmd[1]), client.getSocket()));
	if (client.getNickname() == cmd[2]) {
		channel->second->eraseClient(client.getNickname());
		dispLogs(channel->second->namReplyMsg(client), client.getSocket());
		channel->second->sendToAll(RPL_PART(cmd[2], cmd[1]));
		this->deleteEmptyChannels();
		dispLogs(RPL_PART(cmd[2], cmd[1]), client.getSocket());
		return ;
	}
	std::vector<std::pair<Client *, bool> >::iterator ope = channel->second->findMember(client.getNickname());
	if (ope == channel->second->getMembers().end())
		return (dispLogs(ERR_NOTONCHANNEL(client.getNickname(), cmd[1]), client.getSocket()));
	if (!ope->second)
		return (dispLogs(ERR_CHANOPRIVSNEEDED(client.getNickname(), cmd[1]), client.getSocket()));
	std::vector<std::pair<Client *, bool> >::iterator target = channel->second->findMember(cmd[2]);
	if (target == channel->second->getMembers().end())
		return (dispLogs(ERR_NOTONCHANNEL(client.getNickname(), cmd[1]), client.getSocket()));
	if (cmd.size() == 4)
		dispLogs(RPL_KICK(client.getNickname(), channel->second->getName(), target->first->getNickname(), cmd[3]), target->first->getSocket());
	else
		dispLogs(RPL_KICK(client.getNickname(), channel->second->getName(), target->first->getNickname(), ""), target->first->getSocket());
	int	socketTarget = target->first->getSocket();
	channel->second->eraseClient(target->first->getNickname());
	dispLogs(channel->second->namReplyMsg(client), socketTarget);
	channel->second->sendToAll(RPL_PART(cmd[2], cmd[1]));
	return ;
}