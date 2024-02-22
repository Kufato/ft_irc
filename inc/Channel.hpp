/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:03:16 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/22 14:27:05 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_irc.hpp"

class	Client;
class	Server;

class	Channel {

	private: 
		int										_clientLimit;
		bool									_inviteOnly;
		bool									_restrictTopic;
		std::string								_name;
		std::string								_topic;
		std::string								_password;
		std::vector<std::pair<Client *, bool> > _members;

	public:
	// Constructor / Destructor
		Channel(std::string name);
		~Channel();

	// Public methods
		void												showMembers(void);
		void												addClient(Client *client);
		void												sendToAll(std::string msg);
		void												sendToAllOp(std::string msg);
		bool												memberPresent(Client client);
		void												sendToAllNonOp(std::string msg);
		void												opClient(Client *client, bool mode);
		std::string											namReplyMsg(Client client);
		std::vector<std::pair<Client *, bool> >::iterator	findMember(std::string nickname);
		std::vector<std::pair<Client *, bool> >::iterator	eraseClient(std::string targetName);

	// Getters
		int										getNbOperator();
		int										getClientLimit();
		bool									isInviteOnly();
		bool									isTopicRestricted();
		std::string								getName();
		std::string								getTopic();
		std::string								getPassword();
		std::vector<std::pair<Client *, bool> >	&getMembers();

	// Setters
		void	setInviteMode(bool mode);
		void	setName(std::string name);
		void	setClientLimit(int limit);
		void	setRestictMode(bool mode);
		void	setTopic(std::string topic);
		void	setPassword(std::string password);
};
