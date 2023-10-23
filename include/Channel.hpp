#ifndef CHANNEL_HPP
#define CHANNEL_HPP

# include "server.hpp"

class   Channel {
private:
    std::vector<int>    _members;
    std::vector<int>    _opMembers;
    std::string         _name;
    Topic               _topic;

public:
    Channel(int opMember);
    Channel(std::string name, int opMember);
    ~Channel( void );
    
    void                setMember(int newMember);
    void                setOpMember(int oldOpMember, int newOpMember);
    void                setGrade(int Member, int grade);
    bool                setTopic(int Member, std::string topic);

    std::string         getTopic(void) const;
    std::string         getName(void) const;
    std::vector<int>    getAllMember( void ) const;
    std::vector<int>    getAllOpMember( void ) const;

    void                suppMember(int opMember, int suppMember);
    void                suppOpMember(int opMember, int suppOpMember);
    void                memberLeave(int leaver);

    void                 sendMessage(const char* message) const;

    bool                isInChannel(int user);
};

#endif
