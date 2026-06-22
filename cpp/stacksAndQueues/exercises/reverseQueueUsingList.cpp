#include <iostream>

#include "../Stacks/stack.hpp"
#include "../queues/Queue.hpp"

template <typename T>
void reverseQueue(Queue<T>& cola)
{
    Stack<T> auxStack;

    // 1. Pasar todo de la cola a la pila (invierte el orden)
    while (cola.getSize() > 0) {
        auto item = cola.pop();
        if (item.has_value()) {
            auxStack.push(item.value());
        }
    }

    // 2. Devolverlo a la cola original
    while (auxStack.getSize() > 0) {
        auto item = auxStack.pop();
        if (item.has_value()) {
            cola.push(item.value());
        }
    }
}
