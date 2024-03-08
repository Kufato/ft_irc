/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:53:16 by axcallet          #+#    #+#             */
/*   Updated: 2024/03/08 13:49:42 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_irc.hpp"

void	Server::mode_i(bool newmode, Client &client, std::vector<std::string> cmd, std::map<std::string, Channel *>::iterator channel) {
	if (cmd.size() > 3)
		return (dispLogs(ERR_TOOMUCHPARAMS(client.getNickname(), concatString(cmd)), client.getSocket()));
	channel->second->setInviteMode(newmode);
	channel->second->sendToAll(RPL_MODE(client.getNickname(), channel->second->getName(), cmd[2], ""));
	return (dispLogs(RPL_CHANNELMODEIS(client.getNickname(), cmd[1], cmd[2]), client.getSocket()));
}

void	Server::mode_t(bool newmode, Client &client, std::vector<std::string> cmd, std::map<std::string, Channel *>::iterator channel) {
	if (cmd.size() > 3)
		return (dispLogs(ERR_TOOMUCHPARAMS(client.getNickname(), concatString(cmd)), client.getSocket()));
	channel->second->setRestictMode(newmode);
	channel->second->sendToAll(RPL_MODE(client.getNickname(), channel->second->getName(), cmd[2], ""));
	return (dispLogs(RPL_CHANNELMODEIS(client.getNickname(), cmd[1], cmd[2]), client.getSocket()));
}

void	Server::mode_k(bool newmode, Client &client, std::vector<std::string> cmd, std::map<std::string, Channel *>::iterator channel) {
	if (!newmode) {
		if (cmd.size() > 3)
			return (dispLogs(ERR_TOOMUCHPARAMS(client.getNickname(), concatString(cmd)), client.getSocket()));
		channel->second->setPassword(NULL);
		channel->second->sendToAll(RPL_MODE(client.getNickname(), channel->second->getName(), cmd[2], ""));
	}
	else {
		if (cmd.size() < 4)
			return (dispLogs(ERR_NEEDMOREPARAMS(client.getNickname(), concatString(cmd)), client.getSocket()));
		if (!checkCharacters(cmd[3]))
			return (dispLogs(ERR_BADCHAR(client.getNickname(), cmd[3]), client.getSocket()));
		channel->second->setPassword(cmd[3]);
		channel->second->sendToAllOp(RPL_MODE(client.getNickname(), channel->second->getName(), cmd[2], cmd[3]));
		channel->second->sendToAllNonOp(RPL_MODE(client.getNickname(), channel->second->getName(), cmd[2], "*REDACTED*"));
	}
	return (dispLogs(RPL_CHANNELMODEIS(client.getNickname(), cmd[1], cmd[2]), client.getSocket()));
}

void	Server::mode_o(bool newmode, Client &client, std::vector<std::string> cmd, std::map<std::string, Channel *>::iterator channel) {
	if (cmd.size() < 4)
		return (dispLogs(ERR_NEEDMOREPARAMS(client.getNickname(), concatString(cmd)), client.getSocket()));
	std::vector<std::pair<Client *, bool> >::iterator clienttmp = channel->second->findMember(cmd[3]);
	if (clienttmp == channel->second->getMembers().end())
		return (dispLogs(ERR_NOTONCHANNEL(client.getNickname(), cmd[1]), client.getSocket()));
	if (clienttmp->first->getNickname() == client.getNickname() && clienttmp->second && channel->second->getNbOperator())
		return (dispLogs(ERR_CANTDESERT(client.getNickname(), channel->second->getName()), client.getSocket()));
	channel->second->opClient(clienttmp->first, newmode);
	channel->second->sendToAll(RPL_MODE(client.getNickname(), channel->second->getName(), cmd[2], cmd[3]));
	channel->second->sendToAll(channel->second->namReplyMsg(client));
	return (dispLogs(RPL_CHANNELMODEIS(client.getNickname(), cmd[1], cmd[2]), client.getSocket()));
}

void	Server::mode_l(bool newmode, Client &client, std::vector<std::string> cmd, std::map<std::string, Channel *>::iterator channel) {
	if (!newmode) {
		if (cmd.size() > 3)
			return (dispLogs(ERR_TOOMUCHPARAMS(client.getNickname(), concatString(cmd)), client.getSocket()));
		channel->second->setClientLimit(0);
		channel->second->sendToAll(RPL_MODE(client.getNickname(), channel->second->getName(), cmd[2], ""));
	}
	else {
		if (cmd.size() < 4)
			return (dispLogs(ERR_NEEDMOREPARAMS(client.getNickname(), concatString(cmd)), client.getSocket()));
		int limit = atoi(cmd[3].c_str());
		if (limit < 1 || limit > 10	)
			return (dispLogs(ERR_NOTINRANGE(client.getNickname()), client.getSocket()));
		channel->second->setClientLimit(limit);
		channel->second->sendToAll(RPL_MODE(client.getNickname(), channel->second->getName(), cmd[2], cmd[3]));
	}
	return (dispLogs(RPL_CHANNELMODEIS(client.getNickname(), cmd[1], cmd[2]), client.getSocket()));
}

void	Server::mode(Client &client, std::vector<std::string> cmd) {
	if (checkFormat(cmd, client, 2, 4))
		return ;
	std::map<std::string, Channel *>::iterator	channel = this->_listChannels.find(cmd[1]);
	if (channel == this->_listChannels.end())
		return (dispLogs(ERR_NOSUCHCHANNEL(client.getNickname(), cmd[1]), client.getSocket()));
	std::vector<std::pair<Client *, bool> >::iterator clientmp = channel->second->findMember(client.getNickname());
	if (clientmp == channel->second->getMembers().end())
		return (dispLogs(ERR_NOTONCHANNEL(client.getNickname(), cmd[1]), client.getSocket()));
	if (cmd.size() == 2)
		return ;
	if (!clientmp->second)
		return (dispLogs(ERR_CHANOPRIVSNEEDED(client.getNickname(), cmd[1]), client.getSocket()));
	if ((cmd[2][0] != '+' && cmd[2][0] != '-') || cmd[2].length() != 2)
		return (dispLogs(ERR_UNKNOWNMODE(client.getNickname()), client.getSocket()));
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
			return (dispLogs(ERR_UNKNOWNMODE(client.getNickname()), client.getSocket()));
	}
}