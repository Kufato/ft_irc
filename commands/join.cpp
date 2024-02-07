/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:09:30 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/07 14:53:42 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_irc.hpp"

void	Server::join(Client &client, std::vector<std::string> cmd) {


	if (cmd.size() < 2)
		return (dispLogs(ERR_NEEDMOREPARAMS, client.getSocket(), NULL));
	if (cmd.size() > 3)
		return (dispLogs(ERR_TOOMANYPARAMS, client.getSocket(), NULL));
	if (!searchNameChannel(cmd[2])) {
		if (cmd.size() == 3)
			return (dispLogs(ERR_PASSCREATECHANNEL, client.getSocket(), NULL));
		if (cmd.size() == 2)
			this->_listChannels.insert(std::pair<std::string, Channel *>(cmd[1], new Channel(cmd[1])));
	}
	else {
		std::map<std::string, Channel *>::iterator	channel = this->_listChannels.find(cmd[1]);
		if (channel->second->isInviteOnly() == true) {
			std::vector<std::string>::iterator it = client->_listInvitation.begin();
			while (it != client->_listInvitation.end())
				it++;
			if (it == client->_listInvitation.end())
				return (dispLogs(ERR_NOINVITATION, client.getSocket(), NULL));
		}
		if (channel->second->getPassword() != NULL) {
			if (cmd[2].empty())
				return (dispLogs(ERR_NOPASS, client.getSocket(), NULL));
			if (cmd[2] != channel->second->getPassword())
				return (dispLogs(ERR_BADPASS, client.getSocket(), NULL));
		}
		if (channel->second->_members.size() != 0) {
			if (channel->second->_members.size() == channel->second->getClientLimit());
				return (dispLogs(ERR_CHANNELFULL, client.getSocket(), NULL));
		}
		
		
		// if (cmd.size() == 2 && channel->second->isInviteOnly() == true)
		// 	return (dispLogs("il faut un mdp pour les inviteonlychannel", client.getSocket(), NULL));
		// if (cmd.size() == 3 && channel->second->isInviteOnly() == false)
		// 	return (dispLogs("arg en trop"), client.getSocket())
		// if (cmd.size() == 3 && channel->second->isInviteOnly() == true) {
		// 	if ()
		// 	join private channel with key cmd[3]
		// }
		// if (cmd.size() == 2 && channel->second->isInviteOnly() == false)
		// 	join channel;
	}
}