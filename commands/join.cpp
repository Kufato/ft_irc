#include "../inc/ft_irc.hpp"

void Server::join(Client &client, std::vector<std::string> cmd) {
    if (cmd.size() < 2 || cmd[1].empty())
        return (dispLogs(ERR_NEEDMOREPARAMS, client.getSocket()));
    if (cmd.size() > 3)
        return (dispLogs(ERR_TOOMANYPARAMS, client.getSocket()));
//    if (cmd.size == 2) //&& le channel est inviteonly)
 //       return (dispLogs("il faut un mdp pour les inviteonlychannel"), client.getSocket)
//     if (cmd.size == 3 && le channel est pas inviteonly
//          return (dispLogs("pas besoin de 3e arg pour un channel pas en inviteonly"), client.getSocket())
//    if (cmd.size() == 2)
        //create/join channel
    // if (cmd.size() == 3)
//      join private channel with key cmd[3]

}