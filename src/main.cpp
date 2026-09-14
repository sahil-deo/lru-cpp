#include <iostream>
#include <queue>
#include <mutex>
#include "gateway.h"
#include "cache.h"
#include <thread>
int main()
{
    // initialize main object
    Cache c;
    std::string input;
    std::mutex mtx;
    std::queue<std::string> messages;

    Gateway gateway(5555, &messages, &mtx);

    std::thread t = std::thread([&gateway]()
    {
        gateway.start();
    });

    while(1)
    {
        mtx.lock();
        if(!messages.empty())
        {
            input = messages.front();
            messages.pop();
        }
        else
        {
            mtx.unlock();
            continue;
        }
        mtx.unlock();

        if(input.size() != 3)
        {
            std::cout << "Invalid Input\n";
            continue;
        }
        std::cout << input << "\n";
        std::string command = input.substr(0, 3);
        std::string arg = input.substr(3);
        if(command == "get")
        {
            std::cout << c.get("test") << std::endl;
        }
        else if(command == "set")
        {
            c.set("test", "test");
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
    t.join();

}