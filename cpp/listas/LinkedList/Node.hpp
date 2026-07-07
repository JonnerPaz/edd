#pragma once

/**
 * @brief - Clase que representa un nodo de una lista simple
 */
template <typename T>
class BinaryNode
{
   private:
    T data;
    BinaryNode<T>* next;

   public:
    BinaryNode(T data) : data(data), next(nullptr) {};

    BinaryNode<T>* getNextNode() { return next == nullptr ? nullptr : next; };

    void setNextNode(BinaryNode<T>* next) { this->next = next; };

    T getData() { return data; };

    void setData(T data) { this->data = data; };
};
