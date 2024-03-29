/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:50:06 by axcallet          #+#    #+#             */
/*   Updated: 2024/03/11 17:59:29 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_irc.hpp"

/**
 * Add an invitation in the invitation list of the client specified in cmd
 *
 * 
 * @param client the client sending the invitation
 * @param cmd the full invite command
*/
void	Server::invite(Client &client, std::vector<std::string> cmd) {
	if (checkFormat(cmd, client, 3, 3))
		return ;
	if (cmd[1] == "bot" && this->_bot)
		return (dispLogs(ERR_BOTINVITE(client.getNickname()), client.getSocket()));
	std::map<std::string, Channel *>::iterator	channel = this->_listChannels.find(cmd[2]);
	if (channel == this->_listChannels.end())
		return (dispLogs(ERR_NOSUCHCHANNEL(client.getNickname(), cmd[2]), client.getSocket()));
	std::vector<std::pair<Client *, bool> >::iterator operatortmp = channel->second->findMember(client.getNickname());
	if (operatortmp == channel->second->getMembers().end())
		return (dispLogs(ERR_NOTONCHANNEL(client.getNickname(), channel->second->getName()), client.getSocket()));
	if (channel->second->isInviteOnly() == true && !operatortmp->second)
		return (dispLogs(ERR_CHANOPRIVSNEEDED(client.getNickname(), cmd[2]), client.getSocket()));
	Client *clientTmp = searchNameClient(cmd[1]);
	if (clientTmp) {
		std::vector<std::string> &invitationsTmp = clientTmp->getListInvitation();
		std::vector<std::string>::iterator it = invitationsTmp.begin();
		while (it != invitationsTmp.end()) {
			if (it->c_str() == cmd[2])
				break;
			it++;
		}
		if (it != clientTmp->getListInvitation().end())
			return (dispLogs(ERR_ALREADYINVITED(client.getNickname(), cmd[2]), client.getSocket()));
		clientTmp->setInvitation(cmd[2]);
		dispLogs(RPL_INVITERCVR(client.getNickname(), cmd[1], cmd[2]), clientTmp->getSocket());
		return (dispLogs(RPL_INVITESNDR(client.getNickname(), cmd[1], cmd[2]), client.getSocket()));
	}
	else
		return (dispLogs(ERR_NOSUCHNICK(client.getNickname(), cmd[1]), client.getSocket()));
}