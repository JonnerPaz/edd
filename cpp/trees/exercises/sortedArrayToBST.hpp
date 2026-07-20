#pragma once
#include "../NodeTree.hpp"

/**
 * sortedArrayToBST — Construye un BST balanceado desde un arreglo ordenado.
 *
 * Toma el elemento del medio como raíz para garantizar balance,
 * y construye recursivamente los subárboles izquierdo (mitad izquierda)
 * y derecho (mitad derecha).
 *
 * Complejidad: O(n).
 */
template <typename T>
NodeTree<T>* sortedArrayToBST(const T* arr, int left, int right)
{
    if (left > right)
        return nullptr;

    int mid = left + (right - left) / 2;
    NodeTree<T>* node = new NodeTree<T>(arr[mid]);

    node->setLeftNode(sortedArrayToBST(arr, left, mid - 1));
    node->setRightNode(sortedArrayToBST(arr, mid + 1, right));

    return node;
}

template <typename T>
NodeTree<T>* sortedArrayToBST(const T* arr, int size)
{
    return sortedArrayToBST(arr, 0, size - 1);
}
