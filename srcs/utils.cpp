/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:33:38 by axcallet          #+#    #+#             */
/*   Updated: 2024/03/22 09:49:46 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_irc.hpp"

/**
 * Search for a client using nickname
 *
 * @param nickname the name to look for
 * @return the adress of the client found, NULL if it isn't found
*/
Client	*Server::searchNameClient(std::string nickname) {
	for (std::map<int, Client *>::iterator it = this->_listClients.begin(); it != this->_listClients.end(); it++) {
		if (it->second->getNickname() == nickname)
			return (it->second);
	}
	return (NULL);
}

/**
 * Search for a channel using a name
 *
 * @param name the name of the channel to look for
 * @return the adress of the channel found, NULL if it isn't found
*/
Channel	*Server::searchNameChannel(std::string name) {
	if (_listChannels.empty())
		return NULL;
	for (std::map<std::string, Channel *>::iterator it = this->_listChannels.begin(); it != this->_listChannels.end(); it++) {
		if (it->first == name)
			return (it->second);
	}
	return (NULL);
}

/**
 * Send a string to a client.
 *
 * @param str the string to send
 * @param clientFD the fd of the target client
*/
void	dispLogs(std::string str, int clientFD) {
	send(clientFD, str.c_str(), str.length(), 0);
}

/**
 * Classic itoa bcz it doesn't exist in c++98 :(
 * 
 * @param n the int to convert
 * @return the converted string
*/
std::string itoa(int n) {
	char buffer[20];
	std::sprintf(buffer, "%d", n);
	return std::string(buffer);
}

/**
 * Check if the string has forbidden characters (listed below)
 *
 * @param s the string to parse
 * @return whether the string is valid or not
*/
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

/**
 * Concatenate all the strings of a vector, putting spaces between elements
 *
 * @param cmd the vector to concatenate
 * @return the resulting string
*/
std::string		concatString(std::vector<std::string> cmd)
{
	if (cmd.empty())
		return ("");
	std::string	s = cmd[0];
	for (size_t i = 1; i < cmd.size(); i++)
		s += " " + cmd[i];
	return s;
}

/**
 * Check if the number of arguments is within the @param l and @param u range. If not, send
 * ERR_NEEDMOREPARAMS or ERR_TOOMUCHPARAMS to the client sending the command
 *
 * @param cmd the command to check
 * @param client the client sending the command
 * @param l the lower bound
 * @param u the upper bound
*/
bool	checkFormat(std::vector<std::string> cmd, Client client, int l, int u)
{
	if ((int)cmd.size() < l)
		dispLogs(ERR_NEEDMOREPARAMS(client.getNickname(), concatString(cmd)), client.getSocket());
	else if ((int)cmd.size() > u)
		dispLogs(ERR_TOOMUCHPARAMS(client.getNickname(), concatString(cmd)), client.getSocket());
	else
		return false;
	return true;
}