#include "DoubleLinkedNode.hpp"

template <typename T>
Node<T>* removeNthFromEnd(Node<T>* head, int n)
{
    if (head == nullptr || n <= 0) return head;

    Node<T>* dummy = new Node<T>(0);
    dummy->setNextNode(head);
    head->setPrevNode(dummy);  // Asumiendo lista doble

    Node<T>* fast = dummy;
    Node<T>* slow = dummy;

    // 1. Adelantamos 'fast' N + 1 pasos para que 'slow' quede un nodo ANTES del objetivo
    for (int i = 0; i <= n; ++i) {
        if (fast == nullptr) {
            delete dummy;  // N era mayor que el tamaño de la lista
            return head;
        }
        fast = fast->getNextNode();
    }

    // 2. Movemos ambos a la misma velocidad
    while (fast != nullptr) {
        slow = slow->getNextNode();
        fast = fast->getNextNode();
    }

    // 3. 'slow' está justo antes del nodo a eliminar
    Node<T>* nodeToDelete = slow->getNextNode();
    Node<T>* nextNode = nodeToDelete->getNextNode();

    // 4. Reconectamos saltando 'nodeToDelete'
    slow->setNextNode(nextNode);
    if (nextNode != nullptr) {
        nextNode->setPrevNode(slow);
    }

    // Si eliminamos la cabeza real, actualizamos
    if (nodeToDelete == head) {
        head = nextNode;
    }

    delete nodeToDelete;

    // Limpieza del dummy
    head->setPrevNode(nullptr);
    delete dummy;

    return head;
}
