#pragma once

#include "Node.hpp"

template <typename T>
class List
{
   private:
    Node<T>* head;

   public:
    List() : head(nullptr) {}

    List(Node<T>* head) : head(head) {}

    Node<T>* getHead() { return this->head; }

    Node<T>* setHead(Node<T>* head)
    {
        if (this->head != nullptr) {
            return this->head;
        }

        this->head = head;
        return this->head;
    }
};
