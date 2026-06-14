// Estudiante: Jonner Paz
// Realizar una función que devuelva el head de una lista simple invertida
// (El algoritmo de la funcion debe invertir la lista en una pasada)

#include <format>
#include <iostream>

#include "SingleLinkedNode.hpp"

using namespace std;

template <typename T>
Node<T>* reverseList(Node<T>*& head)
{
    if (head == nullptr || head->getNextNode() == nullptr) {
        return head;  // Lista vacía o de un solo elemento
    }

    Node<T>* tmp = nullptr;
    Node<T>* current = head;
    Node<T>* next = nullptr;

    while (current->getNextNode() != nullptr) {
        next = current->getNextNode();
        tmp = next->getNextNode();
        next->setNextNode(current);
        current->setNextNode(tmp);

        current = tmp;

        if (next == nullptr) return head;
    }

    return head;
}

template <typename T>
Node<T>* insertEnd(Node<T>*& head, T data)
{
    if (head == nullptr) {
        return new Node(data);
    }

    Node<T>* prev = nullptr;
    Node<T>* cur = head;

    while (cur != nullptr) {
        prev = cur;
        cur = cur->getNextNode();
    }

    prev->setNextNode(new Node(data));
    return head;
}

template <typename T>
Node<T>* reverseLinkedList(Node<T>*& head)
{
}

template <typename T>
void loopList(Node<T>* head)
{
    if (head == nullptr) {
        cout << "No hay elementos en el puntero suministrado" << endl;
    }

    while (head != nullptr) {
        cout << std::format("{}, ", head->getData());
        head = head->getNextNode();

        if (head == nullptr) {
            cout << "\n";
        }
    }
}

int main()
{
    Node<int>* list = new Node(1);
    insertEnd(list, 2);
    insertEnd(list, 3);
    insertEnd(list, 4);
    insertEnd(list, 5);

    reverseList(list);
    loopList(list);

    return 0;
}
