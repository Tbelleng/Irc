#include "server.hpp"

Message::Message(void) : Message(0){
    if (DEBUG_MESS)
        std::cout << "# Constructor Message called #" << std::endl;
    return ;
}

Message::Message(std::string message, User &sender) : _message(message), _sender(sender), _dest(dest) {
    if (DEBUG_MESS)
        std::cout << "# Constructor Message by string is called #" << std::endl;
    return ;
}

Message::Message(const Message& other) : _message(other.getMessage()), _send(other.getSender()), _dest(other.getChannel()) {
    if (DEBUG_MESS)
        std::cout << "# Constructor Message by copy is called #" << std::endl;
    return ;
}

Message::~Message(void) {
    if (DEBUG_MESS)
        std::cout << "| Destructor Message is called |" << std::endl;
    return ;
}

std::string Message::getMessage(void) {
    return this->_message;
}

Channel Message::getChannel(void) {
    return this->_dest;
}

User    Message::getSender(void) {
    return this->_sender;
}
