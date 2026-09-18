#include <iostream>
#include <queue>
#include <mutex>
#include "gateway.h"
#include "cache.h"
#include <thread>

std::vector<std::string> getCommand(std::string &s)
{
    std::vector<std::string> args{};

    int prev{};
    int i{};
    for (i = 0; i < s.size(); i++)
    {
        if (s[i] == ':')
        {
            args.push_back(s.substr(prev, i - prev));
            prev = i + 1;
        }
    }
    return args;
}

int main()
{
    // initialize main object
    Cache c;
    std::string input{}, message{}, command{}, arg{};
    std::mutex mtx{};
    std::queue<std::string> messages{};
    std::vector<std::string> args;
    Gateway gateway(5555, &messages, &mtx);

    std::thread t = std::thread([&gateway]()
                                { gateway.start(); });

    while (1)
    {
        mtx.lock();
        if (!messages.empty())
        {
            message = messages.front();
            messages.pop();
        }
        else
        {
            mtx.unlock();
            continue;
        }
        mtx.unlock();

        args = getCommand(message);

        for (auto it : args)
        {
            std::cout << it << " ";
        }
        std::cout << "\n";
        if (args.size() == 0)
        {
            gateway.sendMessage("Invalid Command");
            continue;
        }
        else if (args.size() == 1)
        {
            if (args[0] == "ext")
            {
                exit(EXIT_SUCCESS);
                continue;
            }
        }
        else if (args.size() == 2)
        {
            if (args[0] == "get")
            {
                gateway.sendMessage(c.get(args[1]));
                continue;
            }
        }
        else if (args.size() == 3)
        {
            if (args[0] == "set")
            {
                c.set(args[1], args[2]);
                continue;
            }
        }
        std::cout << "INVALID COMMAND: " << command << "\n";
    }
    t.join();
}
