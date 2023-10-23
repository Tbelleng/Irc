#include "irc.hpp"

std::vector<std::string>    ft_split(std::string s1, const char token) {
    std::vector<std::string>    buffer;
    std::string                 tmp;
    
    for (uint i = 0; i < s1.size(); i++) {
        if (s1[i] != token)
            tmp += s1[i];
        else if (!tmp.empty()){
            buffer.push_back(tmp);
            tmp.clear();
        }
    }

    if (!tmp.empty()) {
        buffer.push_back(tmp);
    }
    
    return buffer;
}

void    _send(const char* message, int member) {
        ssize_t bytesSent = send(member, message, std::strlen(message), 0);
        if(bytesSent == -1) {
            std::cerr << "Failed to send message to client: " << member << std::endl;
            // check si c'est bien securise 
        }
}
