/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:07:38 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/21 18:21:25 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

gbretgbert  5gbert #pragma once

#include <map>
#include <vector>
#include <cstdio>
#include <fcntl.h>
#include <cstdlib>
#include <cstring>
#include <signal.h>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "Client.hpp"
#include "Server.hpp"
#include "Channel.hpp"

// Functions
void			newSignal(int signum);
bool			checkCharacters(std::string s);
std::string		concatString(std::vector<std::string> cmd);
bool			checkFormat(std::vector<std::string> cmd, Client client, int u, int o);

// Defines
#define ERR_NOTINRANGE(client)							(": " + client + " :You're not in the authorized range\r\n")
// #define ERR_NORECIPIENT(client)							(": 411 " + client + " :No recipient given PRIVMSG\r\n")
#define ERR_CMDNOTFOUND(client)							(": 421 " + client + " :Command not found\r\n")
#define ERR_UNKNOWNMODE(client)							(": 472 " + client + " :Is unknown mode char\r\n")
#define ERR_NOTEXTTOSEND(client)						(": 412 " + client + " :No text to send\r\n")
#define ERR_SAMENICKNAME(client)						(": " + client + " :There is already your nickname\r\n")
// #define ERR_NOTREGISTERED(client)						(": 451 " + client + " :You have not registered\r\n")
#define ERR_BADCHAR(client, name)						(": " + client + " " + name + " :Error you have used forbidden characters\r\n")
#define ERR_PASSWDMISMATCH(client)						(": 464 " + client + " :Incorrect password\r\n")
#define ERR_NOSUCHNICK(client, nick)					(": 401 " + client + " " + nick + " :No such nickname\r\n")
// #define ERR_UMODEUNKNOWNFLAG(client)					(": 501 " + client + " :Unknown MODE flag\r\n")
#define ERR_PASSCREATECHANNEL(client)					(": " + client +  " :Channel don't need password at creation\r\n")
#define ERR_ALREADYREGISTERED(client)					(": 462 " + client + " :You may not reregister\r\n")
#define ERR_AUTOKICK(client, channel)					(": " + client + " " + channel + " :Can't kick yourself\r\n")
#define ERR_ALREADYIN(client, channel)					(": " + client + " " + channel + " :Your are already in the channel\r\n")
#define ERR_TOOMUCHPARAMS(client, cmd)					(": " + client + " " + cmd + " :Too much parameters\r\n")
// #define	ERR_UNKNOWNCOMMAND(client, cmd)					(": " + client + " " + cmd + " :")
#define ERR_NICKNAMEINUSE(client, nick)					(": 433 " + client + " " + nick + " :Nickname is already in use\r\n")
#define ERR_NEEDMOREPARAMS(client, cmd)					(": 461 " + client + " " + cmd + " :Not enough parameters\r\n")
#define ERR_NOTONCHANNEL(client, channel)				(": 442 " + client + " " + channel + " :Not on that channel\r\n")
#define ERR_CHANNELISFULL(client, channel)				(": 471 " + client + " " + channel + " :Cannot join channel (+l)\r\n")
#define ERR_NOSUCHCHANNEL(client, channel)				(": 403 " + client + " " + channel + " :No such channel\r\n")
#define ERR_BADCHANNELKEY(client, channel)				(": 475 " + client + " " + channel + " :Cannot join channel (+k)\r\n")
#define ERR_ERRONUSENICKNAME(client, nick)				(": 432 " + client + " " + nick + " :Erroneus nickname\r\n")
#define ERR_ERRONUSEUSERNAME(client, user)				(": " + client + " " + user + " :Erroneus username\r\n")
#define ERR_ALREADYINVITED(client, channel)				(": " + client + " " + channel + " :This user is already invite\r\n")
#define ERR_BADCHARCHANNEL(client, channel)				(": " + client + " " + channel + " :Channel's name must start with '#'\r\n")
#define ERR_INVITEONLYCHAN(client, channel)				(": 473 " + client + " " + channel + " :Can't join channel (+i)\r\n")
#define ERR_CHANOPRIVSNEEDED(client, channel)			(": 482 " + client + " " + channel + " :You're not channel operator\r\n")
#define ERR_CANNOTSENDTOCHAN(client, channel)			(": 404 " + client + " " + channel + " :Channel is restricted (+t)\r\n")
#define ERR_CANTDESERT(client, channel)					(": " + client + " " + channel + " :You can't desert (try Op'ing another member)\r\n")
// #define ERR_USERONCHANNEL(client, nick, channel)		(": 303 " + client + " " + nick + " " + channel + " :is already on channel\r\n")
// #define ERR_USERNOTINCHANNEL(client, nick, channel)		(": 441 " + client + " " + nick + " " + channel + " :They aren't on that channel\r\n")

//PRIVMSG BUILDERS
#define USER_MESSAGES(client, target, msg)				(":" + client + " PRIVMSG " + target + " :" +  msg + "\r\n")
#define CHANNEL_MESSAGES(client, channel, msg)			(":" + client + " PRIVMSG " + channel + " :" + msg + "\r\n")

//SERVER REPLIES
#define RPL_WELCOME(client)								(": 001 " + client + " :Welcome in the IRC world, " + client + "\r\n")
#define RPL_JOIN(nick, channel)							(":" + nick + " JOIN " + channel + "\r\n")
// #define RPL_PART(client, channel)						(":" + client + " PART " + channel + "\r\n")
// #define RPL_NICK(oldNick, newNick)						(":" + oldNick + " NICK " + newNick + "\r\n")
#define RPL_NOTOPIC(client, channel)					(": 331 " + client + " " + channel + " :No topic is set\r\n")
#define RPL_TOPIC(client, channel, topic)				(": 332 " + client + " " + channel + " :" + topic + "\r\n")
#define RPL_MODE(client, channel, mode, name)			(":" + client + " MODE " + channel + " " + mode + " " + name + "\r\n")
#define RPL_CHANNELMODEIS(client, channel, mode)		(": 324 " + client + " " + channel + " " + mode + "\r\n")
#define RPL_INVITERCVR(client, invitee, channel)		(":" + client + " INVITE " + invitee + " " + channel + "\r\n")
#define RPL_INVITESNDR(client, invitee, channel)		(": 341 " + client + " " + invitee + " " + channel + "\r\n")
#define RPL_KICK(client, channel, target, reason)		(":" + client + " KICK " + channel + " " + target + " :" + reason + "\r\n")

#define RPL_HELP	"Here is the list of all available commands :\r\n \
					PASS : use it when you need to log and enter the password\r\n \
					NICK : set a new NickName\r\n \
					USER : set a new UserName\r\n \
					KICK : eject a client from the channel\r\n \
					INVITE : invite a client to a channel\r\n \
					TOPIC : change or view the channel topic\r\n \
					PRIVMSG : send a private message\r\n \
					JOIN : joins a channel\r\n \
					MODE : change the channel's mode\r\n 	\
					i: set/remove invite only channel\r\n 	\
					t: set/remove the restrictions of the TOPIC command to channel operators\r\n 	\
					k: set/remove the channel key (password)\r\n 	\
					o: give/take channel operator privilege\r\n 	\
					l: set/remove the user limit to channel\r\n"