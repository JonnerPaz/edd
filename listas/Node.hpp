#pragma once

template <typename T>
class Node
{
   private:
    T data;
    Node<T>* next;

   public:
    Node(T data) : data(data) {};

    Node<T>* getNextNode() { return next == nullptr ? nullptr : next; };

    void setNextNode(Node<T>* next) { this->next = next; };

    T getData() { return data; };

    void setData(T data) { this->data = data; };
};
