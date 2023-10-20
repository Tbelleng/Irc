#pragma once

# include "irc.hpp"

class   Topic {
private:
    std::string topic;
    int        grade;

public:
    Topic(void);
    ~Topic(void);
    Topic(std::string topic, int grade);
    Topic(std::string topic);

    std::string getTopic(void) const;
    int        getGrade(void) const;

    void        setTopic(std::string newTopic);
    void        setGrade(int grade);
};
