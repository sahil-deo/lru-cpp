#include <iostream>
#include "cache.h"

int main()
{
    // initialize main object
    Cache c;
    std::string input;
    while(1)
    {
        std::cout << ">";
        std::cin >> input;
        if(input.size() != 3)
        {
            std::cout << "Invalid Input\n";
            continue;
        }
        std::string command = input.substr(0, 3);
        std::string arg = input.substr(3);
        if(command == "get")
        {
            std::cout << "key > ";
            std::cin >> input;
            std::cout << c.get(input) << std::endl;
        }
        else if(command == "set")
        {
            std::cout << "key > ";
            std::cin >> input;
            std::cout << "value > ";
            std::cin >> arg;
            c.set(input, arg);
        }
        else if(command == "ext")
        {
            break;
        }
        else
        {
            std::cout << "INVALID COMMAND: " << command << "\n";
        }
    }
}