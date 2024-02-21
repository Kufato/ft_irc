/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:28:49 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/21 14:37:05 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_irc.hpp"

void	Server::topic(Client &client, std::vector<std::string> cmd) {
	std::map<std::string, Channel *>::iterator	channel = this->_listChannels.find(cmd[1]);

	if (cmd.size() < 2)
		return (dispLogs(ERR_NEEDMOREPARAMS(client.getNickname(), concatString(cmd)), client.getSocket()));
	if (cmd.size() > 3)
		return (dispLogs(ERR_TOOMUCHPARAMS(client.getNickname(), concatString(cmd)), client.getSocket()));
	if (channel == this->_listChannels.end())
		return (dispLogs(ERR_NOSUCHCHANNEL(client.getNickname(), cmd[1]), client.getSocket()));
	std::vector<std::pair<Client *, bool> >::iterator operatortmp = channel->second->findMember(client.getNickname());
	if (operatortmp == channel->second->getMembers().end())
		return (dispLogs(ERR_NOTONCHANNEL(client.getNickname(), cmd[1]), client.getSocket()));
	if (channel->second->isTopicRestricted() == true && !operatortmp->second)
		return (dispLogs(ERR_CHANOPRIVSNEEDED(client.getNickname(), cmd[1]), client.getSocket()));
	if (cmd.size() == 2) {
		if (channel->second->getTopic() == "")
			return (dispLogs(RPL_NOTOPIC(client.getNickname(), cmd[1]), client.getSocket()));
		return (dispLogs(RPL_TOPIC(client.getNickname(), cmd[1], channel->second->getTopic()), client.getSocket()));
	}
	channel->second->setTopic(cmd[2]);
	return (channel->second->sendToAll(RPL_TOPIC(client.getNickname(), cmd[1], channel->second->getTopic())));
}