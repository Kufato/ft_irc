/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:07:38 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/02 15:23:38 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <vector>
#include <fcntl.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

#include <stdio.h>

#include "Client.hpp"
#include "Server.hpp"
#include "Channel.hpp"

//MSG PASS
#define RPL_PASSACCEPTED		": Password accepted - you are now registered"
#define	ERR_PASSWDMISMATCH		"Error: password incorrect"
#define ERR_ALREADYREGISTRED	"Error: you are already registered"

//MSG NICK
#define RPL_WELCOME				": Welcome to the Internet Relay Network !"
#define ERR_SAMENICKNAME		"Error: you already have this nickname"
#define ERR_NONICKNAMEGIVEN 	"Error: no nickname given"
#define ERR_ERRONEUSNICKNAME 	"Error: invalid character in your nickname"
#define ERR_NICKNAMEINUSE		"Error: nickname is already in use"

//MSG USER
#define	ERR_ALREADYREGISTRED	"Error: you are already registered"

//MSG PRIVMSG
#define ERR_NOUSERFOUND			"Error: the user doesn't exist"
#define ERR_NOTEXTTOSEND 		"Error: your message cannot be empty"
#define ERR_NOCHANNELFOUND 		"Error: the channel doesn't exist"

//MSG MODE
#define ERR_NOOPERATOR			"Error: your are oerator in this channel"
#define ERR_UNKNOWNMODE			"Error: mode doesn't exist."
#define ERR_NOTONCHANNEL		"Error: client is not in this channel"
#define ERR_CHANOPRIVSNEEDED	"Error: channel operator privileges requiered"
#define ERR_NOTINRANGE			"Error: number given is too high/low"
#define RPL_CHANNELMODEIS		": mode changed successfully"

//MSG KICK
#define RPL_KICK				": your are kick from a channel"
#define ERR_AUTOKICK			"Error: you can't autokick"
#define ERR_NOTONCHANNEL		"Error: this client is not on this channel"

//MSG INVITE
#define RPL_INVITE				": you have receive a invitation for the channel"
#define RPL_SENDINVITATION		": you have send a invitation to"

//MSG HELP
#define RPL_HELP				"Here is the list of all available commands :\n \
								PASS : use it when you need to log and enter the password\n \
								NICK : set a new NickName\n \
								USER : set a new UserName\n \
								KICK : eject a client from the channel\n \
								INVITE : invite a client to a channel\n \
								TOPIC : change or view the channel topic\n \
								PRIVMSG : send a private message\n \
								JOIN : joins a channel\n \
								MODE : change the channel's mode\n 	\
								i: set/remove invite only channel\n 	\
								t: set/remove the restrictions of the TOPIC command to channel operators\n 	\
								k: set/remove the channel key (password)\n 	\
								o: give/take channel operator privilege\n 	\
								l: set/remove the user limit to channel\n"

//MSG OTHER
#define ERR_NEEDMOREPARAMS		"Error: not enough parameters"
#define ERR_TOOMANYPARAMS		"Error: too many parameters"
#define ERR_INVALIDCHAR			"Error: character(s) used is invalid"


bool	checkCharacters(std::string s);