#ifndef CHANNEL_HPP
#define CHANNEL_HPP

class   Channel {
private:
    std::vector<int>    _members;
    std::vector<int>    _opMembers;
    std::string         _name;
    int                 _epfd;
    struct epoll_event& _ev;
    Topic               _topic;

public:
    Channel(int opMember, int epfd, struct epoll_event& ev);
    Channel(std::string name, int opMember, int epfd, struct epoll_event& ev);
    ~Channel( void );
    
    void                setMember(int newMember);
    void                setOpMember(int oldOpMember, int newOpMember);
    void                setGrade(int Member, int grade);
    void                setTopic(int Member, std::string topic);

    std::string         getTopic(void) const;
    std::string         getName(void) const;
    std::vector<int>    getAllMember( void ) const;
    std::vector<int>    getAllOpMember( void ) const;

    void                suppMember(int opMember, int suppMember);
    void                suppOpMember(int opMember, int suppOpMember);
    void                memberLeave(int leaver);

    void                 sendMessage(const char* message) const;
};

#endif
