#include "ejer1.hpp"

#include "AVLTree.hpp"
#include "List.hpp"
#include "Queue.hpp"

MaxToMinTree::MaxToMinTree() : raiz(nullptr) {}

MaxToMinTree::~MaxToMinTree()
{
    cleanTree(raiz);
}

// inserta nuevamente en un arbol, pero ya con lo que se pide en el ejercicio
NodeTree<int>* MaxToMinTree::buildTree(NodeList* list)
{
    if (list == nullptr) return nullptr;

    NodeTree<int>* root = new NodeTree<int>(list->valor);
    list = list->siguiente;

    Queue<NodeTree<int>*> queue;
    queue.push(root);

    while (list != nullptr) {
        auto opt = queue.front();
        if (!opt.has_value()) break;
        NodeTree<int>* parent = opt.value();
        queue.pop();

        if (list != nullptr) {
            NodeTree<int>* left = new NodeTree<int>(list->valor);
            parent->setLeftNode(left);
            queue.push(left);
            list = list->siguiente;
        }

        if (list != nullptr) {
            NodeTree<int>* right = new NodeTree<int>(list->valor);
            parent->setRightNode(right);
            queue.push(right);
            list = list->siguiente;
        }
    }

    return root;
}

void MaxToMinTree::showTree(NodeTree<int>* node) const
{
    if (node == nullptr) return;

    Queue<NodeTree<int>*> queue;
    Queue<int> levels;
    queue.push(node);
    levels.push(0);

    // saca los valores del arbol y los muestra en pantalla
    while (queue.getSize() > 0) {
        std::optional<NodeTree<int>*> optNode = queue.front();
        queue.pop();
        std::optional<int> optLevel = levels.front();
        levels.pop();

        if (!optNode.has_value() || !optLevel.has_value()) break;

        NodeTree<int>* current = optNode.value();
        int level = optLevel.value();

        std::cout << "Nivel " << level << ": " << current->getData() << "\n";

        if (current->getLeftNode() != nullptr) {
            queue.push(current->getLeftNode());
            levels.push(level + 1);
        }
        if (current->getRightNode() != nullptr) {
            queue.push(current->getRightNode());
            levels.push(level + 1);
        }
    }
}

void MaxToMinTree::cleanTree(NodeTree<int>* nodo)
{
    if (nodo == nullptr) return;
    cleanTree(nodo->getLeftNode());
    cleanTree(nodo->getRightNode());
    delete nodo;
}

void MaxToMinTree::inorderToList(NodeTree<int>* nodo, List& lista)
{
    if (nodo == nullptr) return;
    inorderToList(nodo->getLeftNode(), lista);
    lista.add(nodo->getData());
    inorderToList(nodo->getRightNode(), lista);
}

void MaxToMinTree::exec()
{
    AVLTree<int> avl;

    std::cout << "Ingrese numeros (0 para terminar): ";
    int num;
    while (std::cin >> num && num != 0) avl.insert(num);

    if (avl.getRoot() == nullptr) {
        std::cout << "No se ingresaron numeros.\n";
        return;
    }

    List lista;
    // sacarlos inorden me los da más ordenados (--- middle ++++)
    inorderToList(avl.getRoot(), lista);

    raiz = buildTree(lista.getHead());

    std::cout << "\n--- Árbol (menores arriba, mayores abajo) ---\n";
    showTree(raiz);
}
