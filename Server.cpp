/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:10:15 by axcallet          #+#    #+#             */
/*   Updated: 2024/01/25 18:22:58 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

// Constructor/Destructor
Server::Server(void) {
	this->_port = 6969;
	this->_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_serverSocket == -1)
		throw std::logic_error("Couldn't create socket.");
	this->_serverAddr.sin_family = AF_INET;
	this->_serverAddr.sin_port = htons(6969);
	this->_serverAddr.sin_addr.s_addr = INADDR_ANY;
}

Server::~Server(void) {
	close (this->_epollFd);
	close (this->_serverSocket);
	return ;
}

// Public methods
void	Server::createServer() {
	if (bind(this->_serverSocket, (struct sockaddr*)&this->_serverAddr, sizeof(this->_serverAddr))) {
		close (this->_serverSocket);
		throw std::logic_error("Couldn't bind socket.");
	}
	if (listen(this->_serverSocket, 69)) {
		close (this->_serverSocket);
		throw std::logic_error("Couldn't listen for connections.");
	}
	if (this->_epollFd = epoll_create1(0)) {
		close (this->_serverSocket);
		throw std::logic_error("Couldn't create the epoll instance.");
	}
	this->_event.events = EPOLLIN;
	this->_event.data.fd = this->_serverSocket;
	if (epoll_ctl(this->_epollFd, EPOLL_CTL_ADD, this->_serverSocket, &this->_event)) {
		close (this->_epollFd);
		close (this->_serverSocket);
		throw std::logic_error("Couldn't add the server socket to the epoll instance.");
	}
	return ;
}

void	Server::lauchServer(void) {
	int					event_count;
	struct epoll_event	events[100];

	while (true) {
		event_count = epoll_wait(this->_epollFd, events , 100, -1);
		for (int i = 0; i < event_count; i++) {
			if (events[i].data.fd == this->_serverSocket)
				handleNewClient();
			else
				handleClient(events[i].data.fd);
		}
	}
	return ;
}

void	Server::handleNewClient(void) {
	int					clientFd;
	struct sockaddr_in	clientAddr;
	socklen_t			clientAddrLen = sizeof(struct sockaddr);

	memset(&clientAddr, 0, clientAddrLen);
	clientFd = accept(this->_serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
	if (clientFd == -1)
		throw std::logic_error("Couldn't accept new client");
	fcntl(clientFd, F_SETFL, O_NONBLOCK);
	if (epoll_ctl(this->_epollFd, EPOLL_CTL_ADD, clientFd, &this->_event))
		throw std::logic_error("Couldn't add the new client");
	this->_listClients.insert(std::pair<int, Client *>(clientFd, new Client(clientFd)));
	return ;
}

/**
 * Read the data sent by a client.
 * 
 * The data can be received incorrectly, and the connection can be closed by the client.
 * 
 * @param clientSocket the socket of the client sending data.
*/
void	Server::handleClient(int clientSocket)
{
	char	buff[2048];
	int		bytesRead;
	
	while (true) {
		bytesRead = recv(clientSocket, buff, sizeof(buff), 0);
		if (bytesRead <= 0) {
			if (!bytesRead)	
				std::cout << "Connection with client closed." << std::endl;
			else
				std::cerr << "Error receiving data from client." << std::endl;
			break;
		}
		Client client = NULL; // need to get the adress of the client object whose socket = clientSocket
		std::string	msg = this->handleRequest(client, buff);
		if (msg != "")
			send(clientSocket, msg.c_str(), msg.length(), 0);
	}
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
	while (pos != std::string::npos)
	{
		pos = request.find_first_not_of(' ', posend);
		if (pos != std::string::npos)
		{
			posend = request.find(' ', pos);
			if (posend == std::string::npos)
				posend = request.length();
			res.push_back(request.substr(pos, posend - pos));
		}
	}
	return (res);
}

/**
 * Parse the request of a client and execute it if possible.
 * 
 * @param client the client who sent the request.
 * @param request the data sent by the client.
 * @return the message to send back to the client.
*/
std::string	Server::handleRequest(Client &client, std::string request)
{
	std::vector<std::string> cmd = this->splitRequest(request);
	std::string commands[7] = {"PASS", "NICK", "USER", "KICK", "INVITE", "TOPIC", "MODE"};
	int i;
	for (i = 0; i < 7; i++)
	{
		if (cmd[0] == commands[i])
			break;
	}
	if (i && !client.isLogged())
		return ("Please enter the server's password using : PASS <password>\n");
	else if (i > 2 && !client.isRegistered())
		return ("Please enter a nickname and a username using : NICK <nickname>  and  USER <username>\n");
	switch (i)
	{
		case 0:
			return (this->logClient(client, cmd));
	}
}

/**
 * Tries to log the client using the password they provided.
 * 
 * @param client the client who tries to log in.
 * @param cmd the request separated in args (first one is "PASS", second one is the value, ...)
 * @return the message to send back to the client.
*/
std::string	Server::logClient(Client &client, std::vector<std::string> cmd)
{
	if (cmd.size() != 2)
		return ("Incorrect number of argument.");
	if (this->_password == cmd[1])
	{
		client.setLogged(true);
		return ("Successfully logged to the server.");
	}
	else
		return ("Password incorrect, try again.");
}