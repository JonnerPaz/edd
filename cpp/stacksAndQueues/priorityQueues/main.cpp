#include <iostream>

#include "../priorityQueues/priorityQueue.hpp"

using namespace std;

template <typename T>
void loopPrioQueue(PriorityQueue<T>*& prioQueue)
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

int main()
{
    PriorityQueue<int>* masterList = new PriorityQueue<int>();
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
    return 0;
}
