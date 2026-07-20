#pragma once
#include <stack>
#include "../NodeTree.hpp"

/**
 * kthSmallest — Encuentra el k-ésimo elemento más pequeño en un BST.
 *
 * Algoritmo: recorrido inorden iterativo con pila (stack).
 * El inorden de un BST genera los valores en orden ascendente,
 * así que el k-ésimo valor visitado es la respuesta.
 *
 * Complejidad: O(h + k), donde h es la altura del árbol.
 */
template <typename T>
T kthSmallest(NodeTree<T>* root, int k)
{
    std::stack<NodeTree<T>*> st;
    NodeTree<T>* current = root;

    while (current != nullptr || !st.empty()) {
        while (current != nullptr) {
            st.push(current);
            current = current->getLeftNode();
        }

        current = st.top();
        st.pop();

        if (--k == 0)
            return current->getData();

        current = current->getRightNode();
    }

    return T();
}
