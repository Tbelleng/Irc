#include "irc.hpp"

std::vector<std::string>    copyAllCmd(void) {
    std::vector<std::string>    cmd;

    cmd.push_back("MODE");
    cmd.push_back("KICK");
    cmd.push_back("INVITE");
    cmd.push_back("PART");
    cmd.push_back("JOIN");
    cmd.push_back("WHO");
    cmd.push_back("WHOIS");
    cmd.push_back("WHOWAS");
    cmd.push_back("KILL");
    cmd.push_back("NOTICE");
    cmd.push_back("PRIVMSG");
    cmd.push_back("PASS");
    cmd.push_back("OPER");
    cmd.push_back("TOPIC");
    cmd.push_back("USER");
    cmd.push_back("QUIT");
    cmd.push_back("NICK");
    cmd.push_back("NAMES");
    cmd.push_back("LIST");
    return cmd;
}

User&   getUser(int socket_client) {
    for(std::vector<User*>.iterator it = this->userList.begin(); it != this->userList.end(); it++) {
        if (it.getFd() == socket_client)
            return it;
    }
    return 0;
}

bool    _parcing(std::string buffer, int socket_client) {
    std::vector<std::string>    cmds = copyAllCmd();
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
