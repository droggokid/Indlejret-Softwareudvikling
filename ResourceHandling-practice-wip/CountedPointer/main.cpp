#include "SmartString.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    SmartString ss(new std ::string("Hello world"));
    std ::cout << "String length : " << ss->length() << std ::endl;

    if (ss->find("world") != std ::string ::npos)
        std ::cout << "The 'ss' string does contain 'world '" << std ::endl;
    else
        std ::cout << "The 'ss' string does NOT contain 'world '" << std ::endl;

    SmartString ss2 = ss; // <- Deliberately why? What happens ?
}