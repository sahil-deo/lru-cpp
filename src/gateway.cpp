#include "gateway.h"
#include <iostream>
Gateway::Gateway(short port, std::queue<std::string>* messages, std::mutex* mtx)
{

    m_mtx = mtx;
    m_messages = messages;
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_family = INADDR_ANY;

    m_serverFd = socket(AF_INET, SOCK_STREAM, 0);

    if(m_serverFd < 0)
    {
        // error
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    setsockopt(m_serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if(bind(m_serverFd, (sockaddr*)&addr, sizeof(addr)) < 0){
        exit(EXIT_FAILURE);
    }
}

void Gateway::start()
{
    // starting listenting

    if(listen(m_serverFd, 1) < 0)
    {
        exit(EXIT_FAILURE);
    }

    m_clientFd = accept(m_serverFd, nullptr, nullptr);
    
    if(m_clientFd < 0)
    {
        exit(EXIT_FAILURE);
    }

    char buffer[1024];

    while(1)
    {
        int n = recv(m_clientFd, &buffer, sizeof(buffer), 0);

        if(n <= 0)
        {
            exit(EXIT_FAILURE);
        }
        std::cout << n << "\n";
        std::cout << std::string(buffer, n) << "\n";
        m_mtx->lock();
        m_messages->push(std::string(buffer, n));
        m_mtx->unlock();
    }
}

void Gateway::stop()
{

}

void Gateway::sendMessage(std::string message)
{
    int n = send(m_clientFd, message.c_str(), message.size(), 0);
    if(n <= 0)
    {
        exit(EXIT_FAILURE);
    }
}