#pragma once
#include <limits>
#include "../NodeTree.hpp"

/**
 * isValidBST — Verifica si un árbol binario cumple la propiedad de BST.
 *
 * Para cada nodo, todos los valores en su subárbol izquierdo deben
 * ser menores, y todos en el derecho deben ser mayores.
 *
 * Algoritmo: recorrido con cotas (min, max).
 * Al ir a la izquierda, actualiza la cota superior (max = raíz).
 * Al ir a la derecha, actualiza la cota inferior (min = raíz).
 * Si algún nodo viola las cotas, no es BST.
 *
 * Complejidad: O(n).
 */
template <typename T>
bool isValidBST(NodeTree<T>* root, T min, T max)
{
    if (root == nullptr)
        return true;

    if (root->getData() <= min || root->getData() >= max)
        return false;

    return isValidBST(root->getLeftNode(), min, root->getData()) &&
           isValidBST(root->getRightNode(), root->getData(), max);
}

template <typename T>
bool isValidBST(NodeTree<T>* root)
{
    return isValidBST(root,
                      std::numeric_limits<T>::min(),
                      std::numeric_limits<T>::max());
}
