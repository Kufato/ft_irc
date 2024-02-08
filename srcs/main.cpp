/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:04:34 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/08 14:49:53 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Channel.hpp"

int main (int argc, char **argv) {
	if (argc != 3) {
		std::cerr << "Wrong number of arguments" << std::endl;
		return (1);
	}
	try {
		Server server(atoi(argv[1]), argv[2]);
		server.createServer();
		server.lauchServer();
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	
	return (0);
}