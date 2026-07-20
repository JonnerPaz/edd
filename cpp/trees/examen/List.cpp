#include "List.hpp"

List::List() : cabeza(nullptr) {}

List::~List()
{
    NodeList* actual = cabeza;
    while (actual != nullptr) {
        NodeList* tmp = actual;
        actual = actual->siguiente;
        delete tmp;
    }
}

void List::add(int v)
{
    NodeList* nuevo = new NodeList(v);
    if (cabeza == nullptr) {
        cabeza = nuevo;
        return;
    }
    NodeList* tmp = cabeza;
    while (tmp->siguiente != nullptr) tmp = tmp->siguiente;
    tmp->siguiente = nuevo;
}

void List::sort()
{
    if (cabeza == nullptr) return;
    bool swapped;
    do {
        swapped = false;
        NodeList* tmp = cabeza;
        while (tmp->siguiente != nullptr) {
            if (tmp->valor > tmp->siguiente->valor) {
                int aux = tmp->valor;
                tmp->valor = tmp->siguiente->valor;
                tmp->siguiente->valor = aux;
                swapped = true;
            }
            tmp = tmp->siguiente;
        }
    } while (swapped);
}

NodeList* List::getHead() const
{
    return cabeza;
}

bool List::isEmpty() const
{
    return cabeza == nullptr;
}
