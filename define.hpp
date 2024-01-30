/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:45:03 by axcallet          #+#    #+#             */
/*   Updated: 2024/01/30 17:27:53 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

//MSG PASS
#define RPL_PASSACCEPTED		"Password accepted - you are now registered"
#define	ERR_PASSWDMISMATCH		"Password incorrect"
#define ERR_ALREADYREGISTRED	"You are already registered"

//MSG NICK
#define RPL_WELCOME				"Welcome to the Internet Relay Network !"
#define ERR_NONICKNAMEGIVEN 	"no nickname given"
#define ERR_ERRONEUSNICKNAME 	"invalid character in your nickname"
#define ERR_NICKNAMEINUSE		"nickname is already in use"

//MSG OTHER
#define ERR_NEEDMOREPARAMS		"Not enough parameters"
#define ERR_TOOMANYPARAMS		"Too many parameters"
