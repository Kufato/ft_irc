#include "../ft_irc.hpp"
#include "../define.hpp"

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
		return (dispLogs(ERR_NEEDMOREPARAMS, client.getSocket()));
	if (cmd.size() > 2)
		return (dispLogs(ERR_TOOMANYPARAMS, client.getSocket()));
	if (this->_password == cmd[1])
	{
		client.setLogged(true);
		return (dispLogs(RPL_PASSACCEPTED, client.getSocket()));
	}
	else
		return (dispLogs(ERR_PASSWDMISMATCH, client.getSocket()));
}