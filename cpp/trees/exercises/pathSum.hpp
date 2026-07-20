#pragma once
#include "../NodeTree.hpp"

/**
 * hasPathSum — Determina si existe un camino raíz → hoja cuya suma
 * sea igual al valor objetivo.
 *
 * Resta el valor del nodo actual del objetivo y verifica recursivamente
 * si algún hijo puede completar la suma restante. Cuando llega a una hoja,
 * verifica si el valor restante es 0.
 *
 * Complejidad: O(n).
 */
template <typename T>
bool hasPathSum(NodeTree<T>* root, T target)
{
    if (root == nullptr)
        return false;

    T remaining = target - root->getData();

    if (root->getLeftNode() == nullptr &&
        root->getRightNode() == nullptr)
        return remaining == 0;

    return hasPathSum(root->getLeftNode(), remaining) ||
           hasPathSum(root->getRightNode(), remaining);
}
