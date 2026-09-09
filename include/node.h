#pragma once

#include <string>

struct Node
{
    std::string key;
    std::string value;
    Node *next;
    Node *prev;
};

inline Node* createNode(std::string key, std::string value)
{
    Node* n = new Node;
    n->key = key;
    n->value = value;
    n->prev = nullptr;
    n->next = nullptr;
    return n;
}