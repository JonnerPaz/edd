#include "DoubleLinkedNode.hpp"

template <typename T>
Node<T>* findMiddleNode(Node<T>* head)
{
    if (head == nullptr) return nullptr;

    Node<T>* slow = head;
    Node<T>* fast = head;

    // 'fast' avanza el doble de rápido. Cuando 'fast' llega al final,
    // 'slow' estará exactamente en la mitad.
    while (fast != nullptr && fast->getNextNode() != nullptr) {
        slow = slow->getNextNode();
        fast = fast->getNextNode()->getNextNode();
    }

    return slow;
}
