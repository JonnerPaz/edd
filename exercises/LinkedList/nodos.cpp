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
Node<T>* insert_nodes(Node<T>* node_a, Node<T>* node_b, List<T>* list)
{
    Node<T>* head = nullptr;
    if (list->getHead() == nullptr) {
        head = node_a;
        list->setHead(head);
    } else {
        head = list->getHead();

        // traversing_list
        while (head->getNextNode() != nullptr) {
            head = head->getNextNode();
        }
        head->setNextNode(node_a);
    }

    Node<T>* prev_node = nullptr;
    Node<T>* current_node = head;

    while (current_node != nullptr) {
        prev_node = current_node;
        current_node = current_node->getNextNode();

        if (current_node == nullptr) {
            break;
        }
    }

    prev_node->setNextNode(node_b);

    head = nullptr;
    prev_node = nullptr;
    current_node = nullptr;

    return list->getHead();
}

/**
 * @brief - Recorre la lista que le pases y la imprime en consola
 * @param head - El puntero al primer nodo de la lista
 */
template <typename T>
void traversing_list(Node<T>* head)
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

int main()
{
    List<int>* list = new List<int>();
    Node<int>* first_node = new Node{4};
    Node<int>* second_node = new Node{5};

    Node<int>* head = nullptr;
    traversing_list(head);

    head = insert_nodes(first_node, second_node, list);
    traversing_list(head);

    Node<int>* third_node = new Node{6};
    Node<int>* fourth_node = new Node{7};
    third_node->setNextNode(fourth_node);

    Node<int>* aditional_node = new Node{16};
    head = insert_nodes(third_node, aditional_node, list);
    traversing_list(head);

    return 0;
}
