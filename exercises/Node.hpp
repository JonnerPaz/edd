#pragma once

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

template <typename T>
class List
{
   private:
    Node<T>* head;

   public:
    List() : head(nullptr) {}

    List(Node<T>* head) : head(head) {}

    Node<T>* getHead() { return this->head; }

    Node<T>* setHead(Node<T>* head)
    {
        if (this->head != nullptr) {
            return this->head;
        }

        this->head = head;
        return this->head;
    }
};
