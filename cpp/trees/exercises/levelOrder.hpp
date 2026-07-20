#pragma once
#include <iostream>
#include <queue>
#include "../NodeTree.hpp"

/**
 * levelOrder — Recorrido por niveles (BFS) de un árbol binario.
 *
 * Imprime los nodos nivel por nivel, de izquierda a derecha.
 * Cada nivel se imprime en una línea separada.
 *
 * Algoritmo: usa una cola (queue). Procesa cada nivel completo
 * antes de pasar al siguiente (cuenta la cantidad de nodos por nivel).
 *
 * Complejidad: O(n).
 */
template <typename T>
void levelOrder(NodeTree<T>* root)
{
    if (root == nullptr)
        return;

    std::queue<NodeTree<T>*> q;
    q.push(root);
    int level = 0;

    while (!q.empty()) {
        int levelSize = q.size();
        std::cout << "Nivel " << level << ": ";

        for (int i = 0; i < levelSize; i++) {
            NodeTree<T>* node = q.front();
            q.pop();
            std::cout << node->getData() << " ";

            if (node->getLeftNode())
                q.push(node->getLeftNode());
            if (node->getRightNode())
                q.push(node->getRightNode());
        }

        std::cout << "\n";
        level++;
    }
}
