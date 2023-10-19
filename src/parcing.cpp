#include "server.hpp"

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
    std::vector<std::string>    cmd = copyAllCmd();
    User*    sender = getUser(socket_client);

    if (sender == 0)
        return (NULL);
}
