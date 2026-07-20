/*
 * Crear un programa que ordene en un arbol binario numero de tal manera que los valores mayores
 * sean aquellos en los niveles más bajos y los menores en los niveles más altos
 */

#pragma once

#include "List.hpp"
#include "NodeTree.hpp"

/**
 * A pesar que la clase se llama MaxToMinTree,
 * Esta es sólo una clase wrapper que permite la construcción del arbol como lo pide el ejercicio
 * Pero la verdadera lógica de árbol se encuentra en AVL.cpp
 */
class MaxToMinTree
{
   private:
    NodeTree<int>* raiz;

    static NodeTree<int>* buildTree(NodeList* lista);
    void showTree(NodeTree<int>* nodo) const;
    void cleanTree(NodeTree<int>* nodo);
    static void inorderToList(NodeTree<int>* nodo, List& lista);

   public:
    MaxToMinTree();
    ~MaxToMinTree();
    void exec();
};
