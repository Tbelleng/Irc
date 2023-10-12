#include "server.hpp"

Topic::Topic(void) : topic("No topic set!"), grade(0){
    if(DEBUG_TOPIC)
        std::cout << "# Default Topic constructor #" << std::endl;
    return ;
}

Topic::Topic(std::string topic) : topic(topic), grade(0) {
   if(DEBUG_TOPIC)
        std::cout << "# Default Topic constructor #" << std::endl;
    return ;
}

Topic::Topic(std::string topic, int grade) : topic(topic), grade(grade) {
    if(DEBUG_TOPIC)
        std::cout << "# Default Topic constructor #" << std::endl;
    return ;
}

Topic::~Topic(void) {
    if(DEBUG_TOPIC)
        std::cout << "| Default Topic constructor |" << std::endl;
    return ;
}

int    Topic::getGrade(void) const {
    return this->grade;
}

std::string Topic::getTopic(void) const {
    return (this->topic);
}

void    Topic::setTopic(std::string newTopic) {
    this->topic = newTopic;
    return ;
}

void    Topic::setGrade(int grade) {
    this->grade = grade;
    return ;
}
