/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:44:11 by axcallet          #+#    #+#             */
/*   Updated: 2024/03/11 16:51:33 by axcallet         ###   ########.fr       */
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
			if (!searchNameChannel(cmd[i])) {
				dispLogs(ERR_NOSUCHCHANNEL(client.getNickname(), cmd[i]), client.getSocket());
				continue;
			}
			Channel channelTmp = *this->_listChannels.find(cmd[i])->second;
			if (!channelTmp.memberPresent(client)) {
				dispLogs(ERR_CANNOTSENDTOCHAN(client.getNickname(), channelTmp.getName()), client.getSocket());
				continue;
			}
			std::vector<std::pair<Client *, bool> > clientsTmp = channelTmp.getMembers();
			for (std::vector<std::pair<Client *, bool> >::iterator it = clientsTmp.begin(); it != clientsTmp.end(); it++) {
				if (client.getNickname() != it->first->getNickname()) {
					std::string	msg = client.getNickname() + " sent to " + channelTmp.getName() + " : " + cmd[cmd.size() - 1] + '\n'; 
					dispLogs(CHANNEL_MESSAGES(client.getNickname(), channelTmp.getName(), cmd[cmd.size() - 1]), it->first->getSocket());
				}
			}
		}
		else {
			Client *receiver = searchNameClient(cmd[i]);
			if (!receiver)
				dispLogs(ERR_NOSUCHNICK(client.getNickname(), cmd[i]), client.getSocket());
			else if (receiver->getNickname() != "bot")
				dispLogs(USER_MESSAGES(client.getNickname(), receiver->getNickname(), cmd[cmd.size() - 1]), receiver->getSocket());
			else
				this->bot_msg(client, *receiver, cmd);
		}
	}
}