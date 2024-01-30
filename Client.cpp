/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:49:34 by axcallet          #+#    #+#             */
/*   Updated: 2024/01/30 17:17:19 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

Client::Client(int socket) : _socket(socket), _username(NULL), _nickname(NULL) {
	this->_logged = false;
	this->_registered = false;
}

Client::~Client(void) {
	return ;
}
