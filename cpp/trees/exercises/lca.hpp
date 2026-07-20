#pragma once
#include "../NodeTree.hpp"

/**
 * lcaBST — Ancestro común más cercano (Lowest Common Ancestor) en un BST.
 *
 * Dados dos valores a y b, encuentra el nodo más profundo que es
 * ancestro de ambos. Aprovecha la propiedad del BST para buscar
 * el punto donde a y b se separan (uno va a la izquierda y otro
 * a la derecha, o uno es igual a la raíz).
 *
 * Algoritmo:
 * - Si ambos son menores que la raíz → LCA está a la izquierda.
 * - Si ambos son mayores que la raíz → LCA está a la derecha.
 * - Sino → la raíz actual es el LCA.
 *
 * Complejidad: O(log n) promedio, O(n) peor caso.
 */
template <typename T>
NodeTree<T>* lcaBST(NodeTree<T>* root, T a, T b)
{
    if (root == nullptr)
        return nullptr;

    if (a < root->getData() && b < root->getData())
        return lcaBST(root->getLeftNode(), a, b);

    if (a > root->getData() && b > root->getData())
        return lcaBST(root->getRightNode(), a, b);

    return root;
}
