
#pragma once
#include <iostream>
#include <optional>

#include "../../listas/LinkedList/Node.hpp"

template <typename T>
class Queue
{
   private:
    Node<T>* first = nullptr;
    Node<T>* last = nullptr;
    int size = 0;

   public:
    Queue() : first(nullptr), last(nullptr) {}

    Queue(T data)
    {
        if (data != nullptr) {
            this->push(data);
        }
    }

    void push(T data)
    {
        Node<T>* newNode = new Node<T>(data);
        if (this->first == nullptr || this->last == nullptr) {
            this->first = newNode;
            this->last = this->first;
        } else {
            this->last->setNextNode(newNode);
            this->last = this->last->getNextNode();
        }
        this->size++;

        newNode = nullptr;
    }

    std::optional<T> pop()
    {
        T value = this->first->getData();
        if (this->first == this->last) {
            this->first = nullptr;
            this->last = nullptr;
            return std::nullopt;
        }

        Node<T>* tmp = this->first;
        this->first->setNextNode(this->first->getNextNode());
        this->size--;
        this->first = this->first->getNextNode();

        delete tmp;
        tmp = nullptr;
        return value;
    }

    int getSize() const { return size; }

    void loopQueue()
    {
        Node<T>* tmp = this->first;
        while (tmp != nullptr) {
            std::cout << tmp->getData() << std::endl;
            tmp = tmp->getNextNode();
        }
    }
};
