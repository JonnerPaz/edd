#pragma once
#include "../NodeTree.hpp"

/**
 * invertTree — Invierte un árbol binario (espejo).
 *
 * Intercambia recursivamente el hijo izquierdo con el derecho
 * en cada nodo. El árbol resultante es la imagen espejo del original.
 *
 * Algoritmo: recorrido postorden (izquierdo → derecho → raíz).
 * Para cada nodo, primero invierte los subárboles y luego
 * intercambia los punteros left y right.
 *
 * Complejidad: O(n), donde n es la cantidad de nodos.
 */
template <typename T>
NodeTree<T>* invertTree(NodeTree<T>* root)
{
    if (root == nullptr)
        return nullptr;

    NodeTree<T>* left = invertTree(root->getLeftNode());
    NodeTree<T>* right = invertTree(root->getRightNode());

    root->setLeftNode(right);
    root->setRightNode(left);

    return root;
}
