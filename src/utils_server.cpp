#include "irc.hpp"

User&   getUser(int socket_client) {
    for(std::vector<User*>.iterator it = this->userList.begin(); it != this->userList.end(); it++) {
        if (it.getFd() == socket_client)
            return it;
    }
    return 0;
}

bool    _parcing(std::string buffer, int socket_client) {
    std::vector<std::string>    buffers = ft_split(buffer, ' '); 
    std::string                 name = ++buffer.begin();
    User*    sender = getUser(socket_client, name);

    if (sender == 0)
        return (0);

    std::string cmd = buffers[1];
    switch (cmd){
        case MODE:
            parse.mode(buffers, sender);
            break;
        case KICK:
            parse.kick(buffers, sender);
            break;
        case INVITE:
            parse.invite(buffers, sender);
            break;
        case PART:
            parse.part(buffers, sender);
            break;
        case JOIN:
            parse.join(buffers, sender);
            break;
        case WHO:
            parse.who(buffers, sender);
            break;
        case WHOIS:
            parse.whois(buffers, sender);
            break;
        case WHOWAS:
            parse.whowas(buffers, sender);
            break;
        case KILL:
            parse.kill(buffers, sender);
            break;
        case NOTICE:
            parse.notice(buffers, sender);
            break;
        case PASS:
            parse.pass(buffers, sender);
            break;
        case OPER:
            parse.oper(buffers, sender);
            break;
        case TOPIC:
            parse.topic(buffers, sender);
            break;
        case USER:
            parse.user(buffers, sender);
            break;
        case QUIT:
            parse.quit(buffers, sender);
            break;
        case NICK:
            parse.nick(buffers, sender);
            break;
        case NAMES:
            parse.names(buffers, sender);
            break;
        case LIST:
            parse.list(buffers, sender);
        default :
            parse.sendNoCmd(buffers, sender);
    }

    return 1;
}
