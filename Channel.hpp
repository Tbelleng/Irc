#pragma once

# include "server.hpp"


class   Channel {
private:
    std::vector<int>    member;
    std::vector<int>    opMember;
    std::string         name;
    int                 epfd;
    struct epoll_event& ev;

public:
    Channel(int opMember, int epfd, struct epoll_event& ev);
    Channel(std::string name, int opMember, int epfd, struct epoll_event& ev);
    ~Channel( void );
    
    void                setMember(int newMember);
    void                setOpMember(int oldOpMember, int newOpMember);

    std::string         getName(void) const;
    std::vector<int>    getAllMember( void ) const;
    std::vector<int>    getAllOpMember( void ) const;

    void                suppMember(int suppMember);
    void                suppOpMember(int oldOpMember, int suppOpMember);

    int                 sendMessage(const char* message) const;
};
