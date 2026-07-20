#pragma once
#include <iostream>
#include <queue>
#include <deque>
#include "../NodeTree.hpp"

/**
 * zigzagLevelOrder — Recorrido en zigzag (nivel por nivel alternando dirección).
 *
 * Imprime el primer nivel de izquierda a derecha, el segundo de derecha
 * a izquierda, el tercero de izquierda a derecha, y así sucesivamente.
 *
 * Algoritmo: BFS con un deque por nivel. Si la dirección es izquierda→derecha,
 * inserta al final del deque; si es derecha→izquierda, inserta al inicio.
 * Alterna la dirección al terminar cada nivel.
 *
 * Complejidad: O(n).
 */
template <typename T>
void zigzagLevelOrder(NodeTree<T>* root)
{
    if (root == nullptr)
        return;

    std::queue<NodeTree<T>*> q;
    q.push(root);
    bool leftToRight = true;
    int level = 0;

    while (!q.empty()) {
        int levelSize = q.size();
        std::deque<T> levelDeque;

        for (int i = 0; i < levelSize; i++) {
            NodeTree<T>* node = q.front();
            q.pop();

            if (leftToRight)
                levelDeque.push_back(node->getData());
            else
                levelDeque.push_front(node->getData());

            if (node->getLeftNode())
                q.push(node->getLeftNode());
            if (node->getRightNode())
                q.push(node->getRightNode());
        }

        std::cout << "Nivel " << level << ": ";
        for (size_t i = 0; i < levelDeque.size(); i++)
            std::cout << levelDeque[i] << " ";
        std::cout << "\n";

        leftToRight = !leftToRight;
        level++;
    }
}
