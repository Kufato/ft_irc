#include "../inc/ft_irc.hpp"

void Server::join(Client &client, std::vector<std::string> cmd) {
    (void)client;
    (void)cmd;
//     if (cmd.size() < 2 || cmd[0].empty())
//         return (dispLogs(ERR_NEEDMOREPARAMS, client.getSocket(), NULL));
//     if (cmd.size() > 3)
//         return (dispLogs(ERR_TOOMANYPARAMS, client.getSocket(), NULL));
//     if (!searchNameChannel(cmd[2])) {
//         if (cmd.size() == 3)
//             return (dispLogs("pas besoin de 3e arg pour creer un channel", client.getSocket(), NULL));
// //    if (cmd.size() == 2)
// //       create channel
//     }
//     else { // (le channel existe)
//         if (cmd.size() == 2 && isInviteOnly())
//             return (dispLogs("il faut un mdp pour les inviteonlychannel", client.getSocket(), NULL));
//         if (cmd.size() == 3 && !isInviteOnly())
// //       return (dispLogs("arg en trop pour private channel"), client.getSocket)
// //    if (cmd.size() == 3 && isInviteOnly)
// //      join private channel with key cmd[3]
// //    if (cmd.size() == 2 && !inInviteOnly)        
// //      join channel;
// //    }
}