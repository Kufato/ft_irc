/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:53:16 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/01 13:53:41 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

static bool	checkClientIsOpe(Client &client, Channel channel, std::vector<std::pair<Client *, bool> > listClients) {
	for (std::vector<std::pair<Client *, bool> >::iterator it = listClients.begin(); it != listClients.end(); it++) {
		if (client.getNickname() == it->first->getNickname()) {
			if (it->second == false)
				return (false);
			return (true);
		}
	}
}

void	Server::mode(Client &client, std::vector<std::string> cmd) {
	Channel									channel = *this->_listChannels.find(cmd[1])->second;
	std::vector<std::pair<Client *, bool> >	listClients = channel.getMembers();

	if (cmd.size() < 3)
		return (dispLogs(ERR_NEEDMOREPARAMS, client.getSocket()));
	if (cmd.size() > 4)
		return (dispLogs(ERR_TOOMANYPARAMS, client.getSocket()));
	if (!checkClientIsOpe(client, channel, listClients))
		return (dispLogs(ERR_NOOPERATOR, client.getSocket()));
	if (cmd[1][0] == '#') {
		if 
	}
	else {
		
	}
}