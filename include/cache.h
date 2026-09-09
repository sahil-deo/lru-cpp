#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include "node.h"


class Cache
{
    private:
    std::unordered_map<std::string, Node*> m_hmap;
    Node *m_head;
    Node *m_last;
    u_int32_t m_maxSize;
    u_int32_t m_occuipied;

    private:
    void setNode(std::string key, std::string val);
    Node* getNode(std::string key);
    std::string getNodeValue(std::string key);
    void deleteNode(std::string key);
    Node* unlink(std::string key);
    void pushFront(Node* n);
    void deleteLast();

    public:
    
    Cache();
    ~Cache(){};
    std::string get(std::string);
    void set(std::string, std::string);

};