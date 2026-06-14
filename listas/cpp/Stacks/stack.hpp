#pragma once
#include <iostream>
#include <optional>

#include "../LinkedList/Node.hpp"

template <typename T>
class Stack
{
   private:
    Node<T>* first = nullptr;
    int size = 0;

   public:
    Stack() : first(nullptr), size(0) {}

    Stack(T data) { this->push(data); }

    ~Stack()
    {
        while (this->first != nullptr) {
            this->pop();
        }
    }

    void push(T data)
    {
        Node<T>* node = new Node<T>(data);

        if (!this->first) {
            this->first = node;
        } else {
            node->setNextNode(this->first);
            this->first = node;
        }
        this->size++;

        node = nullptr;
    }

    std::optional<T> pop()
    {
        if (this->first == nullptr) {
            return std::nullopt;
        }
        T value = this->first->getData();

        Node<T>* tmp = this->first;
        this->first = this->first->getNextNode();

        delete tmp;
        this->size--;

        return value;
    }

    int getSize() const { return size; }

    void loopStack()
    {
        Node<T>* tmp = this->first;
        while (tmp != nullptr) {
            std::cout << tmp->getData() << std::endl;
            tmp = tmp->getNextNode();
        }
    }
};
