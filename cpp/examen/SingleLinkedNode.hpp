#pragma once

/**
 * @brief - Clase que representa un nodo de una lista simple
 */
template <typename T>
class Node
{
   private:
    T data;
    Node<T>* next;

   public:
    Node(T data) : data(data), next(nullptr) {};

    Node<T>* getNextNode() { return next == nullptr ? nullptr : next; };

    void setNextNode(Node<T>* next) { this->next = next; };

    T getData() { return data; };

    void setData(T data) { this->data = data; };
};
