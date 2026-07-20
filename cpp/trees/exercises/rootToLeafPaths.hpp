#pragma once
#include <algorithm>
#include <iostream>
#include "../NodeTree.hpp"

/**
 * rootToLeafPaths — Imprime todos los caminos desde la raíz hasta cada hoja.
 *
 * Cada camino se muestra como una secuencia de valores separados por " → ".
 * Ejemplo: 5 → 3 → 2
 *
 * Algoritmo: DFS con un arreglo auxiliar que almacena el camino actual.
 * Cuando se llega a una hoja, se imprime el camino completo.
 *
 * Complejidad: O(n).
 */
template <typename T>
int treeHeight(NodeTree<T>* node)
{
    if (node == nullptr)
        return 0;
    return 1 + std::max(treeHeight(node->getLeftNode()),
                        treeHeight(node->getRightNode()));
}

template <typename T>
void printPaths(NodeTree<T>* node, T* path, int depth)
{
    if (node == nullptr)
        return;

    path[depth] = node->getData();

    if (node->getLeftNode() == nullptr &&
        node->getRightNode() == nullptr) {
        for (int i = 0; i <= depth; i++) {
            if (i > 0)
                std::cout << " → ";
            std::cout << path[i];
        }
        std::cout << "\n";
    } else {
        printPaths(node->getLeftNode(), path, depth + 1);
        printPaths(node->getRightNode(), path, depth + 1);
    }
}

template <typename T>
void rootToLeafPaths(NodeTree<T>* root)
{
    if (root == nullptr)
        return;

    int h = treeHeight(root);
    T* path = new T[h];
    printPaths(root, path, 0);
    delete[] path;
}
