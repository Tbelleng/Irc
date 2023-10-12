#pragma once

# include "server.hpp"

# define DEBUG 1

class   Channel {
private:
    std::vector<int> member;
    std::string name;

public:
    Channel( void );
    Channel(std::string name);
    ~Channel( void );
    
    std::string     getName(void) const;
    void            addMember(int newMember);
    void            suppMember(int suppMember);
    std::vector<int>     getAllMember( void ) const;
    int             sendMessage(const char* message, const int epfd, struct epoll_event& ev) const;
};
