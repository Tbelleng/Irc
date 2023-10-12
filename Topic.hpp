#pragma once

# include "server.hpp"

class   Topic {
private:
    std::string topic;
    bool        grade;

public:
    Topic(void);
    ~Topic(void);
    Topic(std::string topic, bool grade);
    Topic(std::string topic);

    std::string getTopic(void) const;
    bool        getGrade(void) const;

    void        setTopic(std::string newTopic);
    void        setGrade(bool grade);
};
