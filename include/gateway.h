#include <arpa/inet.h>
#include <unistd.h>
#include <string>

class Gateway
{
    private:
    int m_serverFd;
    int m_clientFd;

    private:


    public:
    Gateway(short port);
    ~Gateway() = default;

    void start();
    void stop();

};