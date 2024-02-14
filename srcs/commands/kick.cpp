/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:21:42 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/14 18:01:52 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_irc.hpp"

void	Server::kick(Client &client, std::vector<std::string> cmd) {
	int											pos = 2;
	std::map<std::string, Channel *>::iterator	channel = this->_listChannels.find(cmd[2]);
	
	if (cmd.size() < 3)
		return (dispLogs(ERR_NEEDMOREPARAMS(client.getNickname(), concatString(cmd)), client.getSocket()));
	if (cmd.size() > 5)
		return (dispLogs(ERR_TOOMUCHPARAMS(client.getNickname(), concatString(cmd)), client.getSocket()));
	if (client.getNickname() == cmd[3])
		return (dispLogs(ERR_AUTOKICK(client.getNickname(), cmd[2]), client.getSocket()));
	if (channel == this->_listChannels.end()) {
		channel = this->_listChannels.find(cmd[1]);
		if (channel == this->_listChannels.end())
			return (dispLogs(ERR_NOSUCHCHANNEL(client.getNickname(), cmd[1]), client.getSocket()));
		pos = 1;
	}
	std::vector<std::pair<Client *, bool> >::iterator operator = channel->second->findMember(client.getNickname());
	if (operator == channel->second->getMembers().end())
		return (dispLogs(ERR_NOTONCHANNEL(client.getNickname(), cmd[pos]), client.getSocket()));
	// std::cout << operator->first << " " << operator->second << std::endl;
	if (!operator->second)
		return (dispLogs(ERR_CHANOPRIVSNEEDED(client.getNickname(), cmd[pos]), client.getSocket()));
	// std::vector<std::pair<Client *, bool> > clientsTmp = channel->second->getMembers();
	std::vector<std::pair<Client *, bool> >::iterator target = channel->second->findMember(cmd[pos + 1]);
	if (target == channel->second->getMembers().end())
		return (dispLogs(ERR_NOTONCHANNEL(client.getNickname(), cmd[pos]), client.getSocket()));
	dispLogs(RPL_KICK(client.getNickname(), channel->second->getName(), target->first->getNickname(), cmd[pos + 2]), target->first->getSocket());
	int	socketTarget = target->first->getSocket();
	channel->second->getMembers().erase(target);
	dispLogs(channel->second->namReplyMsg(client), socketTarget);
	channel->second->sendToAll(channel->second->namReplyMsg(client));
	return ;
}