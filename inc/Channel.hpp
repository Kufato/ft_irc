/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:03:16 by axcallet          #+#    #+#             */
/*   Updated: 2024/02/06 15:03:07 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_irc.hpp"

class	Client;
class	Server;

class Channel
{
	private: 
		std::string								_name;
		std::string								_topic;
		std::string								_password;
		std::vector<std::pair<Client *, bool> > _members;
		int										_clientLimit;
		bool									_inviteOnly;
		bool									_restrictTopic;
	public:
		Channel(std::string name);
		~Channel();
		void						addClient(Client *client);
		void						opClient(Client *client, bool mode);
		std::vector<std::pair<Client *, bool> >::iterator	findMember(Client client);

		// Getters
		std::string								getName();
		std::string								getTopic();
		std::string								getPassword();
		std::vector<std::pair<Client *, bool> >	getMembers();
		int										getClientLimit();
		bool									isInviteOnly();
		bool									isTopicRestricted();

		// Setters
		void	setName(std::string name);
		void	setTopic(std::string topic);
		void	setPassword(std::string password);
		void	setClientLimit(int limit);
		void	setInviteMode(bool mode);
		void	setRestictMode(bool mode);
};
