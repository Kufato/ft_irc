/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:09:30 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/08 13:54:58 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_irc.hpp"

void	Server::join(Client &client, std::vector<std::string> cmd) {


	if (cmd.size() < 2)
		return (dispLogs(ERR_NEEDMOREPARAMS, client.getSocket(), NULL));
	if (cmd.size() > 3)
		return (dispLogs(ERR_TOOMANYPARAMS, client.getSocket(), NULL));
	if (cmd[1][0] != '#')
		return (dispLogs(ERR_BADCHARCHANNEL, client.getSocket(), NULL));
	if (!searchNameChannel(cmd[1])) {
		if (cmd.size() == 3)
			return (dispLogs(ERR_PASSCREATECHANNEL, client.getSocket(), NULL));
		if (cmd.size() == 2)
		{
			Channel *newChannel = new Channel(cmd[1]);
			this->_listChannels.insert(std::pair<std::string, Channel *>(cmd[1], newChannel));
			newChannel->addClient(&client);
			newChannel->opClient(&client, true);
			std::cout << newChannel->getMembers()[0].first->getNickname() << std::endl;
			return (dispLogs(RPL_CHANNELCREATED, client.getSocket(), (void *)cmd[1].c_str()));
		}
	}
	else {
		std::map<std::string, Channel *>::iterator	channel = this->_listChannels.find(cmd[1]);
		if (channel->second->findMember(client) != channel->second->getMembers().end())
			return (dispLogs(ERR_ALREADYIN, client.getSocket(), NULL));
		std::vector<std::string> listInvitations = client.getListInvitation();
		std::vector<std::string>::iterator it = listInvitations.begin();
		if (channel->second->isInviteOnly() == true) {
			while (it != listInvitations.end())
			{
				if (it->c_str() == cmd[1])
					break;
				it++;
			}
			if (it == client.getListInvitation().end())
				return (dispLogs(ERR_NOINVITATION, client.getSocket(), NULL));
		}
		if (channel->second->getPassword() != "") {
			if (cmd.size() != 3)
				return (dispLogs(ERR_NOPASS, client.getSocket(), NULL));
			if (cmd[2] != channel->second->getPassword())
				return (dispLogs(ERR_BADPASS, client.getSocket(), NULL));
		}
		if (channel->second->getMembers().size() != 0) {
			if ((int)channel->second->getMembers().size() >= channel->second->getClientLimit())
				return (dispLogs(ERR_CHANNELFULL, client.getSocket(), NULL));
		}
		if (it != client.getListInvitation().end())
			listInvitations.erase(it);
		channel->second->addClient(&client);
		std::cout << channel->second->getMembers()[0].first->getNickname() << std::endl;
		return (dispLogs(RPL_CHANNELJOINED, client.getSocket(), NULL));
		
		
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