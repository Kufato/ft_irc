/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:54:00 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/12 14:46:41 by axcallet         ###   ########.fr       */
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
	if (cmd.size() < 2)
		return (dispLogs(ERR_NEEDMOREPARAMS(client.getNickname(), concatString(cmd)), client.getSocket()));
	if (cmd.size() > 2)
		return (dispLogs(ERR_TOOMUCHPARAMS(client.getNickname(), concatString(cmd)), client.getSocket()));
	if (this->_password == cmd[1]) {
		client.setLogged(true);
		// return (dispLogs(RPL_PASSACCEPTED, client.getSocket(), NULL));
	}
	else
		return (dispLogs(ERR_PASSWDMISMATCH(client.getNickname()), client.getSocket()));
}