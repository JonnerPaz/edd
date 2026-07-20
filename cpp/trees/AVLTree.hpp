#pragma once

#include <algorithm>
#include <stdexcept>

#include "./NodeTree.hpp"

/**
 * Árbol Binario de Búsqueda Auto-balanceado (AVL).
 *
 * Mantiene la propiedad de BST y, además, para todo nodo:
 *   |balanceFactor| ≤ 1
 * donde balanceFactor = altura(subárbol izquierdo) - altura(subárbol derecho).
 *
 * Cuando un nodo se desbalancea, se aplican rotaciones para restaurar
 * el equilibrio. Altura de nullptr = 0, altura de hoja = 1.
 */
template <typename T>
class AVLTree
{
   private:
    NodeTree<T>* root;

    /**
     * Retorna la altura de un nodo (0 si es nullptr).
     * @note O(1) porque la altura se almacena en el nodo.
     */
    int height(NodeTree<T>* node) const { return node == nullptr ? 0 : node->getHeight(); }

    /**
     * Calcula el factor de equilibrio: altura(izquierdo) - altura(derecho).
     * @return Factor de equilibrio. |bf| > 1 indica desbalance.
     */
    int balanceFactor(NodeTree<T>* node) const
    {
        if (node == nullptr) return 0;
        return height(node->getLeftNode()) - height(node->getRightNode());
    }

    /**
     * Actualiza la altura del nodo basándose en la altura de sus hijos.
     * Altura = 1 + max(altura_hijo_izquierdo, altura_hijo_derecho).
     */
    void updateHeight(NodeTree<T>* node)
    {
        if (node == nullptr) return;
        node->setHeight(1 + std::max(height(node->getLeftNode()), height(node->getRightNode())));
    }

