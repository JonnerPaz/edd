#include <cctype>
#include <sstream>
#include <string>

#include "../Stacks/stack.hpp"

// Evaluar una expresión matemática en notación postfija (postfix) y devolver su resultado.
// Algo como lo que hacíamos en la clase de teoría de computación.

int evaluatePostfix(const std::string& expresion)
{
    Stack<int> pila;
    std::stringstream ss(expresion);
    std::string token;

    while (ss >> token) {
        // Si es un número (puede ser de más de un dígito)
        if (isdigit(token[0])) {
            pila.push(std::stoi(token));
        }

        // Si es un operador
        else if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (pila.getSize() < 2) return 0;  // Error: faltan operandos

            int b = pila.pop().value();
            int a = pila.pop().value();

            if (token == "+")
                pila.push(a + b);
            else if (token == "-")
                pila.push(a - b);
            else if (token == "*")
                pila.push(a * b);
            else if (token == "/")
                pila.push(a / b);  // Asumiendo b != 0
        }
    }

    return pila.pop().value_or(0);
}
