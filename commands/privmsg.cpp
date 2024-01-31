/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:44:11 by axcallet          #+#    #+#             */
/*   Updated: 2024/01/31 16:48:34 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_irc.hpp"
#include "../define.hpp"

void Server::privmsg(Client &client, std::vector<std::string> cmd) {
	if (cmd.size() < 3 )
		return (dispLogs(ERR_NEEDMOREPARAMS, client.getSocket()));
	if (cmd[cmd.size() - 1].empty())
		return (dispLogs(ERR_NOTEXTTOSEND, client.getSocket()));
	for (int i = 1; i < cmd.size(); i++) {
		if (cmd[1][0] == '#')
			// check pour les channels
		else {
			if (searchNameClient(cmd[1]))
				return (dispLogs(ERR_NORECIPIENT, client.getSocket()));
			send(client.getSocket(), cmd[cmd.size() - 1].c_str(), cmd[cmd.size() - 1].length(), 0);
		}
	}
