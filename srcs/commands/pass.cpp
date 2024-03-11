/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:54:00 by axcallet          #+#    #+#             */
/*   Updated: 2024/03/11 11:33:02 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_irc.hpp"

/**
 * Tries to log the client using the password they provided.
 * 
 * @param client the client who tries to log in.
 * @param cmd the request separated in args (first one is "PASS", second one is the value, ...)
 * @return the message to send back to the client.
*/
void	Server::pass(Client &client, std::vector<std::string> cmd)
{
	if (client.isRegistered())
		return (dispLogs(ERR_ALREADYREGISTERED(client.getNickname()), client.getSocket()));
	if (checkFormat(cmd, client, 2, 2))
		return ;
	if (this->_password == cmd[1]) {
		client.setLogged(true);
		return (dispLogs("You may enter the 'NICK <nickname>' and 'USER <username>' commands\r\n", client.getSocket()));
	}
	else
		return (dispLogs(ERR_PASSWDMISMATCH(client.getNickname()), client.getSocket()));
	std::cout << "Connexion au serveur IRC réussie !" << std::endl;	
}