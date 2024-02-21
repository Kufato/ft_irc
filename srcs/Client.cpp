/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:49:34 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/21 18:06:54 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Channel.hpp"

/**
 * Constructor of Channel
*/
Client::Client(int socket) : _socket(socket), _username(""), _nickname("") {
	this->_logged = false;
	this->_registered = false;
}

/**
 * Destructor of Channel
*/
Client::~Client(void) {
	return ;
}
