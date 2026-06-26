#pragma once
#include <iostream>
#include <optional>

#include "./Queue.hpp"

// crear una cola de prioridad donde los datos se procesan las siguientes categorias:
// 0 -> prioridad maxima
// 5 -> prioridad minima

template <typename T>
class PriorityQueue
{
   private:
    Queue<T>* queues[6];
    // Para N cantidad de
    int priority = 5;

   public:
    PriorityQueue()
    {
        for (int i = 0; i < 6; i++) {
            queues[i] = new Queue<T>();
        }
    }

    ~PriorityQueue()
    {
        for (int i = 0; i < 6; i++) {
            delete queues[i];
        }
    }

    void push(T data, int priority = 5)
    {
        if (priority < 0 || priority > 5) {
            std::cerr << "Invalid priority level. Must be between 0 and 5." << std::endl;
            return;
        }
        queues[priority]->push(data);
    }

    std::optional<T> pop()
    {
        for (int i = 0; i <= priority; i++) {
            if (queues[i]->getSize() > 0) {
                return queues[i]->pop();
            }
        }
        return std::nullopt;  // No elements to dequeue
    }

    bool isEmpty() const
    {
        for (int i = 0; i <= priority; i++) {
            if (queues[i]->getSize() > 0) {
                return false;
            }
        }
        return true;
    }
};
