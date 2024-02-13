/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:09:30 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/13 11:34:24 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_irc.hpp"

void	Server::join(Client &client, std::vector<std::string> cmd) {


	if (cmd.size() < 2)
		return (dispLogs(ERR_NEEDMOREPARAMS(client.getNickname(), concatString(cmd)), client.getSocket()));
	if (cmd.size() > 3)
		return (dispLogs(ERR_TOOMUCHPARAMS(client.getNickname(), concatString(cmd)), client.getSocket()));
	if (cmd[1][0] != '#')
		return (dispLogs(ERR_BADCHARCHANNEL(client.getNickname(), cmd[1]), client.getSocket()));
	if (!searchNameChannel(cmd[1])) {
		if (cmd.size() == 3)
			return (dispLogs(ERR_PASSCREATECHANNEL(client.getNickname()), client.getSocket()));
		Channel *newChannel = new Channel(cmd[1]);
		this->_listChannels.insert(std::pair<std::string, Channel *>(cmd[1], newChannel));
		newChannel->addClient(&client);
		newChannel->opClient(&client, true);
		std::cout << newChannel->getMembers()[0].first->getNickname() << std::endl;
		return (dispLogs(RPL_JOIN(client.getNickname(), cmd[1]), client.getSocket()));
	}
	std::map<std::string, Channel *>::iterator	channel = this->_listChannels.find(cmd[1]);
	std::vector<std::pair<Client *, bool> > listMembers = channel->second->getMembers();
	if (channel->second->memberPresent(client))
		return (dispLogs(ERR_ALREADYIN(client.getNickname(), cmd[1]), client.getSocket()));
	std::vector<std::string> listInvitations = client.getListInvitation();
	std::vector<std::string>::iterator it = listInvitations.begin();
	if (channel->second->isInviteOnly() == true) {
		while (it != listInvitations.end()) {
			if (it->c_str() == cmd[1])
				break;
			it++;
		}
		if (it == client.getListInvitation().end())
			return (dispLogs(ERR_INVITEONLYCHAN(client.getNickname(), cmd[1]), client.getSocket()));
	}
	if (channel->second->getPassword() != "") {
		if (cmd[2] != channel->second->getPassword() || cmd.size() != 3)
			return (dispLogs(ERR_BADCHANNELKEY(client.getNickname(), cmd[1]), client.getSocket()));
	}
	if (channel->second->getMembers().size() != 0) {
		if ((int)channel->second->getMembers().size() >= channel->second->getClientLimit())
			return (dispLogs(ERR_CHANNELISFULL(client.getNickname(), cmd[1]), client.getSocket()));
	}
	if (it != client.getListInvitation().end())
		listInvitations.erase(it);
	channel->second->addClient(&client);
	std::cout << channel->second->getMembers()[0].first->getNickname() << std::endl;
	return (dispLogs(RPL_JOIN(client.getNickname(), cmd[1]), client.getSocket()));
}