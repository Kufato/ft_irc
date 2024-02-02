/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:33:38 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/02 15:27:04 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

bool	Server::searchNameClient(std::string nickname) {
	for (std::map<int, Client *>::iterator it = this->_listClients.begin(); it != this->_listClients.end(); it++) {
		if (it->second->getNickname() == nickname)
			return (true);
	}
	return (false);
}

Channel	Server::searchNameChannel(std::string name) {
	for (std::map<std::string, Channel *>::iterator it = this->_listChannels.begin(); it != this->_listChannels.end(); it++) {
		if (it->first == name)
			return (*it->second);
	}
	return ((Channel)NULL);
}

void	Server::dispLogs(std::string str, int clientFD, void *param) {
	std::string tmp = "[IRC] ";
	tmp += str;
	if (param)
		tmp += (char *)param;
	send(clientFD, tmp.c_str(), sizeof(tmp), 0);
}

bool	checkCharacters(std::string s) {
	std::string allowedChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_";

	if (s.find_first_not_of(allowedChars) != std::string::npos)
		return (false);
	return (true);
}