#include <iostream>

#include "../stacksAndQueues/queues/Queue.hpp"
#include "./Stacks/stack.hpp"

using namespace std;

int main()
{
    Stack<int>* stack = new Stack<int>();
    stack->push(1);
    stack->push(2);
    stack->push(3);
    stack->push(4);

    cout << "Stack:" << endl;
    stack->loopStack();

    auto resStack = stack->pop();
    if (resStack.has_value()) {
        cout << "Popped: " << resStack.value() << endl;
    } else {
        cout << "Stack is empty" << endl;
    }
    cout << "Stack after pop: " << endl;
    stack->loopStack();

    Queue<int>* queue = new Queue<int>();
    queue->push(1);
    queue->push(2);
    queue->push(3);
    queue->push(4);

    cout << "Queue:" << endl;
    queue->loopQueue();
    auto resQueue = queue->pop();
    if (resQueue.has_value()) {
        cout << "Popped: " << resQueue.value() << endl;
    } else {
        cout << "Queue is empty" << endl;
    }
    cout << "Queue after pop:" << endl;
    queue->loopQueue();

    return 0;
}
