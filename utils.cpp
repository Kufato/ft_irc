/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:33:38 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/01 11:52:56 by axcallet         ###   ########.fr       */
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
			return (it->second);
	}
	return (NULL);
}

void	Server::dispLogs(std::string str, int clientFD) {
	std::string tmp = "[IRC] ";
	tmp += str;
	send(clientFD, tmp.c_str(), sizeof(tmp), 0);
}