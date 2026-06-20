// Detectar un ciclo en una lista doblemente enlazada
#include <utility>

#include "DoubleLinkedNode.hpp"

template <typename T>
std::pair<Node<T>*, Node<T>*> splitCyclicList(Node<T>* head)
{
    if (head == nullptr) return {nullptr, nullptr};

    Node<T>* slow = head;
    Node<T>* fast = head;
    bool hasCycle = false;

    // 1. Detectar si hay ciclo con el algoritmo de Floyd
    while (fast != nullptr && fast->getNextNode() != nullptr) {
        slow = slow->getNextNode();
        fast = fast->getNextNode()->getNextNode();
        if (slow == fast) {
            hasCycle = true;
            break;
        }
    }

    if (!hasCycle) {
        return {head, nullptr};  // No hay ciclo, retornamos la lista original
    }

    // 2. Encontrar el inicio del ciclo
    slow = head;
    Node<T>* prevToCycle = nullptr;  // Para romper el enlace desde la parte lineal

    while (slow != fast) {
        prevToCycle = slow;  // Guardamos el último nodo lineal
        slow = slow->getNextNode();
        fast = fast->getNextNode();
    }

    Node<T>* cycleHead = slow;  // 'slow' (o 'fast') es el inicio del ciclo

    // 3. Encontrar el último nodo del ciclo para mantenerlo circular
    Node<T>* cycleTail = cycleHead;
    while (cycleTail->getNextNode() != cycleHead) {
        cycleTail = cycleTail->getNextNode();
    }

    // 4. Separar las listas
    if (prevToCycle != nullptr) {
        prevToCycle->setNextNode(nullptr);  // Rompemos la parte lineal
    } else {
        // Edge case: El ciclo empieza en la cabeza (toda la lista es circular)
        head = nullptr;
    }

    // cycleTail ya apunta a cycleHead, así que la lista circular está intacta.
    // Solo debemos asegurar los punteros 'prev' si es doblemente enlazada.
    cycleHead->setPrevNode(cycleTail);

    return {head, cycleHead};
}
