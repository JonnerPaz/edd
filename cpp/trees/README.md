# Árboles — Guía de Estudio

## 1. ¿Qué es un árbol?

Un **árbol** es una estructura de datos jerárquica (no lineal) compuesta por **nodos** conectados por **aristas** (edges). A diferencia de las listas enlazadas (lineales), cada nodo puede tener cero o más nodos **hijos**.

```
        (raíz)
          |
     +----+----+
     |         |
  (hijo)   (hijo)
     |         |
  +--+--+   +--+--+
  |     |   |     |
 ...   ... ...   ...
```

## 2. Terminología

| Término | Definición |
|---|---|
| **Raíz (root)** | Nodo superior del árbol (sin padre). En un BST, `this->root` apunta a él. |
| **Hoja (leaf)** | Nodo sin hijos (left == nullptr && right == nullptr). |
| **Nodo interno** | Nodo con al menos un hijo. |
| **Padre (parent)** | Nodo que apunta directamente a otro. |
| **Hijo (child)** | Nodo al que apunta un padre. |
| **Hermano (sibling)** | Nodos que comparten el mismo padre. |
| **Ancestro (ancestor)** | Cualquier nodo en el camino de la raíz a un nodo. |
| **Descendiente (descendant)** | Cualquier nodo en el subárbol de un nodo. |
| **Altura (height)** | Número de aristas en el camino más largo desde el nodo hasta una hoja. Un nodo hoja tiene altura 0. La **altura del árbol** es la altura de la raíz. |
| **Nivel (level)** | Raíz está en nivel 0 (o 1, según la definición). Sus hijos en nivel 1, etc. |
| **Profundidad (depth)** | Número de aristas desde la raíz hasta el nodo. |
| **Subárbol (subtree)** | Árbol formado por un nodo y todos sus descendientes. |
| **Factor de equilibrio** | `altura(subárbol_izquierdo) - altura(subárbol_derecho)`. Usado en AVL. |

## 3. Árbol Binario de Búsqueda (BST)

Cada nodo tiene **como máximo 2 hijos**: izquierdo y derecho.

**Propiedad fundamental del BST:**
- Izquierdo < Raíz < Derecho (para todos los nodos)

Es decir: todo nodo en el subárbol izquierdo es **menor** que la raíz, y todo nodo en el subárbol derecho es **mayor**.

```
        5            ← raíz
      /   \
     3     7         ← nivel 1
    / \   / \
   2   4 6   8       ← nivel 2 (hojas)
```

En tu código (`NodeTree.hpp`), cada nodo tiene: `data`, `left`, `right`.

## 4. Inserción en BST

### Algoritmo general:
1. Si el árbol está vacío, el nuevo nodo es la raíz.
2. Si `data < nodo_actual`, ve al subárbol izquierdo.
3. Si `data > nodo_actual`, ve al subárbol derecho.
4. Repite hasta encontrar un `nullptr` (lugar de inserción).
5. Si el dato ya existe, no lo insertes (en un BST sin duplicados).

### Tus 3 implementaciones:

**`insert(T data)` — Iterativa clásica:**
`tree.hpp:17-49` — Busca el padre del nuevo nodo con un `while`, luego lo inserta como hijo izquierdo o derecho.
```cpp
// Encuentra el padre
while (current != nullptr && current->getData() != data) {
    parent = current;
    if (current->getData() < data)
        current = current->getRightNode();
    else
        current = current->getLeftNode();
}
// Inserta
if (parent->getData() < data)
    parent->setRightNode(new NodeTree<T>(data));
else
    parent->setLeftNode(new NodeTree<T>(data));
```

**`insertAlt(T data)` — Iterativa directa:**
`tree.hpp:51-85` — Similar pero sin variable `parent`. Cuando encuentra un `nullptr`, inserta ahí directamente.
```cpp
if (data < curNode->getData()) {
    if (!curNode->getLeftNode()) {
        curNode->setLeftNode(newNode);
        return newNode;
    }
    curNode = curNode->getLeftNode();
} // ... análogo para el lado derecho
```

