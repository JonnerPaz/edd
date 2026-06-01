// Programar una función que evalue que no exista un bucle dentro
// de una lista doblemente enlazada de nodos

#include <format>
#include <iostream>
#include <unordered_set>

#include "DoubleLinkedNode.hpp"

using namespace std;

template <typename T>
Node<T>* insertNodeBeginning(Node<T>*& head, T data)
{
    // list does not exists, return new one
    if (head == nullptr) {
        head = new Node<T>(data);
        return head;
    }

    Node<T>* newNode = new Node<T>(data);

    head->setPrevNode(newNode);
    newNode->setNextNode(head);
    head = newNode;

    return head;
}

template <typename T>
Node<T>* insertNodeEnd(Node<T>*& head, T data)
{
    if (head == nullptr) {
        head = new Node<T>(data);
        return head;
    }

    Node<T>* newNode = new Node<T>(data);

    Node<T>* prevNode = nullptr;
    Node<T>* currentNode = head;

    while (currentNode != nullptr) {
        prevNode = currentNode;
        currentNode = currentNode->getNextNode();
    }

    newNode->setPrevNode(prevNode);
    prevNode->setNextNode(newNode);

    prevNode = nullptr;
    newNode = nullptr;
    currentNode = nullptr;

    return head;
}

template <typename T>
bool hasCycle(Node<T>* head, bool isForward)
{
    Node<T>* slow = head;
    Node<T>* fast = head;

    while (slow != nullptr && fast != nullptr) {
        fast = isForward ? fast->getNextNode() : fast->getPrevNode();
        if (fast == nullptr) {
            break;
        }

        fast = isForward ? fast->getNextNode() : fast->getPrevNode();
        if (fast == nullptr) {
            break;
        }

        slow = isForward ? slow->getNextNode() : slow->getPrevNode();

        if (slow == fast) {
            return true;
        }
    }

    return false;
}

// helper function de hasCycleSet
template <typename T>
bool traverseSet(Node<T>* head, bool isForward)
{
    unordered_set<Node<T>*> visitedNodes;
    Node<T>* current = head;

    while (current != nullptr) {
        // If current node is already present in the set,
        // there's a cycle. Return true
        if (visitedNodes.find(current) != visitedNodes.end()) {
            return true;
        }

        // Add the current node to the set
        visitedNodes.insert(current);
        current = isForward ? current->getNextNode() : current->getPrevNode();
    }

    return false;
}

/**
 *
 * @brief - Traverses the list and returns true if there is a cycle. This function traverses the
 * list in both directions
 * @param head - A ptr of the first node
 * @param isForward - A bool that indicates if the initial traversal is forward or backwards
 * @return true if there is a cycle
 */
template <typename T>
bool hasCycleSet(Node<T>* head, bool isForward)
{
    if (head == nullptr) {
        cout << "No hay elementos en el puntero suministrado" << endl;
        return false;
    }

    bool cycle = traverseSet(head, isForward);

    if (cycle) {
        return true;
    }

    // now backwards
    return traverseSet(head, !isForward);
}

int main()
{
    Node<int>* head = nullptr;

    insertNodeBeginning(head, 1);
    insertNodeBeginning(head, 2);
    insertNodeBeginning(head, 3);
    insertNodeBeginning(head, 4);
    insertNodeBeginning(head, 5);

    // current list:
    // 5 -> 4 -> 3 -> 2 -> 1

    bool cycle = hasCycle(head, true);
    bool cycleSet = hasCycleSet(head, true);
    cout << "--- PRUEBAS SIN CICLO ---" << endl;
    cout << format("hasCycle (Forward): {}", (cycle ? "Si" : "No")) << endl;
    cout << format("hasCycleSet (Forward & Backward): {}", (cycleSet ? "Si" : "No")) << endl;

    // --- CREATING FORWARD CYCLE ---
    // Node '1' (last node) will point to node '3'
    Node<int>* node5 = head;
    Node<int>* node4 = node5->getNextNode();
    Node<int>* node3 = node4->getNextNode();
    Node<int>* node2 = node3->getNextNode();
    Node<int>* node1 = node2->getNextNode();

    cout << "\n--- CREANDO CICLO (1 -> next -> 3) ---" << endl;
    node1->setNextNode(node3);

    cycle = hasCycle(head, true);
    cycleSet = hasCycleSet(head, true);
    cout << format("hasCycle (Forward): {}", cycle ? "Si (Detectado!)" : "No") << endl;
    cout << format("hasCycleSet (Forward & Backward): {}", cycleSet ? "Si (Detectado!)" : "No")
         << endl;

    // --- BREAING FORWARD CYCLE ---
    node1->setNextNode(nullptr);

    // --- CREATING BACKWARD CYCLE ---
    // Node '5' (first node) will point to node '2'
    cout << "\n--- CREANDO CICLO (5 -> prev -> 2) ---" << endl;
    node5->setPrevNode(node2);

    cycle = hasCycle(head, false);
    cycleSet = hasCycleSet(head, false);
    cout << format("hasCycle (Backward): {}", cycle ? "Si (Detectado!)" : "No") << endl;
    cout << format("hasCycleSet (Backward & Forward): {}", cycleSet ? "Si (Detectado!)" : "No")
         << endl;

    return 0;
}
