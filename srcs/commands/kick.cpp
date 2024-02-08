/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:21:42 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/08 14:50:41 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_irc.hpp"

void	Server::kick(Client &client, std::vector<std::string> cmd) {
	std::map<std::string, Channel *>::iterator	channel = this->_listChannels.find(cmd[1]);
	
	if (cmd.size() < 3)
		return (dispLogs(ERR_NEEDMOREPARAMS, client.getSocket(), NULL));
	if (cmd.size() > 3)
		return (dispLogs(ERR_TOOMANYPARAMS, client.getSocket(), NULL));
	if (client.getNickname() == cmd[2])
		return (dispLogs(ERR_AUTOKICK, client.getSocket(), NULL));
	if (channel == this->_listChannels.end())
		return (dispLogs(ERR_NOCHANNELFOUND, client.getSocket(), NULL));
	std::vector<std::pair<Client *, bool> >::iterator operatortmp = channel->second->findMember(client);
	if (operatortmp == channel->second->getMembers().end())
		return (dispLogs(ERR_NOTONCHANNEL, client.getSocket(), NULL));
	if (!operatortmp->second)
		return (dispLogs(ERR_CHANOPRIVSNEEDED, client.getSocket(), NULL));
	std::vector<std::pair<Client *, bool> > clientsTmp = channel->second->getMembers();
	for (std::vector<std::pair<Client *, bool> >::iterator it = clientsTmp.begin(); it != clientsTmp.end(); it++) {
		if (it->first->getNickname() == cmd[2]) {
			channel->second->getMembers().erase(it);
			return (dispLogs(RPL_KICK, it->first->getSocket(), NULL));
		}
	}
	return (dispLogs(ERR_NOTONCHANNEL, client.getSocket(), NULL));
}