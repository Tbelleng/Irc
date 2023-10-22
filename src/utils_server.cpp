#include "server.hpp"
#include "Pars.cpp"
// User&   getUser(int socket_client) {
//     for(std::vector<User*>.iterator it = this->userList.begin(); it != this->userList.end(); it++) {
//         if (it.getFd() == socket_client)
//             return it;
//     }
//     return 0;
// }

void    setError(std::vector<struct s_error>& error) {
    struct s_error a;
    a.nbError = 401;
    a.rplError = ":No such nick/channel\r\n";
    error.push_back(a);
    a.nbError = 403;
    a.rplError = ":No such channel\r\n";
    error.push_back(a);
    a.nbError = 404;
    a.rplError = ":Cannot send to channel\r\n";
    error.push_back(a);
    a.nbError = 411;
    a.rplError = ":No recipient given\r\n";
    error.push_back(a);
    a.nbError = 412;
    a.rplError = ":No text to send\r\n";
    error.push_back(a);
    a.nbError = 421;
    a.rplError = ":Unknown command\r\n";
    error.push_back(a);
    a.nbError = 431;
    a.rplError = ":No nickname given\r\n";
    error.push_back(a);
    a.nbError = 433;
    a.rplError = ":Nickname is already in use\r\n";
    error.push_back(a);
    a.nbError = 436;
    a.rplError = ":Nickname collision KILL\r\n";
    error.push_back(a);
    a.nbError = 443;
    a.rplError = ":is already on channel\r\n";
    error.push_back(a);
    a.nbError = 461;
    a.rplError = ":Not enough parameters\r\n";
    error.push_back(a);
    a.nbError = 462;
    a.rplError = ":You may not reregister\r\n";
    error.push_back(a);
    a.nbError = 471;
    a.rplError = "Cannot join channel (+1)\r\n";
    error.push_back(a);
    a.nbError = 472;
    a.rplError = ":is unknown mode char to me\r\n";
    error.push_back(a);
    a.nbError = 473;
    a.rplError = ":Cannot join channel (+i)\r\n";
    error.push_back(a);
    a.nbError = 474;
    a.rplError = ":Cannot join channel (+b)\r\n";
    error.push_back(a);
    a.nbError = 482;
    a.rplError = ":You're not channel operator\r\n";
}

bool    _parcing(std::string buffer, User& sender, std::vector<Channel*> channelList) 
{
    
    std::vector<std::string>    buffers = ft_split(buffer, ' '); 
    Command cmd = parseCommand(buffers[0]);
    
    switch (cmd){
        case MODE:
            mode(buffers, sender);
            break;
        case KICK:
            kick(buffers, sender);
            break;
        case PART:
            part(buffers, sender, channelList);
            break;
        case JOIN:
            join(buffers, sender, channelList);
            break;
        case NOTICE:
            notice(buffers, sender);
            break;
        case TOPIC:
            topic(buffers, sender);
            break;
        case USER:
            user(buffers, sender);
            break;
        case QUIT:
            quit(buffers, sender);
            break;
        case NICK:
            nick(buffers, sender);
            break;
        default :
            sendNoCmd(buffers, sender);
    }

    return 1;
}
