/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:04:34 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/27 19:49:56 by ajoliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_irc.hpp"

int main (int argc, char **argv) {
	if (argc != 3) {
		std::cerr << "Wrong number of arguments" << std::endl;
		return (1);
	}
	std::string tmp = argv[1];
	if (tmp.find_first_not_of("0123456789") != std::string::npos)
	{
		std::cout << "the port must have only numeric characters" << std::endl;
		return (1);
	}
	try {
		Server server(atoi(argv[1]), argv[2]);
		signal(SIGINT, newSignal);
		server.createServer();
		server.lauchServer();
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	
	return (0);
}
