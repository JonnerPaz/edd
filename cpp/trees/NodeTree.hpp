#pragma once

/**
 * @brief - Clase que representa un nodo de una lista simple
 */
template <typename T>
class NodeTree
{
   private:
    T data;
    NodeTree<T>* left;
    NodeTree<T>* right;

   public:
    NodeTree(T data) : data(data)
    {
        this->left = nullptr;
        this->right = nullptr;
    };

    T getData() { return data; };

    NodeTree<T>* getLeftNode() { return left == nullptr ? nullptr : left; };

    NodeTree<T>* getRightNode() { return right == nullptr ? nullptr : right; };

    void setData(T data) { this->data = data; };

    void setLeftNode(NodeTree<T>* left) { this->left = left; };

    void setRightNode(NodeTree<T>* right) { this->right = right; };
};
