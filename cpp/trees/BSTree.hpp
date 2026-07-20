#pragma once

#include <algorithm>
#include <limits>
#include <stdexcept>

#include "./NodeTree.hpp"

/**
 * Árbol Binario de Búsqueda (BST).
 *
 * Propiedad fundamental: para todo nodo N, todos los valores en el
 * subárbol izquierdo de N son menores que N->data, y todos los valores
 * en el subárbol derecho son mayores.
 *
 * No permite valores duplicados.
 */
template <typename T>
class BSTree
{
   private:
    NodeTree<T>* root;

    /**
     * Inserta un valor en el subárbol cuya raíz es @p node.
     * @param node Raíz del subárbol actual.
     * @param data  Valor a insertar.
     * @return El nodo raíz del subárbol después de la inserción.
     * @note Complejidad: O(log n) promedio, O(n) peor caso.
     */
    NodeTree<T>* insert(NodeTree<T>* node, T data)
    {
        if (node == nullptr) return new NodeTree<T>(data);

        if (data < node->getData())
            node->setLeftNode(insert(node->getLeftNode(), data));
        else if (data > node->getData())
            node->setRightNode(insert(node->getRightNode(), data));

        return node;
    }

    /**
     * Encuentra el nodo con el valor mínimo en el subárbol.
     * @param node Raíz del subárbol.
     * @return Nodo con el valor mínimo, o nullptr si el subárbol está vacío.
     */
    NodeTree<T>* findMin(NodeTree<T>* node) const
    {
        if (node == nullptr) return nullptr;
        while (node->getLeftNode() != nullptr) node = node->getLeftNode();
        return node;
    }

    /**
     * Encuentra el nodo con el valor máximo en el subárbol.
     * @param node Raíz del subárbol.
     * @return Nodo con el valor máximo, o nullptr si el subárbol está vacío.
     */
    NodeTree<T>* findMax(NodeTree<T>* node) const
    {
        if (node == nullptr) return nullptr;
        while (node->getRightNode() != nullptr) node = node->getRightNode();
        return node;
    }

    /**
     * Elimina un valor del subárbol cuya raíz es @p node.
     * Maneja los 3 casos: hoja, un hijo, dos hijos (usa predecesor inorden).
     * @param node Raíz del subárbol actual.
     * @param data  Valor a eliminar.
     * @return El nodo raíz del subárbol después de la eliminación.
     * @note Complejidad: O(log n) promedio, O(n) peor caso.
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

        return node;
    }

    /**
     * Recorrido inorden: izquierdo → raíz → derecho.
     * Genera los valores en orden ascendente para un BST.
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
     * Calcula la altura del subárbol (número de niveles).
     * Altura de nullptr = 0, altura de una hoja = 1.
     */
    int height(NodeTree<T>* node) const
    {
        if (node == nullptr) return 0;
        return 1 + std::max(height(node->getLeftNode()), height(node->getRightNode()));
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
     * Cuenta la cantidad de hojas (nodos sin hijos) en el subárbol.
     */
    int countLeaves(NodeTree<T>* node) const
    {
        if (node == nullptr) return 0;
        if (node->getLeftNode() == nullptr && node->getRightNode() == nullptr) return 1;
        return countLeaves(node->getLeftNode()) + countLeaves(node->getRightNode());
    }

    /**
     * Verifica si el subárbol cumple la propiedad de BST.
     * @param node Raíz del subárbol.
     * @param min  Cota inferior (excluyente) que deben superar los valores.
     * @param max  Cota superior (excluyente) que deben no superar los valores.
     */
    bool isValidBST(NodeTree<T>* node, T min, T max) const
    {
        if (node == nullptr) return true;
        if (node->getData() <= min || node->getData() >= max) return false;
        return isValidBST(node->getLeftNode(), min, node->getData()) &&
               isValidBST(node->getRightNode(), node->getData(), max);
    }

    /**
     * Elimina todos los nodos del subárbol (libera memoria).
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
     * @param node Raíz del subárbol a copiar.
     * @return Nueva raíz del subárbol copiado.
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

   public:
    BSTree() : root(nullptr) {}

    BSTree(const BSTree& other) : root(copy(other.root)) {}

    ~BSTree() { destroy(root); }

    /**
     * Inserta un valor en el BST.
     * @param data Valor a insertar.
     * @note Si el valor ya existe, no hace nada.
     */
    void insert(T data) { root = insert(root, data); }

    /**
     * Elimina un valor del BST.
     * @param data Valor a eliminar.
     * @note Si el valor no existe, no hace nada.
     */
    void remove(T data) { root = remove(root, data); }

    /**
     * Busca un valor en el BST.
     * @param data Valor a buscar.
     * @return true si el valor existe, false en caso contrario.
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
     * @note Árbol vacío → altura 0. Solo raíz → altura 1.
     */
    int height() const { return height(root); }

    /**
     * Retorna la cantidad total de nodos en el árbol.
     */
    int countNodes() const { return countNodes(root); }

    /**
     * Retorna la cantidad de hojas del árbol.
     */
    int countLeaves() const { return countLeaves(root); }

    /**
     * Verifica si el árbol cumple la propiedad de BST.
     * @return true si es un BST válido.
     */
    bool isValidBST() const
    {
        return isValidBST(root, std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
    }

    /**
     * Recorrido inorden: izquierdo → raíz → derecho.
     * @param visit Función llamada con cada valor en orden.
     * @note En un BST genera los valores ordenados ascendentemente.
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
     * Encuentra el sucesor inorden de un valor (el siguiente valor mayor).
     * @param data Valor de referencia.
     * @return El sucesor inorden.
     * @throws std::runtime_error si no hay sucesor (último elemento).
     */
    T successor(T data) const
    {
        NodeTree<T>* current = root;
        NodeTree<T>* succ = nullptr;

        while (current != nullptr) {
            if (data < current->getData()) {
                succ = current;
                current = current->getLeftNode();
            } else if (data > current->getData()) {
                current = current->getRightNode();
            } else {
                if (current->getRightNode() != nullptr)
                    return findMin(current->getRightNode())->getData();
                break;
            }
        }

        if (succ != nullptr) return succ->getData();
        throw std::runtime_error("successor: no successor found");
    }

    /**
     * Encuentra el predecesor inorden de un valor (el anterior valor menor).
     * @param data Valor de referencia.
     * @return El predecesor inorden.
     * @throws std::runtime_error si no hay predecesor (primer elemento).
     */
    T predecessor(T data) const
    {
        NodeTree<T>* current = root;
        NodeTree<T>* pred = nullptr;

        while (current != nullptr) {
            if (data > current->getData()) {
                pred = current;
                current = current->getRightNode();
            } else if (data < current->getData()) {
                current = current->getLeftNode();
            } else {
                if (current->getLeftNode() != nullptr)
                    return findMax(current->getLeftNode())->getData();
                break;
            }
        }

        if (pred != nullptr) return pred->getData();
        throw std::runtime_error("predecessor: no predecessor found");
    }

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
