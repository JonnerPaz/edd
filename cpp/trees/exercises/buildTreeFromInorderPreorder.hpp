#pragma once
#include "../NodeTree.hpp"

/**
 * buildTreeFromInorderPreorder — Construye un árbol binario a partir de
 * los recorridos inorder y preorder.
 *
 * El primer elemento de preorder es siempre la raíz. Se busca ese
 * elemento en inorder: los elementos a la izquierda forman el subárbol
 * izquierdo, y los de la derecha el subárbol derecho. Se repite
 * recursivamente.
 *
 * Complejidad: O(n²) (búsqueda lineal de la raíz en cada paso).
 */
template <typename T>
NodeTree<T>* buildTree(const T* preorder, int& preIdx,
                        const T* inorder, int inLeft, int inRight)
{
    if (inLeft > inRight)
        return nullptr;

    T rootVal = preorder[preIdx++];
    NodeTree<T>* root = new NodeTree<T>(rootVal);

    int inIdx = inLeft;
    while (inorder[inIdx] != rootVal)
        inIdx++;

    root->setLeftNode(
        buildTree(preorder, preIdx, inorder, inLeft, inIdx - 1));
    root->setRightNode(
        buildTree(preorder, preIdx, inorder, inIdx + 1, inRight));

    return root;
}

template <typename T>
NodeTree<T>* buildTreeFromInorderPreorder(const T* preorder,
                                           const T* inorder, int size)
{
    int preIdx = 0;
    return buildTree(preorder, preIdx, inorder, 0, size - 1);
}
