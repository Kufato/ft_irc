/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:26:40 by axcallet          #+#    #+#             */
/*   Updated: 2024/01/30 17:38:02 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_irc.hpp"
#include "../define.hpp"

static bool	checkCharacters(std::string nickname) {
	std::string allowedChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_";
	
	if (nickname.find_first_not_of(allowedChars) != std::string::npos)
		return (false);
	return (true);
}

void Server::nick(Client &client, std::vector<std::string> cmd) {
	if (cmd.size() != 2 || cmd[1].empty())
		return (dispLogs(ERR_NEEDMOREPARAMS, client.getSocket()));
	if (checkCharacters(cmd[1]))
		return (dispLogs(ERR_ERRONEUSNICKNAME, client.getSocket()));
	if (searchNickname(cmd[1]))
		return (dispLogs(ERR_NICKNAMEINUSE, client.getSocket()));
	client.setNickname(cmd[1]);
	client.setRegistered(true);
	dispLogs(RPL_WELCOME, client.getSocket());
}