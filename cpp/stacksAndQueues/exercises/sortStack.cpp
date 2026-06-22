// sortStack: ordenar un stack usando solo otro stack auxiliar
//
// Algoritmo (tipo insertion sort con stacks):
//   1. Creamos un stack auxiliar temp vacío.
//   2. Mientras el stack original s no esté vacío:
//      a. Sacamos el tope de s → current
//      b. Mientras temp no esté vacío Y su tope > current:
//         - Movemos el tope de temp de vuelta a s
//      c. Pusheamos current a temp
//   3. Al final, temp tiene los elementos ordenados ascendentemente
//      (el más pequeño abajo, el más grande arriba).
//   4. Pasamos todo de temp de vuelta a s para que quede con el orden natural.
//
// Complejidad: O(n^2) en tiempo, O(n) en espacio extra.

#include <iostream>
#include <optional>

#include "../Stacks/stack.hpp"

template <typename T>
void sortStack(Stack<T>& s)
{
    Stack<T> temp;

    while (s.getSize() > 0) {
        T current = s.pop().value();

        // Los elementos de temp que sean mayores que current
        // los devolvemos a s para reordenarlos después
        while (temp.getSize() > 0 && temp.top().value() > current) {
            s.push(temp.pop().value());
        }

        temp.push(current);
    }

    // temp tiene los elementos ordenados (menor abajo, mayor arriba)
    // Pasamos todo de vuelta a s
    while (temp.getSize() > 0) {
        s.push(temp.pop().value());
    }
}

// Demo
int main()
{
    Stack<int> s;
    s.push(34);
    s.push(3);
    s.push(31);
    s.push(98);
    s.push(92);
    s.push(23);

    std::cout << "Antes de ordenar:\n";
    s.loopStack();

    sortStack(s);

    std::cout << "Después de ordenar (ascendente):\n";
    s.loopStack();

    return 0;
}
