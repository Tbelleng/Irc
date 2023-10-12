#include "Channel.hpp"

Channel::Channel( void ) : name("Default") {
    if (DEBUG)
        std::cout << "# Default Channel constructor call #" << std::endl;
}

Channel::Channel(std::string name) : name(name) {
    if (DEBUG)
        std::cout << "# String Channel constructor call #" << std::endl;
}

Channel::~Channel( void ) {
    if (DEBUG)
        std::cout << "| Default Channel destructor |";
}

std::string Channel::getName( void ) const {
    return this->name;
}

void    Channel::addMember(int newMember) {
    this->member.push_back(newMember);
    return ;
}

void    Channel::suppMember(int suppMember) {
    this->member.erase(
        std::remove(this->member.begin(), this->member.end(), suppMember),
        this->member.end()
    );
    return ;
}

std::vector<int> Channel::getAllMember( void ) const {
    return this->member;
}

int     Channel::sendMessage(const char* message, const int epfd, struct epoll_event& ev) const {

  for(std::vector<int>::const_iterator it = member.begin(); it != member.end(); ++it) {
        // Ajoute le socket à l'instance epoll pour surveillance en écriture
        ev.events = EPOLLOUT;
        ev.data.fd = *it;
        // if(epoll_ctl(epfd, EPOLL_CTL_ADD, *it, &ev) == -1) {
        //     std::cerr << "Failed to add client socket to epoll set: " << *it << std::endl;
        //     continue;  // Passe au socket client suivant
        //     // check si c'est bien securise 
        // }

        // Attends que le socket soit prêt pour l'écriture
        struct epoll_event events[1]; // Tableau pour contenir les événements retournés par epoll_wait
        int nfds = epoll_wait(epfd, events, 1, 5000); // Attend jusqu'à 5 secondes pour un événement

        if(nfds == -1) {
            std::cerr << "epoll_wait failed for client: " << *it << std::endl;
            // check si c'est bien securise 
        } else if(nfds > 0) {
            ssize_t bytesSent = send(*it, message, std::strlen(message), 0);
            if(bytesSent == -1) {
                std::cerr << "Failed to send message to client: " << *it << std::endl;
                // check si c'est bien securise 
            }
        } else {
            std::cerr << "Send to client " << *it << " timed out." << std::endl;
        }
    }
    return 1;
}
