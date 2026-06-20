// invertir una lista doblemente enlazada
#include "DoubleLinkedNode.hpp"

template <typename T>
Node<T>* reverseList(Node<T>* head)
{
    if (head == nullptr || head->getNextNode() == nullptr) {
        return head;  // Lista vacía o de un solo elemento
    }

    Node<T>* current = head;
    Node<T>* temp = nullptr;

    // Recorremos la lista intercambiando prev y next
    while (current != nullptr) {
        temp = current->getPrevNode();
        current->setPrevNode(current->getNextNode());
        current->setNextNode(temp);

        // ¡Ojo aquí! Como invertimos los punteros, el "siguiente" nodo
        // ahora está en getPrevNode()
        current = current->getPrevNode();
    }

    // Antes de salir, 'temp' apunta al penúltimo nodo (que ahora es el segundo).
    // El nuevo 'head' será el prev de 'temp' (el antiguo último nodo).
    if (temp != nullptr) {
        head = temp->getPrevNode();
    }

    return head;
}
