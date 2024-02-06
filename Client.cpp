/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:49:34 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/06 15:15:21 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/Client.hpp"

Client::Client(int socket) : _socket(socket), _username(""), _nickname("") {
	this->_logged = false;
	this->_registered = false;
}

Client::~Client(void) {
	return ;
}
