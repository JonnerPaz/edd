#include "DoubleLinkedNode.hpp"

// Merge sort para listas doblemente enlazadas
// 2 listas ordenadas de menor a mayor
// Devuelve una nueva lista ordenada

template <typename T>
Node<T>* mergeSortedLists(Node<T>* list1, Node<T>* list2)
{
    // Casos base rápidos
    if (list1 == nullptr && list2 == nullptr) return nullptr;
    if (list1 == nullptr) return list2;
    if (list2 == nullptr) return list1;

    // Nodo ficticio para no lidiar con el caso especial de la cabeza
    Node<T>* dummy = new Node<T>(0);
    Node<T>* current = dummy;

    while (list1 != nullptr && list2 != nullptr) {
        if (list1->getData() <= list2->getData()) {
            current->setNextNode(list1);
            list1->setPrevNode(current);
            list1 = list1->getNextNode();
        } else {
            current->setNextNode(list2);
            list2->setPrevNode(current);
            list2 = list2->getNextNode();
        }
        current = current->getNextNode();
    }

    // Si sobraron elementos en alguna lista, simplemente conectamos el resto
    if (list1 != nullptr) {
        current->setNextNode(list1);
        list1->setPrevNode(current);
    } else if (list2 != nullptr) {
        current->setNextNode(list2);
        list2->setPrevNode(current);
    }

    // Extraemos la verdadera cabeza y liberamos el dummy
    Node<T>* head = dummy->getNextNode();
    head->setPrevNode(nullptr);
    delete dummy;

    return head;
}
