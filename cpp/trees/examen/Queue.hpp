#pragma once
#include <iostream>
#include <optional>

template <typename T>
class Queue
{
   private:
    struct QNode {
        T data;
        QNode* next;

        QNode(T d) : data(d), next(nullptr) {}
    };

    QNode* first = nullptr;
    QNode* last = nullptr;
    int size = 0;

   public:
    Queue() : first(nullptr), last(nullptr) {}

    ~Queue()
    {
        QNode* current = this->first;
        while (current != nullptr) {
            QNode* next = current->next;
            delete current;
            current = next;
        }
    }

    void push(T data)
    {
        QNode* newNode = new QNode(data);
        if (this->first == nullptr || this->last == nullptr) {
            this->first = newNode;
            this->last = this->first;
        } else {
            this->last->next = newNode;
            this->last = this->last->next;
        }
        this->size++;
    }

    std::optional<T> pop()
    {
        if (this->first == nullptr) {
            return std::nullopt;
        }

        T value = this->first->data;
        QNode* tmp = this->first;

        if (this->first == this->last) {
            this->first = nullptr;
            this->last = nullptr;
        } else {
            this->first = this->first->next;
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

        return this->first->data;
    }

    int getSize() const { return size; }

    void loopQueue()
    {
        QNode* tmp = this->first;
        while (tmp != nullptr) {
            std::cout << tmp->data << std::endl;
            tmp = tmp->next;
        }
    }
};
