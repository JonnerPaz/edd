#pragma once
#include <algorithm>
#include <cstdlib>
#include "../NodeTree.hpp"

/**
 * isBalanced — Verifica si un árbol binario está balanceado en altura.
 *
 * Un árbol está balanceado si para cada nodo la diferencia de alturas
 * entre sus subárboles izquierdo y derecho es ≤ 1.
 *
 * Algoritmo: DFS con poda (retorna -1 si está desbalanceado).
 * Para cada nodo calcula la altura de sus hijos. Si la diferencia
 * entre ambos es > 1, propaga -1 hacia arriba indicando desbalance.
 *
 * Complejidad: O(n).
 */
template <typename T>
int checkHeight(NodeTree<T>* root)
{
    if (root == nullptr)
        return 0;

    int left = checkHeight(root->getLeftNode());
    if (left == -1)
        return -1;

    int right = checkHeight(root->getRightNode());
    if (right == -1)
        return -1;

    if (std::abs(left - right) > 1)
        return -1;

    return 1 + std::max(left, right);
}

template <typename T>
bool isBalanced(NodeTree<T>* root)
{
    return checkHeight(root) != -1;
}
