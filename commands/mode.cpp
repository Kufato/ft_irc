/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:53:16 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/01 16:25:03 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

/**
 * Oh god please send help
*/
void	Server::mode(Client &client, std::vector<std::string> cmd) {
	std::map<std::string, Channel *>::iterator	channel = this->_listChannels.find(cmd[1]);

	if (cmd.size() < 3)
		return (dispLogs(ERR_NEEDMOREPARAMS, client.getSocket()));
	if (cmd.size() > 4)
		return (dispLogs(ERR_TOOMANYPARAMS, client.getSocket()));
	if (channel == this->_listChannels.end())
		return (dispLogs(ERR_NOCHANNELFOUND, client.getSocket()));
	std::vector<std::pair<Client *, bool> >::iterator clientmp = channel->second->findMember(client);
	if (clientmp == channel->second->getMembers().end())
		return (dispLogs(ERR_NOTONCHANNEL, client.getSocket()));
	if (!clientmp->second)
		return (dispLogs(ERR_CHANOPRIVSNEEDED, client.getSocket()));
	if ((cmd[2][0] != '+' && cmd[2][0] != '-') || cmd[2].length() != 2)
		return (dispLogs(ERR_UNKNOWNMODE, client.getSocket()));
	bool	newmode = cmd[2][0] == '+';
	switch (cmd[2][1])
	{
		case 'i':
			if (cmd.size() > 3)
				return (dispLogs(ERR_TOOMANYPARAMS, client.getSocket()));
			channel->second->setInviteMode(newmode);
			return (dispLogs(RPL_CHANNELMODEIS, client.getSocket()));
		case 't':
			if (cmd.size() > 3)
				return (dispLogs(ERR_TOOMANYPARAMS, client.getSocket()));
			channel->second->setRestictMode(newmode);
			return (dispLogs(RPL_CHANNELMODEIS, client.getSocket()));
		case 'k':
			if (!newmode) {
				if (cmd.size() > 3)
					return (dispLogs(ERR_TOOMANYPARAMS, client.getSocket()));
				channel->second->setPassword(NULL);
			}
			else {
				if (cmd.size() < 4)
					return (dispLogs(ERR_NEEDMOREPARAMS, client.getSocket()));
				if (!checkCharacters(cmd[3]))
					return (dispLogs(ERR_INVALIDCHAR, client.getSocket()));
				channel->second->setPassword(cmd[3]);
			}
			return (dispLogs(RPL_CHANNELMODEIS, client.getSocket()));
		case 'o':
			if (cmd.size() < 4)
				return (dispLogs(ERR_NEEDMOREPARAMS, client.getSocket()));
			std::vector<std::pair<Client *, bool> >::iterator clienttmp = channel->second->findMember(client);
			if (clienttmp == channel->second->getMembers().end())
				return (dispLogs(ERR_NOTONCHANNEL, client.getSocket()));
			channel->second->opClient(clienttmp->first, newmode);
			return (dispLogs(RPL_CHANNELMODEIS, client.getSocket()));
		case 'l':
			if (!newmode) {
				if (cmd.size() > 3)
					return (dispLogs(ERR_TOOMANYPARAMS, client.getSocket()));
				channel->second->setClientLimit(0);
			}
			else {
				if (cmd.size() < 4)
					return (dispLogs(ERR_NEEDMOREPARAMS, client.getSocket()));
				int limit = atoi(cmd[3].c_str());
				if (limit < 1 || limit > 10	)
					return (dispLogs(ERR_NOTINRANGE, client.getSocket()));
				channel->second->setClientLimit(limit);
			}
			return (dispLogs(RPL_CHANNELMODEIS, client.getSocket()));
		default:
			return (dispLogs(ERR_UNKNOWNMODE, client.getSocket()));
	}
}