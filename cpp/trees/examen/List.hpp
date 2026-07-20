#pragma once

struct NodeList {
    int valor;
    NodeList* siguiente;

    NodeList(int v) : valor(v), siguiente(nullptr) {}
};

class List
{
   private:
    NodeList* cabeza;

   public:
    List();
    ~List();
    void add(int v);
    void sort();
    NodeList* getHead() const;
    bool isEmpty() const;
};
