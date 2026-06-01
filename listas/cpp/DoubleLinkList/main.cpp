#include <format>
#include <iostream>

#include "DoubleLinkedNode.hpp"

using namespace std;

void deleteNode(Node<int>*& head, int data)
{
    Node<int>* prevNode = nullptr;
    Node<int>* curNode = head;

    while (curNode->getNextNode() != nullptr) {
        prevNode = curNode;
        curNode = curNode->getNextNode();

        // first node only
        if (head->getData() == data) {
            Node<int>* tmp = head;
            head = head->getNextNode();
            delete tmp;
            break;
        }

        // middle or last node
        if (curNode->getData() == data && head->getData() != data) {
            Node<int>* tmp = curNode;
            prevNode->setNextNode(curNode->getNextNode());
            delete tmp;
            break;
        }
    }

    curNode = nullptr;
    prevNode = nullptr;

    return;
}

template <typename T>
void deleteAtNthPos(Node<T>*& head, int pos)
{
    if (head == nullptr || pos < 0) {
        return;
    }

    Node<T>* curNode = head;

    if (pos == 0) {
        head = head->getNextNode();

        if (head != nullptr) {
            head->setPrevNode(nullptr);
        }

        delete curNode;
        return;
    }

    // go to nth node
    for (int i = 0; i < pos && curNode != nullptr; i++) {
        curNode = curNode->getNextNode();
    }

    // pos out of range
    if (curNode == nullptr) {
        return;
    }

    // neighbor nodes
    Node<T>* prevNode = curNode->getPrevNode();
    Node<T>* nextNode = curNode->getNextNode();

    if (curNode != nullptr) {
        prevNode->setNextNode(nextNode);
    }

    if (nextNode != nullptr) {
        nextNode->setPrevNode(prevNode);
    }

    delete curNode;
    curNode = nullptr;
    prevNode = nullptr;
    nextNode = nullptr;
}

template <typename T>
void removeAllOcurrences(Node<T>* head, T valueToDelete)
{
    if (head == nullptr) {
        return;
    }

    Node<T>* curNode = head;

    while (curNode != nullptr) {
        // save next before deleting. Otherwise it will be lost
        Node<T>* nextNode = curNode->getNextNode();

        if (curNode->getData() == valueToDelete) {
            Node<T>* prevNode = curNode->getPrevNode();

            if (curNode == head) {
                head = nextNode;
            }

            if (prevNode != nullptr) {
                prevNode->setNextNode(nextNode);
            }

            if (nextNode != nullptr) {
                nextNode->setPrevNode(prevNode);
            }

            delete curNode;
        }

        curNode = nextNode;
    }

    curNode = nullptr;
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
