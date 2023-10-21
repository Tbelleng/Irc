#include "Pars.hpp"

Command parseCommand(const std::string& cmd) {
    if (cmd == "MODE") {
        return MODE;
    } else if (cmd == "KICK") {
        return KICK;
    } else if (cmd == "INVITE") {
        return INVITE;
    } else if (cmd == "PART") {
        return PART;
    } else if (cmd == "JOIN") {
        return JOIN;
    } else if (cmd == "WHO") {
        return WHO;
    } else if (cmd == "WHOIS") {
        return WHOIS;
    } else if (cmd == "WHOWAS") {
        return WHOWAS;
    } else if (cmd == "KILL") {
        return KILL;
    } else if (cmd == "NOTICE") {
        return NOTICE;
    } else if (cmd == "PASS") {
        return PASS;
    } else if (cmd == "OPER") {
        return OPER;
    } else if (cmd == "TOPIC") {
        return TOPIC;
    } else if (cmd == "USER") {
        return USER;
    } else if (cmd == "QUIT") {
        return QUIT;
    } else if (cmd == "NICK") {
        return NICK;
    } else if (cmd == "NAMES") {
        return NAMES;
    } else if (cmd == "LIST") {
        return LIST;
    }
    return UNKNOWN;
}


void    join(std::vector<std::string> buffers, User& sender) {
    (void)buffers;
    (void)sender;
    std::cout << "You used JOIN" << std::endl;
}

void    kick(std::vector<std::string> buffers, User& sender) {
    (void)buffers;
    (void)sender;
    std::cout << "You used KICK" << std::endl;
}

void    invite(std::vector<std::string> buffers, User& sender) {
    (void)buffers;
    (void)sender;
    std::cout << "You used INVITE" << std::endl;
}

void    part(std::vector<std::string> buffers, User& sender) {
    (void)buffers;
    (void)sender;
    std::cout << "You used PART" << std::endl;
}

void    mode(std::vector<std::string> buffers, User& sender) {
    (void)buffers;
    (void)sender;
    //std::cout << "You are in JOIN" << std::endl;
}

void    who(std::vector<std::string> buffers, User& sender) {
    (void)buffers;
    (void)sender;
    //std::cout << "You are in JOIN" << std::endl;
}

void    whois(std::vector<std::string> buffers, User& sender) {
    (void)buffers;
    (void)sender;
    //std::cout << "You are in WHOIS" << std::endl;
}

void    whowas(std::vector<std::string> buffers, User& sender) {
    (void)buffers;
    (void)sender;
    //std::cout << "You are in WHOWAS" << std::endl;
}

void    kill(std::vector<std::string> buffers, User& sender) {
    (void)buffers;
    (void)sender;
    std::cout << "You used KILL" << std::endl;
}

void    notice(std::vector<std::string> buffers, User& sender) {
    (void)buffers;
    (void)sender;
    //std::cout << "You are in NOTICE" << std::endl;
}

void    pass(std::vector<std::string> buffers, User& sender) {
    (void)buffers;
    (void)sender;
    //std::cout << "You are in PASS" << std::endl;
}

void    oper(std::vector<std::string> buffers, User& sender) {
    (void)buffers;
    (void)sender;
    //std::cout << "You are in OPER" << std::endl;
}

void    topic(std::vector<std::string> buffers, User& sender) {
    (void)buffers;
    (void)sender;
    std::cout << "You used TOPIC" << std::endl;
}

void    user(std::vector<std::string> buffers, User& sender) {
    (void)buffers;
    (void)sender;
    std::cout << "You used USER" << std::endl;
}

void    quit(std::vector<std::string> buffers, User& sender) {
    (void)buffers;
    (void)sender;
    std::cout << "You used QUIT" << std::endl;
}

void    nick(std::vector<std::string> buffers, User& sender) {
    (void)buffers;
    (void)sender;
    std::cout << "You used NICK" << std::endl;
}

void    names(std::vector<std::string> buffers, User& sender) {
    (void)buffers;
    (void)sender;
    std::cout << "You used NAMES" << std::endl;
}

void    list(std::vector<std::string> buffers, User& sender) {
    (void)buffers;
    (void)sender;
    std::cout << "You used LIST" << std::endl;
}

void    sendNoCmd(std::vector<std::string> buffers, User& sender) {
    (void)buffers;
    (void)sender;
}

