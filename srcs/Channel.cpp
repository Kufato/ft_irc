/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:53:42 by axcallet          #+#    #+#             */
/*   Updated: 2024/03/11 10:17:09 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Channel.hpp"

/**
 * Constructor of Channel
*/
Channel::Channel(std::string name) : _clientLimit(10), _inviteOnly(false), _restrictTopic(false), _name(name), _topic(""), _password("")
{
}

/**
 * Destructor of Channel
*/
Channel::~Channel()
{
}

/**
 * Add a client as a new member of the channel
 *
 * A pair consisting of the client and his status on the channel
 * (false for regular member, true for operator) is added to a vector
 * @param client the client to add
*/
void	Channel::addClient(Client *client)
{
	std::pair<Client *, bool> newClient(client, false);
	_members.push_back(newClient);
}

/**
 * Set the status of a client in the channel to the mode specified
 * (false for regular member, true for operator)
 *
 * @param client the client targeted
 * @param mode the new mode of the client
*/
void	Channel::opClient(Client *client, bool mode)
{
	std::vector<std::pair<Client *, bool> >::iterator clientmp = this->findMember(client->getNickname());
	if (clientmp != _members.end())
		clientmp->second = mode;
}

/**
 * Search for a member by using his nickname
 *
 * @param nickname the nickname of the member
 * @return an iterator of the pair containing the client, the end of the vector if not found
*/
std::vector<std::pair<Client *, bool> >::iterator	Channel::findMember(std::string nickname)
{
	std::vector<std::pair<Client *, bool> >::iterator it;
	for (it = _members.begin(); it != _members.end(); it++)
	{
		if (it->first->getNickname() == nickname)
			return it;
	}
	return it;
}

/**
 * Search for a client in the channel and indicate if they are a member
 *
 * @param client the client to search
 * @return true if the client is a member of the channel, false if they are not
*/
bool	Channel::memberPresent(Client client)
{
	std::vector<std::pair<Client *, bool> >::iterator it;
	for (it = _members.begin(); it != _members.end(); it++)
	{
		if (it->first->getNickname() == client.getNickname())
			return (true);
	}
	return (false);
}

/**
 * Send a RPL_NAMREPLY to the client given, containing the list
 * of all the members of a channel and their grade (@ for operators,
 * + for regular members)
 *
 * @param client the client to send the RPL_NAMREPLY to
*/
std::string		Channel::namReplyMsg(Client client)
{
	std::string s = ": 353 " + client.getNickname() + " = " + _name + " : ";
	for (std::vector<std::pair<Client *, bool> >::iterator it = _members.begin(); it != _members.end(); it++)
	{
		if (it->second)
			s += "@";
		else
			s += "+";
		s += it->first->getNickname();
		s += " ";
	}
	s += "\r\n";
	return s;
}

/**
 * Send given message to all members of the channel
 *
 * @param msg the message to send
*/
void	Channel::sendToAll(std::string msg)
{
	for (std::vector<std::pair<Client *, bool> >::iterator it = _members.begin(); it != _members.end(); it++)
		send(it->first->getSocket(), msg.c_str(), msg.length(), 0);
}

/**
 * Send given message to all operators of the channel
 *
 * @param msg the message to send
*/
void	Channel::sendToAllOp(std::string msg)
{
	for (std::vector<std::pair<Client *, bool> >::iterator it = _members.begin(); it != _members.end(); it++) {
		if (it->second)
			send(it->first->getSocket(), msg.c_str(), msg.length(), 0);
	}
}

/**
 * Send given message to all regular members of the channel
 *
 * @param msg the message to send
*/
void	Channel::sendToAllNonOp(std::string msg)
{
	for (std::vector<std::pair<Client *, bool> >::iterator it = _members.begin(); it != _members.end(); it++) {
		if (!it->second)
			send(it->first->getSocket(), msg.c_str(), msg.length(), 0);
	}
}

/**
 * Search for a client and erase them from the vector containing the members
 *
 * @param targetName the name of the client targeted
 * @return an iterator to the next client in the vector if the target is erased,
 * an ierator to the end of the vector if not
*/
std::vector<std::pair<Client *, bool> >::iterator	Channel::eraseClient(std::string targetName) {
	std::vector<std::pair<Client *, bool> >::iterator target = this->findMember(targetName);
	if (target != this->_members.end())
		return (this->_members.erase(target));
	return (target);
}

/**
 * Show a list of the members present in the channel
*/
void	Channel::showMembers(void)
{
	std::cout << "List of members of " << _name << ":" << std::endl;
	for (std::vector<std::pair<Client *, bool> >::iterator it = _members.begin(); it != _members.end(); it++)
		std::cout << it->first << std::endl;
}

// Getters
int										Channel::getClientLimit() { return _clientLimit; }

bool									Channel::isInviteOnly() { return _inviteOnly; }

bool									Channel::isTopicRestricted() { return _restrictTopic; }

std::string								Channel::getName() { return _name; }

std::string								Channel::getTopic() { return _topic; }

std::string								Channel::getPassword() { return _password; }

std::vector<std::pair<Client *, bool> >	&Channel::getMembers() { return _members; }

int	Channel::getNbOperator() {
	int	i = 0;

	for (std::vector<std::pair<Client *, bool> >::iterator it = _members.begin(); it != _members.end(); it++)
		i++;
	return (i);
}

// Setters
void	Channel::setName(std::string name) { _name = name; }

void	Channel::setTopic(std::string topic) { _topic = topic; }

void	Channel::setInviteMode(bool mode) { _inviteOnly = mode; }

void	Channel::setClientLimit(int limit) { _clientLimit = limit; }

void	Channel::setRestictMode(bool mode) { _restrictTopic = mode; }

void	Channel::setPassword(std::string password) { _password = password; }
