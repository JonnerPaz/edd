#include <format>
#include <iostream>

#include "Node.hpp"

using namespace std;

void traversing_list(Node<int>* head)
{
    while (head != nullptr) {
        cout << std::format("{}, ", head->getData());
        head = head->getNextNode();

        if (head == nullptr) {
            cout << "\n";
        }
    }
}

void insert_node(Node<int>* head, int data)
{
    Node<int>* new_node = new Node<int>(data);
    new_node->setNextNode(head);
    head = new_node;

    delete new_node;
    new_node = nullptr;
}

/**
 * @param head - a pointer reference to the first node
 */
void insert_node_from_beginning(Node<int>*& head, int data)
{
    Node<int>* new_node = new Node<int>(data);

    // if the list has data that is smaller than the new node
    if (new_node->getData() < head->getData()) {
        // tmp is a ptr to the first node
        Node<int>* tmp = head;

        // set the new node as the first node,
        // carrying the rest of the list that tmp has
        new_node->setNextNode(tmp);

        // set the head back to the new node, now it points to the first node
        head = new_node;

        tmp = nullptr;
    }
    new_node = nullptr;

    return;
}

int main()
{
    // 1. Create head, a ptr to the first node
    // remember to set the type because it is a template
    // even if the variable itself is a ptr
    Node<int>* head = nullptr;

    // 2. Create the first node
    head = new Node<int>(0);

    // 3. Create the second node
    Node<int>* second = new Node<int>(1);
    head->setNextNode(second);

    cout << std::format("{}\n", head->getData());                 //  0
    cout << std::format("{}\n", head->getNextNode()->getData());  // 1
    // As there is no third node, the next node is nullptr. Accessing its data will cause a segfault
    // cout << std::format("{}\n", head->getNextNode()->getNextNode()->getData()); // program dies

    traversing_list(head);  // 0, 1

    cout << "Inserting nodes from beginning\n";
    insert_node_from_beginning(head, -1);
    traversing_list(head);  // -1, 0, 1
    return 0;
}
