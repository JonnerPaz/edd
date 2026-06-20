#include <format>
#include <iostream>

#include "List.hpp"
#include "Node.hpp"

using namespace std;

/**
 * @brief - Crea una lista con los primeros nodos de la misma. En la lista, el orden será según cómo
 * hayas pasado el nodo en los parámetros
 * @param node_a - Puede ser un nodo o una lista de nodos
 * @param node_b  - Este debe ser un nodo huerfano
 */
template <typename T>
Node<T>* insertNodes(Node<T>* node_a, Node<T>* node_b, List<T>* list)
{
    Node<T>* head = nullptr;
    if (list->getHead() == nullptr) {
        head = node_a;
        list->setHead(head);
    } else {
        head = list->getHead();

        while (head->getNextNode() != nullptr) {
            head = head->getNextNode();
        }
        head->setNextNode(node_a);
    }

    Node<T>* prevNode = nullptr;
    Node<T>* curNode = head;

    while (curNode != nullptr) {
        prevNode = curNode;
        curNode = curNode->getNextNode();

        if (curNode == nullptr) {
            break;
        }
    }

    prevNode->setNextNode(node_b);

    head = nullptr;
    prevNode = nullptr;
    curNode = nullptr;

    return list->getHead();
}

/**
 * @brief - Recorre la lista que le pases y la imprime en consola
 * @param head - El puntero al primer nodo de la lista
 */
template <typename T>
void traversingList(Node<T>* head)
{
    if (head == nullptr) {
        cout << "No hay elementos en el puntero suministrado" << endl;
    }

    while (head != nullptr) {
        cout << std::format("{}, ", head->getData());
        head = head->getNextNode();

        if (head == nullptr) {
            cout << "\n";
        }
    }
}

template <typename T>
void deleteNodeBegin(Node<T>*& head)
{
    if (head == nullptr) {
        cout << "No hay elementos en el puntero suministrado" << endl;
    }

    Node<T>* temp = head;
    head = head->getNextNode();
    delete temp;
    temp = nullptr;
}

template <typename T>
void deleteNodeEnd(Node<T>*& head)
{
    if (head == nullptr) {
        cout << "No hay elementos en el puntero suministrado" << endl;
    }

    Node<T>* prevNode = nullptr;
    Node<T>* curNode = head;

    while (curNode->getNextNode() != nullptr) {
        prevNode = curNode;
        curNode = curNode->getNextNode();
    }

    prevNode->setNextNode(nullptr);
    delete curNode;

    curNode = nullptr;
    prevNode = nullptr;
}

int main()
{
    List<int>* list = new List<int>();
    Node<int>* first_node = new Node{4};
    Node<int>* second_node = new Node{5};

    Node<int>* head = nullptr;
    traversingList(head);

    head = insertNodes(first_node, second_node, list);
    traversingList(head);

    Node<int>* third_node = new Node{6};
    Node<int>* fourth_node = new Node{7};
    third_node->setNextNode(fourth_node);

    Node<int>* aditional_node = new Node{16};
    head = insertNodes(third_node, aditional_node, list);
    traversingList(head);

    return 0;
}
