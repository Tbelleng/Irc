#include "Topic.hpp"

Topic::Topic(void) : topic("No topic set!"), grade(false){
    if(DEBUG_TOPIC)
        std::cout << "# Default Topic constructor #" << std::endl;
    return ;
}

Topic::Topic(std::string topic) : topic(topic), grade(true) {
   if(DEBUG_TOPIC)
        std::cout << "# Default Topic constructor #" << std::endl;
    return ;
}

Topic::Topic(std::string topic, bool grade) : topic(topic), grade(grade) {
    if(DEBUG_TOPIC)
        std::cout << "# Default Topic constructor #" << std::endl;
    return ;
}

Topic::~Topic(void) {
    if(DEBUG_TOPIC)
        std::cout << "| Default Topic constructor |" << std::endl;
    return ;
}

bool    Topic::getGrade(void) const {
    return this->grade;
}

std::string Topic::getTopic(void) const {
    return (this->topic);
}

void    Topic::setTopic(std::string newTopic) {
    this->topic = newTopic;
    return ;
}

void    Topic::setGrade(bool grade) {
    this->grade = grade;
    return ;
}
