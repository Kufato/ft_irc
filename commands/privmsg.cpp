/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:44:11 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/06 15:49:53 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_irc.hpp"

void Server::privmsg(Client &client, std::vector<std::string> cmd) {
	if (cmd.size() < 3 )
		return (dispLogs(ERR_NEEDMOREPARAMS, client.getSocket(), NULL));
	if (cmd[cmd.size() - 1].empty())
		return (dispLogs(ERR_NOTEXTTOSEND, client.getSocket(), NULL));
	for (size_t i = 1; i < cmd.size() - 1; i++) {
		if (cmd[i][0] == '#') {
			if (!searchNameChannel(cmd[i]))
				return (dispLogs(ERR_NOCHANNELFOUND, client.getSocket(), NULL));
			Channel channelTmp = *this->_listChannels.find(cmd[i])->second;
			std::vector<std::pair<Client *, bool> > clientsTmp = channelTmp.getMembers();
			for (std::vector<std::pair<Client *, bool> >::iterator it = clientsTmp.begin(); it != clientsTmp.end(); it++) {
				if (client.getNickname() != it->first->getNickname())
					send(it->first->getSocket(), cmd[cmd.size() - 1].c_str(), cmd[cmd.size() - 1].length(), 0);
			}
		}
		else {
			Client *receiver = searchNameClient(cmd[i]);
			if (!receiver)
				return (dispLogs(ERR_NOUSERFOUND, client.getSocket(), NULL));
			std::string	msg = client.getNickname() + " sent to you: " + cmd[cmd.size() - 1] + '\n'; 
			send(receiver->getSocket(), msg.c_str(), msg.length(), 0);
		}
	}
}
