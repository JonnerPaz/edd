#include <iostream>
#include <stack>

#include "tree.hpp"

using namespace std;

void printTree(NodeTree<int>* node, bool recursive)
{
    if (recursive) {
        if (node == nullptr) {
            return;
        }

        printTree(node->getLeftNode(), true);
        std::cout << node->getData() << " ";
        printTree(node->getRightNode(), true);
    } else {
        stack<NodeTree<int>*> st;
        NodeTree<int>* cur = node;

        while (cur != nullptr || !st.empty()) {
            while (cur != nullptr) {
                st.push(cur);
                cur = cur->getLeftNode();
            }

            cur = st.top();
            st.pop();

            std::cout << cur->getData() << " ";

            cur = cur->getRightNode();
        }
    }
}

int main()
{
    BSTree<int> tree = BSTree<int>(nullptr);

    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    cout << "IMPRIMIENDO Árbol (En preorden):" << endl;
    cout << "Recorrido recursivo: ";
    printTree(tree.getRoot(), true);
    cout << "\n";

    cout << "Recorrido iterativo: ";
    printTree(tree.getRoot(), false);
    cout << "\n";

    return 0;
}
