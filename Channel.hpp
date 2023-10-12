#pragma once

# include "irc.hpp"

# define DEBUG 1

class   Channel {
private:
    vector<int> member;
    std::string name;

public:
    Channel( void );
    Channel(std::string name);
    ~Channel( void );
    
    std::string     getName(void) const;
    void            addMember(int newMember);
    void            suppMember(int suppMember);
    vector<int>     getAllMember( void ) const;
    int             sendMessage(std::string message, const int epoll_fd) const;
};
