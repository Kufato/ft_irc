/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:10:15 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/01 11:02:29 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// Constructor/Destructor
Server::Server(int port, std::string password) {
	this->_port = port;
	this->_password = password;
	this->_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_serverSocket == -1)
		throw std::logic_error("Couldn't create socket.");
	this->_serverAddr.sin_family = AF_INET;
	this->_serverAddr.sin_port = htons(port);
	this->_serverAddr.sin_addr.s_addr = INADDR_ANY;
}

Server::~Server(void) {
	close (this->_epollFd);
	close (this->_serverSocket);
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
	if (bind(this->_serverSocket, (struct sockaddr*)&this->_serverAddr, sizeof(this->_serverAddr))) {
		perror("Bind");
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
		std::cout << event_count << std::endl;
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
		throw std::logic_error("Couldn't accept new client");
	fcntl(clientFd, F_SETFL, O_NONBLOCK);
	this->_event.events = EPOLLIN;
	this->_event.data.fd = clientFd;
	if (epoll_ctl(this->_epollFd, EPOLL_CTL_ADD, clientFd, &this->_event))
		throw std::logic_error("Couldn't add the new client");
	this->_listClients.insert(std::pair<int, Client *>(clientFd, new Client(clientFd)));
	std::cout << "Connection establish'ed sheeran" << std::endl;
	send(clientFd, "Please enter the server's password using : PASS <password>\n", 59, 0);
	return ;
}

/**
 * Read the data sent by a client.
 * 
 * The data can be received incorrectly, and the connection can be closed by the client.
 * 
 * @param clientSocket the socket of the client sending data.
*/
void	Server::handleClient(int clientSocket) {
	int			bytesRead;
	char		buff[2048];
	std::string	strBuff;
	
	memset(&buff, 0, sizeof(buff));
	bytesRead = recv(clientSocket, buff, sizeof(buff), 0);
	strBuff = buff;
	if (strBuff.find("/n")) {
		if (bytesRead <= 0) {
			if (!bytesRead)
				std::cout << "Connection with client closed." << std::endl;
			else
				std::cerr << "Error receiving data from client." << std::endl;
		}
		std::cout << "Received : " << buff << std::endl;
		std::map<int, Client*>::iterator it = _listClients.find(clientSocket);
		Client *client = it->second ; // need to get the adress of the client object whose socket = clientSocket
		client->setSocket(clientSocket);
		// std::string	msg = this->handleRequest(*client, buff);
		// if (msg != "")
		// 	send(clientSocket, msg.c_str(), msg.length(), 0);
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
		pos = request.find_first_not_of(" \n", posend);
		if (pos != std::string::npos)
		{
			if (request[pos] == ':')
			{
				if (request[pos + 1])
					res.push_back(request.substr(pos, request.length() - pos));
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
//labite
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
	std::cout << "Splitted request (" << vecSize << ") : ";
	for(unsigned int i = 0; i < vecSize; i++)
	{
		std::cout << "\"" << cmd[i] << "\"" << " ";
	}
	std::cout << std::endl;
	std::string commands[10] = {"PASS", "NICK", "USER", "KICK", "INVITE", "TOPIC", "MODE", "PRIVMSG", "JOIN", "HELP"};
	int i;
	for (i = 0; i < 7; i++) {
		if (cmd[0] == commands[i])
		{
			std::cout << "Found command " << commands[i] << std::endl;
			break;
		}
	}
	if (i && !client.isRegistered())
	if (i > 2 && !client.isLogged())
	{
		return ();
	}
	switch (i) {
		case 0:
			return (this->pass(client, cmd));
		case 1:
			return (this->nick(client, cmd));
		case 2:
			return (this->user(client, cmd));
		case 3:
			return (this->kick());
		case 4:
			return (this->invite());
		case 5:
			return (this->topic());
		case 6:
			return (this->mode());
		case 7;
			return (this->privmsg(client, cmd));
	}
	return ();
}