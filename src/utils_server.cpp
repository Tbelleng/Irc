#include "server.hpp"
#include "Pars.cpp"
// User&   getUser(int socket_client) {
//     for(std::vector<User*>.iterator it = this->userList.begin(); it != this->userList.end(); it++) {
//         if (it.getFd() == socket_client)
//             return it;
//     }
//     return 0;
// }
//SendMessageTo(client, RPL_JOIN(client->GetNickname(), neededChannels[i_neededChannels]));

void    setReplie(std::vector<struct s_replie>* replie) {
    struct s_replie a;
    a.nbReplie = 221;
    a.rplReplie = "\r\n";
    replie->push_back(a);
    a.nbReplie = 301;
    a.rplReplie = " :";
    replie->push_back(a);
    a.nbReplie = 324;
    a.rplReplie = "\r\n";
    replie->push_back(a);
    a.nbReplie = 331;
    a.rplReplie = " :No topic is set\r\n";
    replie->push_back(a);
    a.nbReplie = 332;
    a.rplReplie = " :";
    replie->push_back(a);
    a.nbReplie = 368;
    a.rplReplie = " :End of channel ban list\r\n";
    replie->push_back(a);
    a.nbReplie = 401;
    a.rplReplie = ":No such nick/channel\r\n";
    replie->push_back(a);
    a.nbReplie = 403;
    a.rplReplie = ":No such channel\r\n";
    replie->push_back(a);
    a.nbReplie = 404;
    a.rplReplie = ":Cannot send to channel\r\n";
    replie->push_back(a);
    a.nbReplie = 411;
    a.rplReplie = ":No recipient given";
    replie->push_back(a);
    a.nbReplie = 412;
    a.rplReplie = ":No text to send\r\n";
    replie->push_back(a);
    a.nbReplie = 421;
    a.rplReplie = ":Unknown command\r\n";
    replie->push_back(a);
    a.nbReplie = 431;
    a.rplReplie = ":No nickname given\r\n";
    replie->push_back(a);
    a.nbReplie = 433;
    a.rplReplie = ":Nickname is already in use\r\n";
    replie->push_back(a);
    a.nbReplie = 436;
    a.rplReplie = ":Nickname collision KILL\r\n";
    replie->push_back(a);
    a.nbReplie = 443;
    a.rplReplie = ":is already on channel\r\n";
    replie->push_back(a);
    a.nbReplie = 461;
    a.rplReplie = ":Not enough parameters\r\n";
    replie->push_back(a);
    a.nbReplie = 462;
    a.rplReplie = ":You may not reregister\r\n";
    replie->push_back(a);
    a.nbReplie = 471;
    a.rplReplie = "Cannot join channel (+1)\r\n";
    replie->push_back(a);
    a.nbReplie = 472;
    a.rplReplie = ":is unknown mode char to me\r\n";
    replie->push_back(a);
    a.nbReplie = 473;
    a.rplReplie = ":Cannot join channel (+i)\r\n";
    replie->push_back(a);
    a.nbReplie = 474;
    a.rplReplie = ":Cannot join channel (+b)\r\n";
    replie->push_back(a);
    a.nbReplie = 482;
    a.rplReplie = ":You're not channel operator\r\n";
}

bool    _parcing(std::string buffer, User& sender, std::vector<Channel*>& channelList, std::vector<User*>& userList)
{
    
    std::vector<std::string>    buffers = ft_split(buffer, ' '); 
    Command cmd = parseCommand(buffers[0]);
    
    switch (cmd){
        case MODE:
            mode(buffers, sender);
            break;
        case KICK:
            kick(buffers, sender, channelList, userList);
            break;
        case PART:
            part(buffers, sender, channelList);
            break;
        case JOIN:
            join(buffers, sender, channelList);
            break;
        case PRIVMSG:
            privmsg(buffers, sender, channelList);
        case TOPIC:
            topic(buffers, sender, channelList);
            break;
        case USER:
            user(buffers, sender);
            break;
        case QUIT:
            quit(buffers, sender);
            break;
        case NICK:
            nick(buffers, sender, userList);
            break;
        default :
            sendNoCmd(buffers, sender);
    }

    return 1;
}