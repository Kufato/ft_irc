/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:50:06 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/22 16:01:29 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

/**
 * Add an invitation in the invitation list of the client specified in cmd
 *
 * 
 * @param client the client sending the invitation
 * @param cmd the full invite command
*/
void	Server::invite(Client &client, std::vector<std::string> cmd) {
	std::map<std::string, Channel *>::iterator	channel = this->_listChannels.find(cmd[2]);

	if (checkFormat(cmd, client, 3, 3))
		return ;
	if (channel == this->_listChannels.end())
		return (dispLogs(ERR_NOSUCHCHANNEL(client.getNickname(), cmd[2]), client.getSocket()));
	std::vector<std::pair<Client *, bool> >::iterator operatortmp = channel->second->findMember(client.getNickname());
	if (operatortmp == channel->second->getMembers().end())
		return (dispLogs(ERR_NOTONCHANNEL(client.getNickname(), channel->second->getName()), client.getSocket()));
	if (channel->second->isInviteOnly() == true && !operatortmp->second)
		return (dispLogs(ERR_CHANOPRIVSNEEDED(client.getNickname(), cmd[2]), client.getSocket()));
	Client *clientTmp = searchNameClient(cmd[1]);
	if (clientTmp) {
		std::vector<std::string> invitationsTmp = clientTmp->getListInvitation();
		std::vector<std::string>::iterator it = invitationsTmp.begin();
		while (it != clientTmp->getListInvitation().end()) {
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
	return (dispLogs(ERR_NOTONCHANNEL(client.getNickname(), cmd[2]), client.getSocket()));
	
}