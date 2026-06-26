#pragma once
#include <iostream>
#include <optional>

#include "./Node.hpp"

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

    ~Queue()
    {
        Node<T>* current = this->first;
        while (current != nullptr) {
            Node<T>* next = current->getNextNode();
            delete current;
            current = next;
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
        if (this->first == nullptr) {
            return std::nullopt;
        }

        T value = this->first->getData();
        Node<T>* tmp = this->first;

        if (this->first == this->last) {
            this->first = nullptr;
            this->last = nullptr;
        } else {
            this->first = this->first->getNextNode();
        }

        this->size--;
        delete tmp;
        return value;
    }

    std::optional<T> front() const
    {
        if (this->first == nullptr) {
            return std::nullopt;
        }

        return this->first->getData();
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