**`insertRecursive(NodeTree<T>*& node, T data)` — Recursiva:**
`tree.hpp:87-100` — Caso base: si `node == nullptr`, crea y retorna el nuevo nodo. Luego propaga la asignación recursivamente.

### Complejidad: O(log n) promedio, O(n) peor caso (árbol degenerado).

## 5. Eliminación en BST

3 casos:

### Caso 1: Hoja (sin hijos)
Simplemente se elimina el nodo y su padre apunta a `nullptr`.

```
    5              5
   / \      →    / \
  3   7         3   null
```

### Caso 2: Un hijo
El nodo se reemplaza por su único hijo.

```
    5              5
   / \      →    / \
  3   7         4   7
   \
    4
```

### Caso 3: Dos hijos
Se busca el **sucesor inorden** (el más pequeño del subárbol derecho) o el **predecesor inorden** (el más grande del subárbol izquierdo), se copia su valor al nodo a eliminar, y luego se elimina ese sucesor/predecesor.

```
      5                 6
    /   \             /   \
   3     7     →     3     7
  / \   / \         / \   / \
 2   4 6   8       2   4 8   null

(sucesor inorden de 5 es 6 → se copia 6 a la raíz, se elimina el 6 original)
```

## 6. Recorridos (Traversals)

| Recorrido | Orden | Ejemplo (árbol de arriba) |
|---|---|---|
| **Preorden** | Raíz → Izquierdo → Derecho | `5 3 2 4 7 6 8` |
| **Inorden** | Izquierdo → Raíz → Derecho | `2 3 4 5 6 7 8` (da orden ascendente en BST) |
| **Postorden** | Izquierdo → Derecho → Raíz | `2 4 3 6 8 7 5` |

En tu `main.cpp` tienes el **inorden recursivo** y **inorden iterativo** (usando `stack`).

**Inorden iterativo** (`main.cpp:19-35`):
```cpp
stack<NodeTree<int>*> st;
NodeTree<int>* cur = node;
while (cur != nullptr || !st.empty()) {
    while (cur != nullptr) {   // ir al extremo izquierdo
        st.push(cur);
        cur = cur->getLeftNode();
    }
    cur = st.top();
    st.pop();
    cout << cur->getData() << " ";
    cur = cur->getRightNode();
}
```

## 7. Árboles AVL (Balanceados)

Un **AVL** es un BST que se auto-balancea. Para cada nodo:

```
|balance_factor| ≤ 1   donde balance_factor = altura(izquierdo) - altura(derecho)
```

### Rotaciones (restauran el equilibrio):

| Desbalance | Rotación |
|---|---|
| Izquierda-Izquierda (left-left) | Rotación simple a la derecha |
| Derecha-Derecha (right-right) | Rotación simple a la izquierda |
| Izquierda-Derecha (left-right) | Rotación doble: izquierda → derecha |
| Derecha-Izquierda (right-left) | Rotación doble: derecha → izquierda |

### Ejemplo: Rotación simple a la derecha (Left-Left)

```
    10                   5
   /  \                /   \
  5    15     →       3    10
 / \                 /    /  \
3   7               2    7   15
/
2
```

## 8. Complejidades

| Operación | BST promedio | BST peor caso | AVL/RB |
|---|---|---|---|
| Insertar | O(log n) | O(n) | O(log n) |
| Eliminar | O(log n) | O(n) | O(log n) |
| Buscar | O(log n) | O(n) | O(log n) |
| Recorrer (inorden) | O(n) | O(n) | O(n) |

El **peor caso** (árbol degenerado) ocurre cuando los datos se insertan ordenados, formando efectivamente una lista enlazada.

## 9. Tips para el examen

- Memoria visual: dibuja los árboles en el examen.
- Para inserción y eliminación, traza paso a paso con lápiz.
- En AVL, después de insertar/eliminar, **revisa el balance de todos los ancestros** del nodo modificado, no solo del nodo mismo.
- El **factor de equilibrio** se actualiza después de cada inserción/eliminación.
- Practica los 4 casos de rotación AVL hasta que salgan automáticos.
- Inorden en BST siempre da los elementos **ordenados ascendentemente**.
