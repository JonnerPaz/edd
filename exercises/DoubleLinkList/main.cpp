#include <format>
#include <iostream>

#include "DoubleLinkedNode.hpp"

using namespace std;

void deleteNode(Node<int>*& head, int data)
{
    Node<int>* prev_node = nullptr;
    Node<int>* current_node = head;

    while (current_node->getNextNode() != nullptr) {
        prev_node = current_node;
        current_node = current_node->getNextNode();

        // first node only
        if (head->getData() == data) {
            Node<int>* tmp = head;
            head = head->getNextNode();
            delete tmp;
            break;
        }

        // middle or last node
        if (current_node->getData() == data && head->getData() != data) {
            Node<int>* tmp = current_node;
            prev_node->setNextNode(current_node->getNextNode());
            delete tmp;
            break;
        }
    }

    current_node = nullptr;
    prev_node = nullptr;

    return;
}

void freeList(Node<int>*& head)
{
    Node<int>* tmp = nullptr;

    while (head != nullptr) {
        tmp = head;
        head = head->getNextNode();
        delete tmp;
    }
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
    return 0;
}
