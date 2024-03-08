/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:28:49 by axcallet          #+#    #+#             */
/*   Updated: 2024/03/08 13:50:24 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_irc.hpp"

void	Server::topic(Client &client, std::vector<std::string> cmd) {
	if (checkFormat(cmd, client, 2, 3))
		return ;
	std::map<std::string, Channel *>::iterator	channel = this->_listChannels.find(cmd[1]);
	if (channel == this->_listChannels.end())
		return (dispLogs(ERR_NOSUCHCHANNEL(client.getNickname(), cmd[1]), client.getSocket()));
	std::vector<std::pair<Client *, bool> >::iterator operatortmp = channel->second->findMember(client.getNickname());
	if (operatortmp == channel->second->getMembers().end())
		return (dispLogs(ERR_NOTONCHANNEL(client.getNickname(), cmd[1]), client.getSocket()));
	if (channel->second->isTopicRestricted() == true && !operatortmp->second && cmd.size() == 3)
		return (dispLogs(ERR_CHANOPRIVSNEEDED(client.getNickname(), cmd[1]), client.getSocket()));
	if (cmd.size() == 2) {
		if (channel->second->getTopic() == "")
			return (dispLogs(RPL_NOTOPIC(client.getNickname(), cmd[1]), client.getSocket()));
		return (dispLogs(RPL_TOPIC(client.getNickname(), cmd[1], channel->second->getTopic()), client.getSocket()));
	}
	channel->second->setTopic(cmd[2]);
	return (channel->second->sendToAll(RPL_TOPIC(client.getNickname(), cmd[1], channel->second->getTopic())));
}