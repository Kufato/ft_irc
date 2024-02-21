/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:44:11 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/21 17:53:07 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_irc.hpp"

void Server::privmsg(Client &client, std::vector<std::string> cmd) {
	if (cmd.size() < 3 )
		return (dispLogs(ERR_NEEDMOREPARAMS(client.getNickname(), concatString(cmd)), client.getSocket()));
	if (cmd[cmd.size() - 1].empty())
		return (dispLogs(ERR_NOTEXTTOSEND(client.getNickname()), client.getSocket()));
	for (size_t i = 1; i < cmd.size() - 1; i++) {
		if (cmd[i][0] == '#') {
			if (!searchNameChannel(cmd[i]))
				return (dispLogs(ERR_NOSUCHCHANNEL(client.getNickname(), cmd[i]), client.getSocket()));
			Channel channelTmp = *this->_listChannels.find(cmd[i])->second;
			if (channelTmp.isTopicRestricted() && !channelTmp.memberPresent(client))
				return (dispLogs(ERR_CANNOTSENDTOCHAN(client.getNickname(), channelTmp.getName()), client.getSocket()));
			std::vector<std::pair<Client *, bool> > clientsTmp = channelTmp.getMembers();
			for (std::vector<std::pair<Client *, bool> >::iterator it = clientsTmp.begin(); it != clientsTmp.end(); it++) {
				if (client.getNickname() != it->first->getNickname()) {
					std::string	msg = client.getNickname() + " sent to " + channelTmp.getName() + " : " + cmd[cmd.size() - 1] + '\n'; 
					dispLogs(CHANNEL_MESSAGES(client.getNickname(), channelTmp.getName(), cmd[2]), it->first->getSocket());
				}
			}
		}
		else {
			Client *receiver = searchNameClient(cmd[i]);
			if (!receiver)
				return (dispLogs(ERR_NOSUCHNICK(client.getNickname(), cmd[i]), client.getSocket()));
			std::string	msg = client.getNickname() + " sent to you: " + cmd[cmd.size() - 1] + '\n'; 
			dispLogs(USER_MESSAGES(client.getNickname(), receiver->getNickname(), cmd[2]), receiver->getSocket());
		}
	}
}
