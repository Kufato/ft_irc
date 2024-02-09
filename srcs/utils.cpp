/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:33:38 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/09 14:50:43 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Channel.hpp"

bool	Server::clientExist(std::string nickname) {
	for (std::map<int, Client *>::iterator it = this->_listClients.begin(); it != this->_listClients.end(); it++) {
		if (it->second->getNickname() == nickname)
			return (true);
	}
	return (false);
}

Client	*Server::searchNameClient(std::string nickname) {
	for (std::map<int, Client *>::iterator it = this->_listClients.begin(); it != this->_listClients.end(); it++)
		std::cout << it->second->getNickname() << std::endl;
	for (std::map<int, Client *>::iterator it = this->_listClients.begin(); it != this->_listClients.end(); it++) {
		if (it->second->getNickname() == nickname)
			return (it->second);
	}
	return (NULL);
}

Channel	*Server::searchNameChannel(std::string name) {
	if (_listChannels.empty())
		return NULL;
	for (std::map<std::string, Channel *>::iterator it = this->_listChannels.begin(); it != this->_listChannels.end(); it++) {
		if (it->first == name)
			return (it->second);
	}
	return (NULL);
}

void	Server::dispLogs(std::string str, int clientFD, void *param) {
	std::string tmp = "[IRC] ";
	if (param)
		tmp += (char *)param;
	tmp += str;
	tmp += '\n';
	send(clientFD, tmp.c_str(), tmp.length(), 0);
}

bool	checkCharacters(std::string s) {
	std::string allowedChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_";

	if (s.find_first_not_of(allowedChars) != std::string::npos)
		return (false);
	return (true);
}

/**
 * Split the request into a vector of strings, separated by spaces.
 * 
 * @param request the data sent by the client.
 * @return vector containing all the arguments present in the request.
*/
std::vector<std::string>	Server::splitRequest(std::string request)
{
	std::vector<std::string>	res;
	size_t pos = 0;
	size_t posend = 0;
	while (pos != std::string::npos) {
		pos = request.find_first_not_of(" \n", posend);
		if (pos != std::string::npos) {
			if (request[pos] == ':') {
				if (request[pos + 1])
					res.push_back(request.substr(pos + 1, request.length() - pos));
				break;
			}
			posend = request.find_first_of(" \n", pos);
			if (posend == std::string::npos)
				posend = request.length();
			res.push_back(request.substr(pos, posend - pos));
		}
	}
	return (res);
}