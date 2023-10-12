#include "Topic.hpp"

Topic::Topic(void) : topic("No topic set!"){
    if(DEBUG_TOPIC)
        std::cout << "# Default Topic constructor #" << std::endl;
    return ;
}

Topic::Topic(std::string topic) : topic(topic) {
    if(DEBUG_TOPIC)
        std::cout << "# Default Topic constructor #" << std::endl;
    return ;
}

Topic::~Topic(void) {
    if(DEBUG_TOPIC)
        std::cout << "| Default Topic constructor |" << std::endl;
    return ;
}

std::string Topic::getTopic(void) const {
    return (this->topic);
}

void    Topic::setTopic(std::string newTopic) {
    this->topic = newTopic;
    return ;
}
