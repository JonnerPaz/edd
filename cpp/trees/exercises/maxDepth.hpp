#pragma once
#include <algorithm>
#include "../NodeTree.hpp"

/**
 * maxDepth — Altura (profundidad máxima) de un árbol binario.
 *
 * Es la cantidad de nodos en el camino más largo desde la raíz
 * hasta una hoja. Árbol vacío retorna 0, solo raíz retorna 1.
 *
 * Algoritmo: recursivo. Altura = 1 + max(altura_izq, altura_der).
 *
 * Complejidad: O(n).
 */
template <typename T>
int maxDepth(NodeTree<T>* root)
{
    if (root == nullptr)
        return 0;
    return 1 + std::max(maxDepth(root->getLeftNode()),
                        maxDepth(root->getRightNode()));
}
