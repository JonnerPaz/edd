#pragma once

#include "./Node.hpp"

template <typename T>
class List
{
   private:
    Node<T>* head;
    int length = 0;

   public:
    List() : head(nullptr) {}

    List(Node<T>* head) : head(head) {}

    ~List()
    {
        Node<T>* current = this->head;
        while (current != nullptr) {
            Node<T>* next = current->getNextNode();
            delete current;
            current = next;
        }
    }

    Node<T>* getHead() { return this->head; }

    void push(T data)
    {
        Node<T>* newNode = new Node<T>(data);
        if (this->head == nullptr) {
            this->head = newNode;
        } else {
            Node<T>* current = this->head;
            while (current->getNextNode() != nullptr) {
                current = current->getNextNode();
            }
            current->setNextNode(newNode);
        }

        this->length++;
        return;
    }

    void pop()
    {
        if (this->head == nullptr) {
            return;
        }

        if (this->head->getNextNode() == nullptr) {
            delete this->head;
            this->head = nullptr;
            this->length--;
            return;
        }

        Node<T>* prevNode = nullptr;
        Node<T>* currentNode = this->head;

        while (currentNode->getNextNode() != nullptr) {
            prevNode = currentNode;
            currentNode = currentNode->getNextNode();
        }

        prevNode->setNextNode(nullptr);
        delete currentNode;
        this->length--;
    }

    void shift()
    {
        if (this->head == nullptr) {
            return;
        }

        Node<T>* tmp = this->head;
        this->head = this->head->getNextNode();
        delete tmp;
        this->length--;
        tmp = nullptr;
    }

    void unshift(T data)
    {
        Node<T>* newNode = new Node<T>(data);
        if (this->head == nullptr) {
            this->head = newNode;
            return;
        } else {
            newNode->setNextNode(this->head);
            this->head = newNode;
        }

        this->length++;
        return;
    }

    Node<T>* get(int index)
    {
        if (!this->head || index < 0 || index >= this->length) {
            return nullptr;
        }

        Node<T>* curNode = this->head;
        for (int i = 0; i < index; i++) {
            curNode = curNode->getNextNode();

            if (curNode == nullptr) {
                return nullptr;
            }
        }

        return curNode;
    }

    bool set(int index, T data)
    {
        Node<T>* node = this->get(index);
        if (node) {
            node->setData(data);
            return node;
        }

        return false;
    }

    bool insert(int index, T data)
    {
        if (index < 0 || index > this->length) {
            return false;
        }

        // inserta al inicio de la lista
        if (index == 0) {
            this->unshift(data);
            return true;
        }

        // inserta al final de la lista
        if (index == this->length) {
            this->push(data);
            return true;
        }

        Node<T>* prevNode = this->get(index - 1);
        Node<T>* currentNode = this->get(index);

        if (prevNode == nullptr || currentNode == nullptr) {
            return false;
        }

        Node<T>* newNode = new Node<T>(data);
        newNode->setNextNode(currentNode);
        prevNode->setNextNode(newNode);
        this->length++;
        return true;
    }

    bool remove(int index)
    {
        if (index < 0 || index >= this->length) {
            return false;
        }

        // elimina el primer nodo
        if (index == 0) {
            this->shift();
            return true;
        }

        // elimina el último nodo
        if (index == this->length - 1) {
            this->pop();
            return true;
        }

        Node<T>* prevNode = this->get(index - 1);
        Node<T>* currentNode = this->get(index);

        if (prevNode == nullptr || currentNode == nullptr) {
            return false;
        }

        prevNode->setNextNode(currentNode->getNextNode());
        delete currentNode;
        this->length--;
        return true;
    }

    bool reverse()
    {
        if (this->head == nullptr) {
            return false;
        }

        Node<T>* prevNode = nullptr;
        Node<T>* currentNode = this->head;
        Node<T>* nextNode = nullptr;

        while (currentNode != nullptr) {
            nextNode = currentNode->getNextNode();
            currentNode->setNextNode(prevNode);
            prevNode = currentNode;
            currentNode = nextNode;
        }

        this->head = prevNode;
        return true;
    }

    int getSize() const { return this->length; }
};
