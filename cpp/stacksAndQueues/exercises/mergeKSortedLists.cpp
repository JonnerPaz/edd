// Merge K Sorted Lists
//
// Fusiona K listas enlazadas ordenadas en una sola lista ordenada.
//
// Enfoque (sin heap extra):
//   - Mantenemos un arreglo de punteros Node<T>* que indica la posición
//     actual dentro de cada lista
//   - En cada iteración, escaneamos las K cabezas y elegimos la menor
//   - Agregamos ese valor a la lista resultado y avanzamos esa lista
//   - Repetimos hasta consumir todas las listas
//
// Complejidad: O(n * k) tiempo, O(1) espacio extra (sin contar el resultado)
//
// Nota: En un examen real, podrías optimizar con un min-heap para O(n log k).

#include <iostream>

#include "../../listas/LinkedList/List.hpp"

template <typename T>
List<T> mergeKSortedLists(List<T>* lists[], int k)
{
    List<T> result;
    Node<T>* positions[k];

    for (int i = 0; i < k; i++) {
        positions[i] = lists[i]->getHead();
    }

    while (true) {
        int minIdx = -1;
        T minVal;

        for (int i = 0; i < k; i++) {
            if (positions[i] != nullptr) {
                if (minIdx == -1 || positions[i]->getData() < minVal) {
                    minIdx = i;
                    minVal = positions[i]->getData();
                }
            }
        }

        if (minIdx == -1) break;  // todas las listas vacías

        result.push(minVal);
        positions[minIdx] = positions[minIdx]->getNextNode();
    }

    return result;
}

// Demo: fusionar 3 listas ordenadas
int main()
{
    List<int> l1;
    l1.push(1);
    l1.push(4);
    l1.push(7);

    List<int> l2;
    l2.push(2);
    l2.push(5);
    l2.push(8);

    List<int> l3;
    l3.push(3);
    l3.push(6);
    l3.push(9);

    List<int>* lists[] = {&l1, &l2, &l3};
    int k = 3;

    List<int> merged = mergeKSortedLists(lists, k);

    std::cout << "Listas originales:\n";
    std::cout << "L1: 1 4 7\n";
    std::cout << "L2: 2 5 8\n";
    std::cout << "L3: 3 6 9\n\n";
    std::cout << "Merge: ";
    Node<int>* cur = merged.getHead();
    while (cur != nullptr) {
        std::cout << cur->getData() << " ";
        cur = cur->getNextNode();
    }
    std::cout << "\n(esperado: 1 2 3 4 5 6 7 8 9)\n";

    return 0;
}
