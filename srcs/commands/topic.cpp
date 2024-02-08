/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:28:49 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/08 15:55:28 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_irc.hpp"

void	Server::topic(Client &client, std::vector<std::string> cmd) {

	if (cmd.size() < 2)
		return (dispLogs(ERR_NEEDMOREPARAMS, client.getSocket(), NULL));
	if (cmd.size() > 3)
		return (dispLogs(ERR_TOOMANYPARAMS, client.getSocket(), NULL));
	std::map<std::string, Channel *>::iterator	channel = this->_listChannels.find(cmd[1]);
	if (channel == this->_listChannels.end())
		return (dispLogs(ERR_NOCHANNELFOUND, client.getSocket(), NULL));
	std::vector<std::pair<Client *, bool> >::iterator operatortmp = channel->second->findMember(client);
	if (operatortmp == channel->second->getMembers().end())
		return (dispLogs(ERR_NOTONCHANNEL, client.getSocket(), NULL));
	if (!operatortmp->second)
		return (dispLogs(ERR_CHANOPRIVSNEEDED, client.getSocket(), NULL));
}