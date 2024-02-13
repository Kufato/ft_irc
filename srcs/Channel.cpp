#include "../inc/Channel.hpp"

Channel::Channel(std::string name) : _clientLimit(10), _inviteOnly(false), _restrictTopic(false), _name(name), _topic(""), _password("")
{
}

Channel::~Channel()
{
}

void	Channel::addClient(Client *client)
{
	std::pair<Client *, bool> newClient(client, false);
	_members.push_back(newClient);
}

void	Channel::opClient(Client *client, bool mode)
{
	std::vector<std::pair<Client *, bool> >::iterator clientmp = this->findMember(*client);
	if (clientmp != _members.end())
		clientmp->second = mode;
}

std::vector<std::pair<Client *, bool> >::iterator	Channel::findMember(Client client)
{
	std::vector<std::pair<Client *, bool> >::iterator it;
	for (it = _members.begin(); it != _members.end(); it++)
	{
		if (it->first->getNickname() == client.getNickname())
		{
			std::cout << it->first->getNickname() << std::endl;
			return (it);
		}
	}
	return (_members.end());
}

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

// Getters
int			Channel::getClientLimit() { return _clientLimit; }

bool		Channel::isInviteOnly() { return _inviteOnly; }

bool		Channel::isTopicRestricted() { return _restrictTopic; }

std::string	Channel::getName() { return _name; }

std::string	Channel::getTopic() { return _topic; }

std::string	Channel::getPassword() { return _password; }

std::vector<std::pair<Client *, bool> >	Channel::getMembers() { return _members; }

// Setters
void	Channel::setName(std::string name) { _name = name; }

void	Channel::setTopic(std::string topic) { _topic = topic; }

void	Channel::setPassword(std::string password) { _password = password; }

void	Channel::setClientLimit(int limit) { _clientLimit = limit; }

void	Channel::setInviteMode(bool mode) { _inviteOnly = mode; }

void	Channel::setRestictMode(bool mode) { _restrictTopic = mode; }