    /**
     * Rotación simple a la derecha (caso Left-Left).
     * @param y Nodo desbalanceado (bf > 1).
     * @return x (nueva raíz del subárbol).
     */
    NodeTree<T>* rotateRight(NodeTree<T>* y)
    {
        NodeTree<T>* x = y->getLeftNode();
        NodeTree<T>* B = x->getRightNode();

        x->setRightNode(y);
        y->setLeftNode(B);

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    /**
     * Rotación simple a la izquierda (caso Right-Right).
     * @param x Nodo desbalanceado (bf < -1).
     * @return y (nueva raíz del subárbol).
     */
    NodeTree<T>* rotateLeft(NodeTree<T>* x)
    {
        NodeTree<T>* y = x->getRightNode();
        NodeTree<T>* B = y->getLeftNode();

        y->setLeftNode(x);
        x->setRightNode(B);

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    /**
     * Rebalancea el nodo si su factor de equilibrio lo requiere.
     *
     * Casos:
     *   Left-Left  (bf > 1 y bf(hijo izq) ≥ 0)  → rotateRight
     *   Left-Right (bf > 1 y bf(hijo izq) < 0)  → rotateLeft + rotateRight
     *   Right-Right(bf < -1 y bf(hijo der) ≤ 0) → rotateLeft
     *   Right-Left (bf < -1 y bf(hijo der) > 0) → rotateRight + rotateLeft
     *
     * @param node Nodo a verificar/rebalancear.
     * @return El nodo (o nueva raíz del subárbol si rotó).
     */
    NodeTree<T>* rebalance(NodeTree<T>* node)
    {
        if (node == nullptr) return nullptr;

        int bf = balanceFactor(node);

        if (bf > 1) {
            if (balanceFactor(node->getLeftNode()) < 0)
                node->setLeftNode(rotateLeft(node->getLeftNode()));
            return rotateRight(node);
        }

        if (bf < -1) {
            if (balanceFactor(node->getRightNode()) > 0)
                node->setRightNode(rotateRight(node->getRightNode()));
            return rotateLeft(node);
        }

        return node;
    }

    /**
     * Inserta un valor y rebalancea el árbol si es necesario.
     * @param node Raíz del subárbol actual.
     * @param data  Valor a insertar.
     * @return La nueva raíz del subárbol (puede cambiar por rotaciones).
     * @note Complejidad: O(log n).
     */
    NodeTree<T>* insert(NodeTree<T>* node, T data)
    {
        if (node == nullptr) return new NodeTree<T>(data);

        if (data < node->getData())
            node->setLeftNode(insert(node->getLeftNode(), data));
        else if (data > node->getData())
            node->setRightNode(insert(node->getRightNode(), data));
        else
            return node;

        updateHeight(node);
        return rebalance(node);
    }

    /**
     * Encuentra el nodo con el valor mínimo en el subárbol (NO DESDE LA ROOT)
     */
    NodeTree<T>* findMin(NodeTree<T>* node) const
    {
        if (node == nullptr) return nullptr;
        while (node->getLeftNode() != nullptr) node = node->getLeftNode();
        return node;
    }

    /**
     * Encuentra el nodo con el valor máximo en el subárbol. (NO DESDE LA ROOT)
     */
    NodeTree<T>* findMax(NodeTree<T>* node) const
    {
        if (node == nullptr) return nullptr;
        while (node->getRightNode() != nullptr) node = node->getRightNode();
        return node;
    }

    /**
     * Elimina un valor y rebalancea el árbol si es necesario.
     * @param node Raíz del subárbol actual.
     * @param data  Valor a eliminar.
     * @return La nueva raíz del subárbol.
     * @note Complejidad: O(log n).
     */
    NodeTree<T>* remove(NodeTree<T>* node, T data)
    {
        if (node == nullptr) return nullptr;

        if (data < node->getData()) {
            node->setLeftNode(remove(node->getLeftNode(), data));
        } else if (data > node->getData()) {
            node->setRightNode(remove(node->getRightNode(), data));
        } else {
            if (node->getLeftNode() == nullptr && node->getRightNode() == nullptr) {
                delete node;
                return nullptr;
            }

            if (node->getLeftNode() == nullptr) {
                NodeTree<T>* temp = node->getRightNode();
                delete node;
                return temp;
            }

            if (node->getRightNode() == nullptr) {
                NodeTree<T>* temp = node->getLeftNode();
                delete node;
                return temp;
            }

            NodeTree<T>* pred = findMax(node->getLeftNode());
            node->setData(pred->getData());
            node->setLeftNode(remove(node->getLeftNode(), pred->getData()));
        }

        updateHeight(node);
        return rebalance(node);
    }

    /**
     * Recorrido inorden: izquierdo → raíz → derecho.
     * Genera los valores en orden ascendente.
     */
    template <typename Visitor>
    void inorder(NodeTree<T>* node, Visitor visit) const
    {
        if (node == nullptr) return;
        inorder(node->getLeftNode(), visit);
        visit(node->getData());
        inorder(node->getRightNode(), visit);
    }

    /**
     * Recorrido preorden: raíz → izquierdo → derecho.
     */
    template <typename Visitor>
    void preorder(NodeTree<T>* node, Visitor visit) const
    {
        if (node == nullptr) return;
        visit(node->getData());
        preorder(node->getLeftNode(), visit);
        preorder(node->getRightNode(), visit);
    }

    /**
     * Recorrido postorden: izquierdo → derecho → raíz.
     */
    template <typename Visitor>
    void postorder(NodeTree<T>* node, Visitor visit) const
    {
        if (node == nullptr) return;
        postorder(node->getLeftNode(), visit);
        postorder(node->getRightNode(), visit);
        visit(node->getData());
    }

    /**
     * Cuenta la cantidad de nodos en el subárbol.
     */
    int countNodes(NodeTree<T>* node) const
    {
        if (node == nullptr) return 0;
        return 1 + countNodes(node->getLeftNode()) + countNodes(node->getRightNode());
    }

    /**
     * Libera la memoria de todos los nodos del subárbol.
     */
    void destroy(NodeTree<T>* node)
    {
        if (node == nullptr) return;
        destroy(node->getLeftNode());
        destroy(node->getRightNode());
        delete node;
    }

    /**
     * Clona recursivamente un subárbol.
     */
    NodeTree<T>* copy(NodeTree<T>* node) const
    {
        if (node == nullptr) return nullptr;
        NodeTree<T>* newNode = new NodeTree<T>(node->getData());
        newNode->setLeftNode(copy(node->getLeftNode()));
        newNode->setRightNode(copy(node->getRightNode()));
        newNode->setHeight(node->getHeight());
        return newNode;
    }

    /**
     * Verifica recursivamente si el subárbol está balanceado.
     */
    bool isBalanced(NodeTree<T>* node) const
    {
        if (node == nullptr) return true;
        int bf = balanceFactor(node);
        if (bf < -1 || bf > 1) return false;
        return isBalanced(node->getLeftNode()) && isBalanced(node->getRightNode());
    }

   public:
    AVLTree() : root(nullptr) {}

    AVLTree(const AVLTree& other) : root(copy(other.root)) {}

    ~AVLTree() { destroy(root); }

    /**
     * Inserta un valor en el AVL y rebalancea automáticamente.
     * @param data Valor a insertar.
     * @note Si el valor ya existe, no hace nada.
     *       Complejidad: O(log n).
     */
    void insert(T data) { root = insert(root, data); }

    /**
     * Elimina un valor del AVL y rebalancea automáticamente.
     * @param data Valor a eliminar.
     * @note Si el valor no existe, no hace nada.
     *       Complejidad: O(log n).
     */
    void remove(T data) { root = remove(root, data); }

    /**
     * Busca un valor en el AVL.
     * @param data Valor a buscar.
     * @return true si el valor existe, false en caso contrario.
     * @note Complejidad: O(log n).
     */
    bool search(T data) const
    {
        NodeTree<T>* current = root;
        while (current != nullptr) {
            if (data == current->getData()) return true;
            if (data < current->getData())
                current = current->getLeftNode();
            else
                current = current->getRightNode();
        }
        return false;
    }

    /**
     * Encuentra el valor mínimo del árbol.
     * @return El valor mínimo.
     * @throws std::runtime_error si el árbol está vacío.
     */
    T findMin() const
    {
        if (root == nullptr) throw std::runtime_error("findMin: tree is empty");
        return findMin(root)->getData();
    }

    /**
     * Encuentra el valor máximo del árbol.
     * @return El valor máximo.
     * @throws std::runtime_error si el árbol está vacío.
     */
    T findMax() const
    {
        if (root == nullptr) throw std::runtime_error("findMax: tree is empty");
        return findMax(root)->getData();
    }

    /**
     * Retorna la altura del árbol (número de niveles).
     * @note Árbol vacío → altura 0. Solo raíz → altura 1. O(1).
     */
    int height() const { return height(root); }

    /**
     * Retorna la cantidad total de nodos en el árbol.
     */
    int countNodes() const { return countNodes(root); }

    /**
     * Recorrido inorden: izquierdo → raíz → derecho.
     * @param visit Función llamada con cada valor en orden ascendente.
     */
    template <typename Visitor>
    void inorder(Visitor visit) const
    {
        inorder(root, visit);
    }

    /**
     * Recorrido preorden: raíz → izquierdo → derecho.
     * @param visit Función llamada con cada valor.
     */
    template <typename Visitor>
    void preorder(Visitor visit) const
    {
        preorder(root, visit);
    }

    /**
     * Recorrido postorden: izquierdo → derecho → raíz.
     * @param visit Función llamada con cada valor.
     */
    template <typename Visitor>
    void postorder(Visitor visit) const
    {
        postorder(root, visit);
    }

    /**
     * Verifica si todo el árbol cumple la condición de balanceo AVL
     * (|factor de equilibrio| ≤ 1 en cada nodo).
     * @return true si el árbol está balanceado.
     */
    bool isBalanced() const { return isBalanced(root); }

    /** Retorna puntero a la raíz del árbol. */
    NodeTree<T>* getRoot() const { return root; }

    /**
     * Elimina todos los nodos del árbol y lo deja vacío.
     */
    void clear()
    {
        destroy(root);
        root = nullptr;
    }
};
