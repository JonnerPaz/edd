#include <format>
#include <iostream>

#include "DoubleLinkedNode.hpp"

using namespace std;

// 1. Crear una función que reciba dos heads de diferentes listas doble enlazadas
// Y devuelva un nuevo head de la fusión de ambas listas en orden de menor a mayor eliminando
// duplicados
template <typename T>
void sortList(Node<T>*& head)
{
    if (head == nullptr) {
        cout << "No valid data";
        return;
    }

    Node<T>* current = head;
    Node<T>* temp = nullptr;

    while (current != nullptr) {
        temp = current->getPrevNode();
        if (temp->getData() <= current->getData()) {
            current->setPrevNode(current->getNextNode());
            current->setNextNode(temp);
            current = current->getPrevNode();
        }
    }
}

template <typename T>
Node<T>* mergeSort(Node<T>*& list1, Node<T>*& list2)
{
    // Casos base rápidos
    if (list1 == nullptr && list2 == nullptr) return nullptr;
    if (list1 == nullptr) return list2;
    if (list2 == nullptr) return list1;

    Node<T>* temp = new Node<T>(0);
    Node<T>* current = temp;

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

    // Extraemos la verdadera cabeza
    Node<T>* head = temp->getNextNode();
    head->setPrevNode(nullptr);
    delete temp;

    return head;
}

template <typename T>
Node<T>* insertNodeBeginning(Node<T>*& head, T data)
{
    // list does not exists, return new one
    if (head == nullptr) {
        head = new Node<T>(data);
        return head;
    }

    Node<T>* newNode = new Node<T>(data);

    head->setPrevNode(newNode);
    newNode->setNextNode(head);
    head = newNode;

    return head;
}

template <typename T>
Node<T>* insertNodeEnd(Node<T>*& head, T data)
{
    if (head == nullptr) {
        head = new Node<T>(data);
        return head;
    }

    Node<T>* newNode = new Node<T>(data);

    Node<T>* prevNode = nullptr;
    Node<T>* currentNode = head;

    while (currentNode != nullptr) {
        prevNode = currentNode;
        currentNode = currentNode->getNextNode();
    }

    newNode->setPrevNode(prevNode);
    prevNode->setNextNode(newNode);

    prevNode = nullptr;
    newNode = nullptr;
    currentNode = nullptr;

    return head;
}

template <typename T>
Node<T>* loopList(Node<T>* head)
{
    if (head == nullptr) {
        cout << "No hay elementos en el puntero suministrado" << endl;
        return nullptr;
    }

    while (head != nullptr) {
        if (head->getNextNode() == nullptr) {
            cout << std::format("{}", head->getData());
            break;
        } else {
            cout << std::format("{}, ", head->getData());
            head = head->getNextNode();
        }
    }

    return head;
}

int main()
{
    Node<int>* list1 = new Node(1);
    insertNodeEnd(list1, 2);
    insertNodeEnd(list1, 8);
    insertNodeEnd(list1, 0);
    insertNodeEnd(list1, 5);
    // cout << "here";

    sortList(list1);
    loopList(list1);

    // Node<int>* list2 = new Node(5);
    // insertNodeEnd(list2, 7);
    // insertNodeEnd(list2, 14);
    // insertNodeEnd(list2, 4);
    // insertNodeEnd(list2, 8);
    //
    // Node<int>* mergedList = mergeSort(list1, list2);
    // loopList(mergedList);

    return 0;
}
