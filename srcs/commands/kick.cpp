/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:21:42 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/12 18:04:34 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_irc.hpp"

void	Server::kick(Client &client, std::vector<std::string> cmd) {
	std::map<std::string, Channel *>::iterator	channel = this->_listChannels.find(cmd[1]);
	
	if (cmd.size() < 3)
		return (dispLogs(ERR_NEEDMOREPARAMS(client.getNickname(), concatString(cmd)), client.getSocket()));
	if (cmd.size() > 4)
		return (dispLogs(ERR_TOOMUCHPARAMS(client.getNickname(), concatString(cmd)), client.getSocket()));
	if (client.getNickname() == cmd[2])
		return (dispLogs(ERR_AUTOKICK(client.getNickname(), cmd[1]), client.getSocket(), NULL));
	if (channel == this->_listChannels.end())
		return (dispLogs(ERR_NOSUCHCHANNEL(client.getNickname(), cmd[1]), client.getSocket()));
	std::vector<std::pair<Client *, bool> >::iterator operatortmp = channel->second->findMember(client);
	if (operatortmp == channel->second->getMembers().end())
		return (dispLogs(ERR_NOTONCHANNEL(client.getNickname(), cmd[1]), client.getSocket()));
	if (!operatortmp->second)
		return (dispLogs(ERR_CHANOPRIVSNEEDED(client.getNickname(), cmd[1]), client.getSocket()));
	std::vector<std::pair<Client *, bool> > clientsTmp = channel->second->getMembers();
	for (std::vector<std::pair<Client *, bool> >::iterator it = clientsTmp.begin(); it != clientsTmp.end(); it++) {
		if (it->first->getNickname() == cmd[2]) {
			channel->second->getMembers().erase(it);
			if (cmd.size() == 4)
				return (dispLogs(RPL_KICKREASON(client.getNickname(), cmd[1], cmd[2]), it->first->getSocket()));
			return (dispLogs(RPL_KICK(client.getNickname(), cmd[1], cmd[2], cmd[3]), it->first->getSocket()));
		}
	}
	return (dispLogs(ERR_NOTONCHANNEL(client.getNickname(), cmd[1]), client.getSocket()));
}