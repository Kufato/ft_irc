 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:10:15 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/09 18:03:25 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

// Constructor/Destructor
Server::Server(int port, std::string password) {
	this->_port = port;
	this->_password = password;
	this->_bot = false;
	this->_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	this->_epollFd = 0;
	if (this->_serverSocket == -1)
		throw std::logic_error("Couldn't create socket.");
	this->_serverAddr.sin_family = AF_INET;
	this->_serverAddr.sin_port = htons(port);
	this->_serverAddr.sin_addr.s_addr = INADDR_ANY;
}

Server::~Server(void) {
	if (this->_epollFd)
		close (this->_epollFd);
	if (this->_bot)
		close (this->_botSocket);
	close (this->_serverSocket);
	for (std::map<int, Client *>::iterator it = this->_listClients.begin(); it != this->_listClients.end(); it++) {
		close(it->second->getSocket());
		delete it->second;
	}
	for (std::map<std::string, Channel *>::iterator it = this->_listChannels.begin(); it != this->_listChannels.end(); it++)
		delete it->second;
	return ;
}

// ++++++++++ Public methods ++++++++++

/**
 * Binding socket to port address.
 * Listening to the socket
 * Creation of the epoll instance
 * Add server socket to epoll instance
*/
void	Server::createServer() {
	int	opt = 1;

	if (setsockopt(this->_serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
		std::perror("Bind");
		close (this->_serverSocket);
		throw std::logic_error("Error with setsockopt.");
	}
	if (bind(this->_serverSocket, (struct sockaddr*)&this->_serverAddr, sizeof(this->_serverAddr))) {
		std::perror("Bind");
		close (this->_serverSocket);
		throw std::logic_error("Couldn't bind socket.");
	}
	if (listen(this->_serverSocket, 69)) {
		close (this->_serverSocket);
		throw std::logic_error("Couldn't listen for connections.");
	}
	if ((this->_epollFd = epoll_create1(0)) == -1) {
		close (this->_serverSocket);
		throw std::logic_error("Couldn't create the epoll instance.");
	}
	this->_event.events = EPOLLIN | EPOLLET;
	this->_event.data.fd = this->_serverSocket;
	if (epoll_ctl(this->_epollFd, EPOLL_CTL_ADD, this->_serverSocket, &this->_event)) {
		close (this->_epollFd);
		close (this->_serverSocket);
		throw std::logic_error("Couldn't add the server socket to the epoll instance.");
	}
	std::cout << "Server created successfully." << std::endl;
	return ;
}

/**
 * Waiting for any event with the @param epoll_wait function and stock it
 * 
 * Check if the event is a new connection or another request
*/
void	Server::lauchServer(void) {
	int					event_count;
	struct epoll_event	events[1024];

	while (true) {
		event_count = epoll_wait(this->_epollFd, events , 1024, -1);
		for (int i = 0; i < event_count; i++) {
			if (events[i].data.fd == this->_serverSocket)
				handleNewClient();
			else
				handleClient(events[i].data.fd);
		}
	}
	return ;
}

/**
 * Call the @param accept function to accept a new connection on the server's clientFd socket
 * 
 * Modifying clientFd properties with the @param fcntl function
 * 
 * Call @param epoll_ctl to add file descriptor fd to the set monitored by epoll
 * 
 * Insert the new client in a std::map
*/
void	Server::handleNewClient(void) {
	int					clientFd;
	struct sockaddr_in	clientAddr;
	socklen_t			clientAddrLen = sizeof(struct sockaddr);

	memset(&clientAddr, 0, clientAddrLen);
	clientFd = accept(this->_serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
	if (clientFd == -1)
		throw std::logic_error("Couldn't accept new client"); //NON
	fcntl(clientFd, F_SETFL, O_NONBLOCK);
	this->_event.events = EPOLLIN;
	this->_event.data.fd = clientFd;
	if (epoll_ctl(this->_epollFd, EPOLL_CTL_ADD, clientFd, &this->_event))
		throw std::logic_error("Couldn't add the new client");
	this->_listClients.insert(std::pair<int, Client *>(clientFd, new Client(clientFd)));
	std::cout << "Connection established" << std::endl;
	send(clientFd, "Please enter the server's password using : PASS <password>\r\n", 60, 0);
	return ;
}

/**
 * Read the data sent by a client.
 * 
 * The data can be received incorrectly, and the connection can be closed by the client.
 * The loop prevents data reception from being interrupted and handle all the clients' 
 * requests separated by newlines until there are no requests anymore.
 * 
 * @param clientSocket the socket of the client sending data.
*/
void	Server::handleClient(int clientSocket) {
	int					bytesRead;
	char				buff[2048];
	std::string			request;

	std::map<int, Client*>::iterator	it = _listClients.find(clientSocket);
	if (it == _listClients.end())
		return ;
	Client								*client = it->second;
	
	memset(&buff, 0, sizeof(buff));
	bytesRead = recv(clientSocket, buff, sizeof(buff), 0);
	if (bytesRead <= 0) {
		if (!bytesRead)
		{
			removeClient(client);
			return ;
		}
	}
	client->addBuffer(buff);
	while (client->getBuffer().find_first_not_of("\n\r") != std::string::npos) {
		size_t end = client->getBuffer().find_first_of("\n\r");
		if (end != std::string::npos) {
			request = client->getBuffer().substr(0, end);
			client->addBuffer(client->getBuffer().substr(end + 1, client->getBuffer().length() - request.length())); 
			std::cout << "Received : " << request << std::endl;
			client->setSocket(clientSocket);
			client->getBuffer().clear();
			this->handleRequest(*client, request);
		}
		else
			break;
	}
}

/**
 * Parse the request of a client, execute it if possible
 * then display the answer of the server.
 * 
 * @param client the client who sent the request.
 * @param request the data sent by the client.
*/
void	Server::handleRequest(Client &client, std::string request)
{
	std::vector<std::string> cmd = this->splitRequest(request);
	unsigned int vecSize = cmd.size();
	if (!vecSize)
		return ;
	std::cout << "Splitted request (" << vecSize << ") : ";
	for(unsigned int i = 0; i < vecSize; i++) {
		if (!cmd[i].empty())
			std::cout << "\"" << cmd[i] << "\"" << " ";
	}
	std::cout << std::endl;
	std::string commands[13] = {"PASS", "QUIT", "NICK", "USER", "KICK", "INVITE", "TOPIC", "MODE", "PRIVMSG", "JOIN", "HELP", "WHO", "BOT"};
	int i;
	for (i = 0; i < 13; i++) {
		if (cmd[0] == commands[i])
			break;
	}
	if (i > 1 && !client.isLogged())
		return (dispLogs("Register by using the command PASS <password>\r\n", client.getSocket()));
	if (i > 3 && !client.isRegistered())
		return (dispLogs("Log in by using NICK <nicname> and USER <username>\r\n", client.getSocket()));
	switch (i) {
		case 0:
			return (this->pass(client, cmd));
		case 1:
			return (this->removeClient(&client)); 
		case 2:
			return (this->nick(client, cmd));
		case 3:
			return (this->user(client, cmd));
		case 4:
			return (this->kick(client, cmd));
		case 5:
			return (this->invite(client, cmd));
		case 6:
			return (this->topic(client, cmd));
		case 7:
			return (this->mode(client, cmd));
		case 8:
			return (this->privmsg(client, cmd));
		case 9:
			return (this->join(client, cmd));
		case 10:
			return (this->help(client));
		case 11:
			return ;
		case 12:
			return (this->bot(client));
	}
	return (dispLogs(ERR_CMDNOTFOUND(client.getNickname()), client.getSocket()));
}

/**
 * Close the socket of the client
 * 
 * Remove their socket from epoll
 * Remove the client from the whole server
 *
 * @param client the client to remove
*/
void Server::removeClient(Client *client) {
	close(client->getSocket());
	epoll_ctl(this->_epollFd, EPOLL_CTL_DEL, client->getSocket(), NULL);
	for (std::map<std::string, Channel *>::iterator it = this->_listChannels.begin(); it != this->_listChannels.end(); it++) {
		std::vector<std::pair<Client *, bool> > members = it->second->getMembers();
		std::vector<std::pair<Client *, bool> >::iterator it2 = members.begin();
		while (it2 != members.end()) {
			if (it2->first->getNickname() == client->getNickname()) {
				it2 = it->second->eraseClient(client->getNickname());
				break ;
			}
			else
				it2++;
		}
		it->second->sendToAll(RPL_PART(client->getNickname(), it->second->getName()));
	}
	std::map<int, Client *>::iterator it = this->_listClients.find(client->getSocket());
	if (it != this->_listClients.end())
	{
		this->_listClients.erase(it);
		delete client;
	}
	this->deleteEmptyChannels();
}

/**
 * Delete all the empty channels from the server
*/
void	Server::deleteEmptyChannels(void)
{
	for (std::map<std::string, Channel *>::iterator it = this->_listChannels.begin(); it != this->_listChannels.end();) {
		if (it->second->getMembers().empty()) {
			delete it->second;
			std::map<std::string, Channel *>::iterator tmpit = it;
			it++;
			this->_listChannels.erase(tmpit);
			continue ;
		}
		else if (it->second->getMembers().size() == 1) {
			if (!it->second->getMembers().begin()->second) {
				it->second->opClient(it->second->getMembers().begin()->first, true);
				it->second->sendToAll(RPL_MODE(it->second->getMembers().begin()->first->getNickname(), it->second->getName(), "+o", it->second->getMembers().begin()->first->getNickname()));
			}
		}
		it++;
	}
}

/**
 * Show the name of all the channels of the server and show all their members
*/
void	Server::showChannels(void)
{
	std::cout << "Names of all the current channels:" << std::endl;
	for (std::map<std::string, Channel *>::iterator it = this->_listChannels.begin(); it != this->_listChannels.end(); it++) {
		std::cout << it->second->getName() << std::endl;
		it->second->showMembers();
	}
	std::cout << std::endl;
}