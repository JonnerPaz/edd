#pragma once
#include "../NodeTree.hpp"

/**
 * sameTree — Determina si dos árboles binarios son idénticos.
 *
 * Dos árboles son idénticos si tienen la misma estructura
 * y los mismos valores en cada posición correspondiente.
 *
 * Algoritmo: comparación recursiva en preorden.
 * - Si ambos son nullptr → son iguales.
 * - Si uno es nullptr y el otro no → diferentes.
 * - Si los valores difieren → diferentes.
 * - Sino, comparar recursivamente izquierdo y derecho.
 *
 * Complejidad: O(min(n, m)), donde n y m son las cantidades de nodos.
 */
template <typename T>
bool sameTree(NodeTree<T>* p, NodeTree<T>* q)
{
    if (p == nullptr && q == nullptr)
        return true;
    if (p == nullptr || q == nullptr)
        return false;
    if (p->getData() != q->getData())
        return false;
    return sameTree(p->getLeftNode(), q->getLeftNode()) &&
           sameTree(p->getRightNode(), q->getRightNode());
}
