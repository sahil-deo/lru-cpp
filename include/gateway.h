#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <queue>
#include <mutex>

class Gateway
{
    private:
    int m_serverFd;
    int m_clientFd;
    std::queue<std::string> *m_messages;
    std::mutex *m_mtx;

    private:


    public:
    Gateway(short, std::queue<std::string>*, std::mutex*);
    ~Gateway() = default;

    void start();
    void stop();
    void sendMessage(std::string);
};