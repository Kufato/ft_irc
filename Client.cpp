/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:49:34 by axcallet          #+#    #+#             */
/*   Updated: 2024/01/25 16:50:15 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

Client::Client(int socket) : _clientSocket(socket), _username("unregistered"), _nickname("unregistered") {
	this->_clientSocket = socket;
	this->_logged = false;
	this->_registered = false;
}

Client::~Client(void) {

}
