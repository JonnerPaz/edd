#include "DoubleLinkedNode.hpp"

template <typename T>
bool isPalindrome(Node<T>* head)
{
    if (head == nullptr || head->getNextNode() == nullptr) return true;

    // 1. Encontrar el medio
    Node<T>* slow = head;
    Node<T>* fast = head;
    while (fast != nullptr && fast->getNextNode() != nullptr) {
        slow = slow->getNextNode();
        fast = fast->getNextNode()->getNextNode();
    }

    // 2. Invertir la segunda mitad
    Node<T>* secondHalfHead = slow;
    Node<T>* prev = nullptr;
    Node<T>* current = secondHalfHead;
    Node<T>* next = nullptr;

    while (current != nullptr) {
        next = current->getNextNode();
        current->setNextNode(prev);
        current->setPrevNode(next);  // Para lista doble
        prev = current;
        current = next;
    }
    secondHalfHead = prev;  // 'prev' es la nueva cabeza de la mitad invertida

    // 3. Comparar ambas mitades
    Node<T>* left = head;
    Node<T>* right = secondHalfHead;
    bool isPalin = true;

    while (right != nullptr) {
        if (left->getData() != right->getData()) {
            isPalin = false;
            break;  // No es palíndromo
        }
        left = left->getNextNode();
        right = right->getNextNode();
    }

    return isPalin;
}
