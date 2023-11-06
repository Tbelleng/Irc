#include "server.hpp"
#include "Pars.cpp"

void printAsciiCharacters(const std::string& str)
{
    for (size_t i = 0; i < str.length(); ++i) {
        char c = str[i];
        if (c >= 32 && c <= 126) {
            // Check if the character is in the printable ASCII range
            std::cout << "Character at position " << i << ": " << c << " (ASCII code: " << int(c) << ")\n";
        } else {
            // If the character is not printable, display a message
            std::cout << "Character at position " << i << ": Non-printable character (ASCII code: " << int(c) << ")\n";
        }
    }
}

std::string removeSpecificSpaces(const std::string& input)
{
    std::string result;
    
    for (size_t i = 0; i < input.length(); ++i) {
        if (input[i] != ' ' && input[i] != '\n' && input[i] != '\r' && input[i] != '\t' && input[i] != 0) {
            result += input[i];
        }
    }
    
    return result;
}


std::string trimBuffers(const std::vector<std::string>& buffer)
{
    std::string result;

    if (buffer.size() >= 3) {
        for (size_t i = 2; i < buffer.size(); ++i) {
            result += buffer[i];
            result += " ";
        }

        if (!buffer[2].empty()) {
            result.erase(0, 1);
        }
    }
    return result;
}


bool    _parcing(std::string buffer, User& sender, std::map<std::string, Channel*>& channelList, std::map<int, User*>& userList)
{
    std::vector<std::string>    buffers = ft_split(buffer); 
    Command cmd = parseCommand(buffers[0]);
    printAsciiCharacters(buffers[0]);
    (void)channelList;
    
     switch (cmd){
        case MODE:
            //mode(buffers, sender);
            break;
        case KICK:
            //kick(buffers, sender, channelList, userList);
            break;
        case PART:
            part(buffers, sender, channelList);
            break;
        case JOIN:
            join(buffers, sender, channelList);
            break;
        case PRIVMSG:           // message ressemble a ca "PRIVMSG #hello :salut"
            privmsg(buffers, sender, channelList, userList);
        case TOPIC:
            //topic(buffers, sender, channelList);
            break;
        case USER:
            //user(buffers, sender);
            break;
        case QUIT:
            //quit(buffers, sender);
            break;
         case NICK:
            nick(buffers, sender, userList);
            break;
        default :
            //sendNoCmd(buffers, sender);
             break;
    }

    return 1;
}
