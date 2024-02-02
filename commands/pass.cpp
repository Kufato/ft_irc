, NULL/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:54:00 by axcallet          #+#    #+#             */
/*   Updated: 2024/01/31 13:54:00 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

/**
 * Tries to log the client using the password they provided.
 * 
 * @param client the client who tries to log in.
 * @param cmd the request separated in args (first one is "PASS", second one is the value, ...)
 * @return the message to send back to the client.
*/
void	Server::pass(Client &client, std::vector<std::string> cmd)
{
	if (cmd.size() == 1)
		return (dispLogs(ERR_NEEDMOREPARAMS, client.getSocket(), NULL));
	if (cmd.size() > 2)
		return (dispLogs(ERR_TOOMANYPARAMS, client.getSocket(), NULL));
	if (this->_password == cmd[1])
	{
		client.setLogged(true);
		return (dispLogs(RPL_PASSACCEPTED, client.getSocket(), NULL));
	}
	else
		return (dispLogs(ERR_PASSWDMISMATCH, client.getSocket(), NULL));
}