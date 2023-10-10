#pragma once

# include "irc.hpp"

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
    vector<int>     getAllMember( void ) const;
    int             sendMessage(std::string message) const;
};
