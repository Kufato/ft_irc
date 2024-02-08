/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:50:06 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/08 14:50:35 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_irc.hpp"

void	Server::invite(Client &client, std::vector<std::string> cmd) {

	if (cmd.size() < 3)
		return (dispLogs(ERR_NEEDMOREPARAMS, client.getSocket(), NULL));
	if (cmd.size() > 3)
		return (dispLogs(ERR_TOOMANYPARAMS, client.getSocket(), NULL));
	std::map<std::string, Channel *>::iterator	channel = this->_listChannels.find(cmd[2]);
	if (channel == this->_listChannels.end())
		return (dispLogs(ERR_NOCHANNELFOUND, client.getSocket(), NULL));
	std::vector<std::pair<Client *, bool> >::iterator operatortmp = channel->second->findMember(client);
	if (operatortmp == channel->second->getMembers().end())
		return (dispLogs(ERR_NOTONCHANNEL, client.getSocket(), NULL));
	if (!operatortmp->second)
		return (dispLogs(ERR_CHANOPRIVSNEEDED, client.getSocket(), NULL));
	Client *clientTmp = searchNameClient(cmd[1]);
	if (clientTmp) {
		std::vector<std::string> invitationsTmp = clientTmp->getListInvitation();
		std::vector<std::string>::iterator it = invitationsTmp.begin();
		while (it != clientTmp->getListInvitation().end())
		{
			if (it->c_str() == cmd[2])
				break;
			it++;
		}
		if (it == clientTmp->getListInvitation().end())
			return (dispLogs(ERR_ALREADYINVITED, client.getSocket(), NULL));
		clientTmp->setInvitation(cmd[2]);
		dispLogs(RPL_INVITE, clientTmp->getSocket(), (void *)cmd[2].c_str());
		return (dispLogs(RPL_SENDINVITATION, client.getSocket(), (void *)cmd[1].c_str()));
	}
	return (dispLogs(ERR_NOTONCHANNEL, client.getSocket(), NULL));
	
}