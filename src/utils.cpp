#include "server.hpp"

void    _send(const char* message, int member, int epfd, struct epoll_event& ev) {
    ev.events = EPOLLOUT;
    ev.data.fd = member;

    // Attends que le socket soit prêt pour l'écriture
    struct epoll_event events[1];
    int nfds = epoll_wait(epfd, events, 1, 5000);

    if(nfds == -1) {
        std::cerr << "epoll_wait failed for client: " << member << std::endl;
        // check si c'est bien securise 
    } else if(nfds > 0) {
        ssize_t bytesSent = send(member, message, std::strlen(message), 0);
        if(bytesSent == -1) {
            std::cerr << "Failed to send message to client: " << member << std::endl;
            // check si c'est bien securise 
        }
    } else {
        std::cerr << "Send to client " << member << " timed out." << std::endl;
    }
}
