#pragma once

# include "server.hpp"

class   Message {
private:
    std::string _messsage;
    Channel     _dest;
    User        _sender;

public:
    Message(void);
    Message(std::string message);
    Message(const Message& other);
    ~Message(void);

    std::string getMessage(void) const;
    Channel     getChannel(void) const;
    User        getSender(void) const;
}
