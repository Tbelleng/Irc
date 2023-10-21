#include "server.hpp"
#include "Pars.cpp"
// User&   getUser(int socket_client) {
//     for(std::vector<User*>.iterator it = this->userList.begin(); it != this->userList.end(); it++) {
//         if (it.getFd() == socket_client)
//             return it;
//     }
//     return 0;
// }

bool    _parcing(std::string buffer, User& sender) 
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
        case INVITE:
            invite(buffers, sender);
            break;
        case PART:
            part(buffers, sender);
            break;
        case JOIN:
            join(buffers, sender);
            break;
        case WHO:
            who(buffers, sender);
            break;
        case WHOIS:
            whois(buffers, sender);
            break;
        case WHOWAS:
            whowas(buffers, sender);
            break;
        case KILL:
            kill(buffers, sender);
            break;
        case NOTICE:
            notice(buffers, sender);
            break;
        case PASS:
            pass(buffers, sender);
            break;
        case OPER:
            oper(buffers, sender);
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
        case NAMES:
            names(buffers, sender);
            break;
        case LIST:
            list(buffers, sender);
        default :
            sendNoCmd(buffers, sender);
    }

    return 1;
}
