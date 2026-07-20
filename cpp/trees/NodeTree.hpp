#pragma once

/**
 * Nodo base para árboles binarios (BST y AVL).
 * Cada nodo almacena un valor, punteros a los hijos izquierdo y derecho,
 * y la altura del subárbol del cual es raíz (útil para AVL).
 */
template <typename T>
class NodeTree
{
   private:
    T data;
    NodeTree<T>* left;
    NodeTree<T>* right;
    int height;

   public:
    /** Construye un nodo con el valor dado. Altura inicial = 1. */
    NodeTree(T data) : data(data)
    {
        this->left = nullptr;
        this->right = nullptr;
        this->height = 1;
    };

    /** Retorna el valor almacenado en el nodo. */
    T getData() const { return data; };

    /** Retorna puntero al hijo izquierdo (nullptr si no existe). */
    NodeTree<T>* getLeftNode() const { return left; };

    /** Retorna puntero al hijo derecho (nullptr si no existe). */
    NodeTree<T>* getRightNode() const { return right; };

    /** Retorna la altura del subárbol cuya raíz es este nodo. */
    int getHeight() const { return height; };

    /** Asigna el valor almacenado en el nodo. */
    void setData(T data) { this->data = data; };

    /** Asigna el hijo izquierdo. */
    void setLeftNode(NodeTree<T>* left) { this->left = left; };

    /** Asigna el hijo derecho. */
    void setRightNode(NodeTree<T>* right) { this->right = right; };

    /** Asigna la altura del subárbol. */
    void setHeight(int h) { this->height = h; };
};
