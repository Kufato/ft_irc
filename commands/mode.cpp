/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:53:16 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/02 15:31:50 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

void	Server::mode_i(bool newmode, Client &client, std::vector<std::string> cmd, std::map<std::string, Channel *>::iterator	channel) {
	if (cmd.size() > 3)
		return (dispLogs(ERR_TOOMANYPARAMS, client.getSocket(), NULL));
	channel->second->setInviteMode(newmode);
	return (dispLogs(RPL_CHANNELMODEIS, client.getSocket(), NULL));
}

void	Server::mode_t(bool newmode, Client &client, std::vector<std::string> cmd, std::map<std::string, Channel *>::iterator	channel) {
	if (cmd.size() > 3)
		return (dispLogs(ERR_TOOMANYPARAMS, client.getSocket(), NULL));
	channel->second->setRestictMode(newmode);
	return (dispLogs(RPL_CHANNELMODEIS, client.getSocket(), NULL));
}

void	Server::mode_k(bool newmode, Client &client, std::vector<std::string> cmd, std::map<std::string, Channel *>::iterator	channel) {
	if (!newmode) {
		if (cmd.size() > 3)
			return (dispLogs(ERR_TOOMANYPARAMS, client.getSocket(), NULL));
		channel->second->setPassword(NULL);
	}
	else {
		if (cmd.size() < 4)
			return (dispLogs(ERR_NEEDMOREPARAMS, client.getSocket(), NULL));
		if (!checkCharacters(cmd[3]))
			return (dispLogs(ERR_INVALIDCHAR, client.getSocket(), NULL));
		channel->second->setPassword(cmd[3]);
	}
	return (dispLogs(RPL_CHANNELMODEIS, client.getSocket(), NULL));
}

void	Server::mode_o(bool newmode, Client &client, std::vector<std::string> cmd, std::map<std::string, Channel *>::iterator	channel) {
	if (cmd.size() < 4)
		return (dispLogs(ERR_NEEDMOREPARAMS, client.getSocket(), NULL));
	std::vector<std::pair<Client *, bool> >::iterator clienttmp = channel->second->findMember(client);
	if (clienttmp == channel->second->getMembers().end())
		return (dispLogs(ERR_NOTONCHANNEL, client.getSocket(), NULL));
	channel->second->opClient(clienttmp->first, newmode);
	return (dispLogs(RPL_CHANNELMODEIS, client.getSocket(), NULL));
}

void	Server::mode_l(bool newmode, Client &client, std::vector<std::string> cmd, std::map<std::string, Channel *>::iterator	channel) {
	if (!newmode) {
		if (cmd.size() > 3)
			return (dispLogs(ERR_TOOMANYPARAMS, client.getSocket(), NULL));
		channel->second->setClientLimit(0);
	}
	else {
		if (cmd.size() < 4)
			return (dispLogs(ERR_NEEDMOREPARAMS, client.getSocket(), NULL));
		int limit = atoi(cmd[3].c_str());
		if (limit < 1 || limit > 10	)
			return (dispLogs(ERR_NOTINRANGE, client.getSocket(), NULL));
		channel->second->setClientLimit(limit);
	}
	return (dispLogs(RPL_CHANNELMODEIS, client.getSocket(), NULL));
}

/**
 * Oh god please send help
*/
void	Server::mode(Client &client, std::vector<std::string> cmd) {
	std::map<std::string, Channel *>::iterator	channel = this->_listChannels.find(cmd[1]);

	if (cmd.size() < 3)
		return (dispLogs(ERR_NEEDMOREPARAMS, client.getSocket(), NULL));
	if (cmd.size() > 4)
		return (dispLogs(ERR_TOOMANYPARAMS, client.getSocket(), NULL));
	if (channel == this->_listChannels.end())
		return (dispLogs(ERR_NOCHANNELFOUND, client.getSocket(), NULL));
	std::vector<std::pair<Client *, bool> >::iterator clientmp = channel->second->findMember(client);
	if (clientmp == channel->second->getMembers().end())
		return (dispLogs(ERR_NOTONCHANNEL, client.getSocket(), NULL));
	if (!clientmp->second)
		return (dispLogs(ERR_CHANOPRIVSNEEDED, client.getSocket(), NULL));
	if ((cmd[2][0] != '+' && cmd[2][0] != '-') || cmd[2].length() != 2)
		return (dispLogs(ERR_UNKNOWNMODE, client.getSocket(), NULL));
	bool	newmode = cmd[2][0] == '+';
	switch (cmd[2][1]) {
		case 'i':
			mode_i(newmode, client, cmd, channel);
			break ;
		case 't':
			mode_t(newmode, client, cmd, channel);
			break ;
		case 'k':
			mode_k(newmode, client, cmd, channel);
			break ;
		case 'o':
			mode_o(newmode, client, cmd, channel);
			break ;
		case 'l':
			mode_l(newmode, client, cmd, channel);
			break ;
		default:
			return (dispLogs(ERR_UNKNOWNMODE, client.getSocket(), NULL));
	}
}