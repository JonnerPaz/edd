#include <string>

#include "./stack.hpp"

// Evaluar una expresión matemática y determinar si los paréntesis, corchetes y llaves están
// balanceados correctamente.

bool isBalanced(const std::string& expresion)
{
    Stack<char> stack;

    for (char c : expresion) {
        // Si abre, va a la pila
        if (c == '(' || c == '[' || c == '{') {
            stack.push(c);
        }

        // Si cierra, verificamos concordancia
        else if (c == ')' || c == ']' || c == '}') {
            if (stack.getSize() == 0) return false;  // Cerró algo sin abrir nada

            char top = stack.pop().value();
            if ((c == ')' && top != '(') || (c == ']' && top != '[') || (c == '}' && top != '{')) {
                return false;  // No coinciden los tipos
            }
        }
    }

    return stack.getSize() == 0;
}
