#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5555);
    
    if(inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) != 1)
    {
        exit(EXIT_FAILURE);
    }
    int clientFD = socket(AF_INET, SOCK_STREAM, 0);
    if(connect(clientFD, (sockaddr*)&addr, sizeof(addr)) < 0){
        exit(EXIT_FAILURE);
    }

    std::string input{};
    while(1)
    {
        input = "";
        std::cout << ">";
        std::cin >> input;
        send(clientFD, input.c_str(), input.size(), 0);
        std::cout << "SENT\n";
    }

}