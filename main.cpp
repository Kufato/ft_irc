/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:04:34 by axcallet          #+#    #+#             */
/*   Updated: 2024/01/25 13:42:44 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

static bool	checkInfos(std::string port, std::string password, Server server) {
	if (atoi(port.c_str()) != server.getPort())
		return (false);
	if (password != server.getPassword())
		return (false);
	return (true);
}

int main (int argc, char **argv) {
	if (argc != 3) {
		std::cerr << "Wrong number of arguments" << std::endl;
		return (1);
	}
	Server server;
	if (!checkInfos(argv[1], argv[2], server)) {
		std::cerr << "Wrong arguments" << std::endl;
		return (1);
	}
	server.createServer();
	server.lauchServer();
	
	return (0);
}