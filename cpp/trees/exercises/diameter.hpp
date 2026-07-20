#pragma once
#include <algorithm>
#include "../NodeTree.hpp"

/**
 * diameter — Diámetro de un árbol binario.
 *
 * El diámetro es la longitud del camino más largo entre dos nodos
 * cualesquiera del árbol (medido en cantidad de aristas).
 * Puede pasar o no por la raíz.
 *
 * Algoritmo: DFS que calcula la altura de cada subárbol y actualiza
 * el diámetro como max(diámetro, altura_izq + altura_der).
 *
 * Complejidad: O(n).
 */
template <typename T>
int diameterHelper(NodeTree<T>* root, int& ans)
{
    if (root == nullptr)
        return 0;

    int left = diameterHelper(root->getLeftNode(), ans);
    int right = diameterHelper(root->getRightNode(), ans);

    ans = std::max(ans, left + right);

    return 1 + std::max(left, right);
}

template <typename T>
int diameter(NodeTree<T>* root)
{
    int ans = 0;
    diameterHelper(root, ans);
    return ans;
}
