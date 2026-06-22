#include <iostream>

#include "../priorityQueues/priorityQueueWithArray.hpp"
#include "../priorityQueues/priorityQueueWithLinkedList.hpp"

using namespace std;

template <typename Q>
void loopPrioQueue(Q*& prioQueue)
{
    while (true) {
        auto data = prioQueue->pop();
        if (data.has_value()) {
            cout << "Dato procesado: " << data.value() << endl;
        } else {
            cout << "No hay más datos para procesar." << endl;
            break;
        }
    }
}

void testPriorityQueueWithArray()
{
    cout << "=== PriorityQueueWithArray ===" << endl;
    PriorityQueueWithArray<int>* masterList = new PriorityQueueWithArray<int>();
    cout << "Pasando elements a masterlist (por defecto, la 5)" << endl;
    masterList->push(3);
    masterList->push(4);
    masterList->push(5);
    cout << "Datos pasados a masterList, pero sin prioridad" << endl;
    cout << "Viendo los datos: " << endl;
    loopPrioQueue(masterList);

    cout << "Pasando elements a masterList, pero con prioridad" << endl;
    masterList->push(1, 0);  // Prioridad máxima
    masterList->push(2, 1);  // Prioridad alta
    masterList->push(3, 2);  // Prioridad media
    masterList->push(4, 3);  // Prioridad baja
    masterList->push(5, 2);  // Prioridad media
    masterList->push(6, 0);  // Prioridad máxima
    masterList->push(7);     // Prioridad mínima (5)
    cout << "Viendo los datos: " << endl;
    loopPrioQueue(masterList);

    delete masterList;
}

void testPriorityQueueWithLinkedList()
{
    cout << "\n=== PriorityQueueWithLinkedList ===" << endl;
    PriorityQueueWithLinkedList<int>* masterList = new PriorityQueueWithLinkedList<int>();
    cout << "Pasando elements a masterlist (por defecto, la 5)" << endl;
    masterList->push(3);
    masterList->push(4);
    masterList->push(5);
    cout << "Datos pasados a masterList, pero sin prioridad" << endl;
    cout << "Viendo los datos: " << endl;
    loopPrioQueue(masterList);

    cout << "Pasando elements a masterList, pero con prioridad" << endl;
    masterList->push(1, 0);  // Prioridad máxima
    masterList->push(2, 1);  // Prioridad alta
    masterList->push(3, 2);  // Prioridad media
    masterList->push(4, 3);  // Prioridad baja
    masterList->push(5, 2);  // Prioridad media
    masterList->push(6, 0);  // Prioridad máxima
    masterList->push(7);     // Prioridad mínima (5)
    cout << "Viendo los datos: " << endl;
    loopPrioQueue(masterList);

    delete masterList;
}

int main()
{
    testPriorityQueueWithArray();
    testPriorityQueueWithLinkedList();
    return 0;
}
