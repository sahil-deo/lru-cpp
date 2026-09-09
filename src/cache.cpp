#include "cache.h"


// PUBLIC

Cache::Cache()
{
    m_maxSize = 10;
    m_occuipied = 0;
    m_head = nullptr;
    m_last = nullptr;
}

void Cache::set(std::string key, std::string value)
{
    setNode(key, value);
}

std::string Cache::get(std::string key)
{
    return getNodeValue(key);
}


// PRIVATE

void Cache::setNode(std::string key, std::string value)
{

    if(getNode(key) != nullptr)
    {
        Node* n = unlink(key);
        n->value = value;
        pushFront(n);
        return;
    }
    while(m_occuipied > m_maxSize)
    {
        // delete LRU
        deleteLast();
    }
    m_occuipied++;

    Node* n = createNode(key, value);
    m_hmap[key] = n;
    pushFront(n);
}

Node* Cache::getNode(std::string key)
{
    auto it = m_hmap.find(key);
    if(it == m_hmap.end())return nullptr;
    return m_hmap[key];
}

std::string Cache::getNodeValue(std::string key)
{
    Node* n = unlink(key);
    if(n == nullptr)
        return "";
    
    pushFront(n);

    return n->value;
}

void Cache::pushFront(Node* n)
{   
    if(m_head==nullptr)
    {
        m_head = n;
        m_last = n;
        n->prev = nullptr;
        n->next = nullptr;
    }
    else 
    {
        m_head->prev = n;
        n->next = m_head;
        m_head = n;
    }
}

Node* Cache::unlink(std::string key)
{
    Node* n = getNode(key);

    if(!n)return nullptr;
    
    if(n == m_head)
    {
        m_head = n->next;
        if(m_head!=nullptr)
            m_head->prev = nullptr;
    }
    else if(n == m_last)
    {
        n->prev->next = nullptr;
        m_last = n->prev;
    }
    else
    {
        n->prev->next = n->next;
        n->next->prev = n->prev;
    }

    n->next = nullptr;
    n->prev = nullptr;
    return n;
}


void Cache::deleteLast()
{
    m_occuipied--;
    Node* last = m_last;
    m_last = m_last->prev;
    m_last->next = nullptr;
    m_hmap.erase(last->key);
    delete last;
}