/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:44:11 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/02 15:49:40 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

void Server::privmsg(Client &client, std::vector<std::string> cmd) {
	if (cmd.size() < 3 )
		return (dispLogs(ERR_NEEDMOREPARAMS, client.getSocket(), NULL));
	if (cmd[cmd.size() - 1].empty())
		return (dispLogs(ERR_NOTEXTTOSEND, client.getSocket(), NULL));
	for (int i = 1; i < cmd.size(); i++) {
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
			if (!searchNameClient(cmd[i]))
				return (dispLogs(ERR_NOUSERFOUND, client.getSocket(), NULL));
			send(client.getSocket(), cmd[cmd.size() - 1].c_str(), cmd[cmd.size() - 1].length(), 0);
		}
	}
}
