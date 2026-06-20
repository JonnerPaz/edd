#pragma once

#include <iostream>
#include <optional>

#include "../../listas/LinkedList/List.hpp"
#include "../priorityQueues/Queue.hpp"

template <typename T>
class PriorityQueueWithLinkedList
{
   private:
    int priority = 5;
    List<Queue<T>*>* queues = new List<Queue<T>*>();

   public:
    PriorityQueueWithLinkedList()
    {
        for (int i = 0; i < 6; i++) {
            queues->push(new Queue<T>());
        }
    }

    ~PriorityQueueWithLinkedList()
    {
        for (int i = 0; i < 6; i++) {
            delete queues->get(i)->getData();
        }
        delete queues;
    }

    void push(T data, int priority = 5)
    {
        if (priority < 0 || priority > 5) {
            std::cerr << "Prioridad inválida. Debe estar entre 0 y 5." << std::endl;
            return;
        }

        Queue<T>* queue = queues->get(priority)->getData();
        queue->push(data);
    }

    std::optional<T> pop()
    {
        for (int i = 0; i <= priority; i++) {
            Queue<T>* queue = queues->get(i)->getData();
            if (queue->getSize() > 0) {
                return queue->pop();
            }
        }
        return std::nullopt;  // No elements to dequeue
    }

    bool isEmpty() const
    {
        for (int i = 0; i <= priority; i++) {
            Queue<T>* queue = queues->get(i)->getData();
            if (queue->getSize() > 0) {
                return false;
            }
        }
        return true;
    }
};
