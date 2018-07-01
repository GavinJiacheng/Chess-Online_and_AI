#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

struct Message
{
    Message(std::string TxtName, std::string TxtMessage) {name = TxtName; message = TxtMessage;}
    std::string name;
    std::string message;
};

#endif // MESSAGE_H
