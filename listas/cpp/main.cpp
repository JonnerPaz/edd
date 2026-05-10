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

void insert_node_from_end(Node<int>*& head, int data)
{
    Node<int>* new_node = new Node{data};

    Node<int>* prevNode = nullptr;
    auto currentNode = head;

    while (currentNode->getData() < new_node->getData() && currentNode != nullptr) {
        prevNode = currentNode;
        currentNode = currentNode->getNextNode();

        if (currentNode == nullptr) {
            break;
        }
    }

    prevNode->setNextNode(new_node);

    prevNode = nullptr;
    new_node = nullptr;
    currentNode = nullptr;
}

void insert_node_in_between(Node<int>*& head, int data)
{
    Node<int>* new_node = new Node<int>(data);

    Node<int>* prev_node = nullptr;
    auto current_node = head;

    while (current_node->getData() < new_node->getData() && current_node != nullptr) {
        prev_node = current_node;
        current_node = current_node->getNextNode();

        if (current_node == nullptr) {
            break;
        }
    }

    // from here, currentNode is the node that is bigger than the new node
    // and prevNode is smaller than the new node

    // insert the new node between prevNode and currentNode
    prev_node->setNextNode(new_node);
    new_node->setNextNode(current_node);

    prev_node = nullptr;
    current_node = nullptr;
    new_node = nullptr;
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

    cout << "Inserting nodes from end\n";
    insert_node_from_end(head, 3);
    traversing_list(head);  // -1, 0, 1, 3

    cout << "Inserting nodes in between\n";
    insert_node_in_between(head, 2);
    traversing_list(head);  // -1, 0, 1, 2, 3

    return 0;
}
