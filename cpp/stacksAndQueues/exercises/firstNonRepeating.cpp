// First Non-Repeating Character in a Stream
//
// Dado un flujo de caracteres, para cada carácter recibido se debe
// indicar cuál es el primer carácter que no se ha repetido hasta
// ese momento. Si todos se han repetido, se muestra '#'.
//
// Algoritmo:
//   1. int freq[128] lleva la cuenta de cuántas veces aparece cada char
//   2. Queue<char> order guarda el orden de llegada
//   3. Por cada carácter c:
//      a. Incrementar freq[c]
//      b. Encolar c en order
//      c. Mientras order no esté vacío y el frente tenga freq > 1,
//         descartarlo (pop)
//      d. Si order no está vacío, mostrar el frente; si no, mostrar '#'

#include <iostream>
#include <string>

#include "../queues/Queue.hpp"

void firstNonRepeating(const std::string& stream)
{
    int freq[128] = {0};
    Queue<char> order;

    for (char c : stream) {
        freq[c]++;
        order.push(c);

        // Descartar del frente los que ya se repiten
        while (order.getSize() > 0 && freq[order.front().value()] > 1) {
            order.pop();
        }

        if (order.getSize() > 0) {
            std::cout << c << " -> " << order.front().value() << "\n";
        } else {
            std::cout << c << " -> #\n";
        }
    }
}

// Demo
int main()
{
    std::cout << "Stream: a a b c a b c\n";
    firstNonRepeating("aabcabc");
    // Esperado:
    // a -> a
    // a -> #
    // b -> b
    // c -> b
    // a -> b
    // b -> c
    // c -> #

    std::cout << "\nStream: a b c a b c\n";
    firstNonRepeating("abcabc");
    // Esperado:
    // a -> a
    // b -> a
    // c -> a
    // a -> #
    // b -> #
    // c -> #

    return 0;
}
