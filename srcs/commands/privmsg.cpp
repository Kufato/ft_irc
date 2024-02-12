/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:44:11 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/12 14:34:38 by axcallet         ###   ########.fr       */
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
			std::vector<std::pair<Client *, bool> > clientsTmp = channelTmp.getMembers();
			for (std::vector<std::pair<Client *, bool> >::iterator it = clientsTmp.begin(); it != clientsTmp.end(); it++) {
				if (client.getNickname() != it->first->getNickname()) {
					std::string	msg = client.getNickname() + " sent to " + channelTmp.getName() + " : " + cmd[cmd.size() - 1] + '\n'; 
					send(it->first->getSocket(), msg.c_str(), msg.length(), 0);
				}
			}
		}
		else {
			Client *receiver = searchNameClient(cmd[i]);
			if (!receiver)
				return (dispLogs(ERR_NOSUCHNICK(client.getNickname(), cmd[i]), client.getSocket()));
			std::string	msg = client.getNickname() + " sent to you: " + cmd[cmd.size() - 1] + '\n'; 
			send(receiver->getSocket(), msg.c_str(), msg.length(), 0);
		}
	}
}
