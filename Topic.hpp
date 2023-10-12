#pragma once

# include "server.hpp"

class   Topic {
private:
    std::string topic;

public:
    Topic(void);
    ~Topic(void);
    Topic(std::string topic);

    std::string getTopic(void) const;
    void        setTopic(std::string newTopic);
};
