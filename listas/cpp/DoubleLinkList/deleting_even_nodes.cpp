#include "DoubleLinkedNode.hpp"

template <typename T>
Node<T>* removeEvenValues(Node<T>* head)
{
    Node<T>* current = head;

    while (current != nullptr) {
        Node<T>* nextNode = current->getNextNode();

        if (current->getData() % 2 == 0) {
            // Manejar si es la cabeza
            if (current == head) {
                head = nextNode;
            }

            // Conectar el anterior con el siguiente
            if (current->getPrevNode() != nullptr) {
                current->getPrevNode()->setNextNode(nextNode);
            }

            // Conectar el siguiente con el anterior
            if (nextNode != nullptr) {
                nextNode->setPrevNode(current->getPrevNode());
            }

            delete current;  // Liberar memoria
        }
        current = nextNode;
    }

    return head;
}
