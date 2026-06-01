#pragma once

#include "DoubleLinkedNode.hpp"

template <typename T>
class DoubleLinkList
{
   private:
    Node<T>* head;
    Node<T>* tail;

    // if the list is empty, first node is both head and tail
    bool firstNodeCase(Node<T>* firstNode)
    {
        if (this->head != nullptr && this->tail != nullptr) {
            return false;
        }

        this->head = firstNode;
        this->tail = firstNode;
        return true;
    }

   public:
    DoubleLinkList() : head(nullptr), tail(nullptr) {}

    DoubleLinkList(Node<T>* head) : head(head), tail(nullptr) {}

    Node<T>* getHead() { return this->head; }

    Node<T>* setHead(Node<T>* head)
    {
        if (head == nullptr) {
            return this->head;
        }

        if (this->firstNodeCase(head)) {
            return this->head;
        }

        this->head = head;
        return this->head;
    }

    Node<T>* getTail() { return this->tail; }

    Node<T>* setTail(Node<T>* tail)
    {
        if (tail == nullptr) {
            return this->tail;
        }

        if (this->firstNodeCase(tail)) {
            return this->tail;
        }

        this->tail = tail;
        return this->tail;
    }
};
