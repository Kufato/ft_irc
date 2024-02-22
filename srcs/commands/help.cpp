/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:26:45 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/22 15:07:09 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

/**
 * Send RPL_HELP to a client
 *
 * @param client the client to receive the RPL
*/
void Server::help(Client &client) {
	return (dispLogs(RPL_HELP, client.getSocket()));
}