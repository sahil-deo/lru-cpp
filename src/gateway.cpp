#include "gateway.h"

Gateway::Gateway(short port)
{
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

    

}

void Gateway::stop()
{

}