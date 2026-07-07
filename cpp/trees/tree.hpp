#pragma once
#include "./NodeTree.hpp"

template <typename T>
class BSTree
{
   private:
    NodeTree<T>* root;

   public:
    BSTree(NodeTree<T>* root) { this->root = root; }

    BSTree() { this->root = nullptr; }

    NodeTree<T>* getRoot() { return this->root; }

    void insert(T data)
    {
        if (!this->root) {
            this->root = new NodeTree<T>(data);
            return;
        }

        NodeTree<T>* parent = nullptr;
        NodeTree<T>* current = this->root;

        // Find the parent of the new node
        // If the parent is nullptr, the new node is the root
        while (current != nullptr && current->getData() != data) {
            parent = current;
            if (current->getData() < data) {
                current = current->getRightNode();
            } else {
                current = current->getLeftNode();
            }
        }

        // If the new node is already in the tree, do nothing
        if (current != nullptr) {
            return;
        }

        // When parent is nullptr, the new node is the root
        if (parent->getData() < data) {
            parent->setRightNode(new NodeTree<T>(data));
        } else {
            parent->setLeftNode(new NodeTree<T>(data));
        }
    }

    NodeTree<T>* insertAlt(T data)
    {
        auto newNode = new NodeTree<T>(data);

        if (!this->root) {
            this->root = newNode;
            return this->root;
        }

        auto curNode = this->root;
        while (true) {
            if (data == curNode->getData()) {
                delete newNode;
                return curNode;
            }

            if (data < curNode->getData()) {
                // insert if left is null, else go left
                if (!curNode->getLeftNode()) {
                    curNode->setLeftNode(newNode);
                    return newNode;
                }

                curNode = curNode->getLeftNode();
            } else {
                // insert if right is null, else go right
                if (!curNode->getRightNode()) {
                    curNode->setRightNode(newNode);
                    return newNode;
                }

                curNode = curNode->getRightNode();
            }
        }
    }

    NodeTree<T>* insertRecursive(NodeTree<T>*& node, T data)
    {
        if (node == nullptr) {
            return new NodeTree<T>(data);
        }

        if (node->getData() < data) {
            insertRecursive(node->getRightNode(), data);
        } else {
            insertRecursive(node->getLeftNode(), data);
        }

        return node;
    }
};
