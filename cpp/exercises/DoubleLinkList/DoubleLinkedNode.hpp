// This class is not really necessary given that I already have a Node class
// However, I wanted to leave the other as is for history's sake
// This one introduces the prev pointer
#pragma once

/**
 * @brief - Clase que representa un nodo de una lista doblemente enlazada
 */
template <typename T>
class Node
{
   private:
    T data;
    Node<T>* next;
    Node<T>* prev;

   public:
    Node(T data) : data(data), next(nullptr), prev(nullptr) {}

    Node<T>* getNextNode() const { return next == nullptr ? nullptr : next; }

    Node<T>* getPrevNode() const { return prev == nullptr ? nullptr : prev; }

    void setNextNode(Node<T>* next) { this->next = next; }

    void setPrevNode(Node<T>* prev) { this->prev = prev; }

    T getData() { return data; }

    void setData(T data) { this->data = data; }
};
