// MinStack: stack con getMin() en O(1)
//
// Mantiene dos stacks internos:
//   - data: almacena todos los elementos normalmente
//   - mins: guarda el mínimo histórico en cada nivel
//
// En cada push(), si el nuevo valor es <= al mínimo actual,
// también lo guardamos en _mins. Así _mins.top() siempre
// es el mínimo de toda la pila en ese instante.
//
// En pop(), si sacamos el mismo valor que está en _mins.top(),
// también hacemos pop de _mins para restaurar el mínimo anterior.

#include <iostream>
#include <optional>

#include "../Stacks/stack.hpp"

template <typename T>
class MinStack
{
   private:
    Stack<T> data;
    Stack<T> mins;

   public:
    MinStack() = default;

    void push(T val)
    {
        data.push(val);
        if (mins.getSize() == 0 || val <= mins.top().value()) {
            mins.push(val);
        }
    }

    std::optional<T> pop()
    {
        if (data.getSize() == 0) return std::nullopt;

        T val = data.pop().value();
        if (val == mins.top().value()) {
            mins.pop();
        }

        return val;
    }

    std::optional<T> top() const { return data.top(); }

    std::optional<T> getMin() const { return mins.top(); }

    int getSize() const { return data.getSize(); }

    bool isEmpty() const { return data.getSize() == 0; }
};

// Demo
int main()
{
    MinStack<int> ms;
    ms.push(5);
    ms.push(3);
    ms.push(7);
    ms.push(2);
    ms.push(4);

    std::cout << "Min actual: " << ms.getMin().value() << " (esperado: 2)\n";
    ms.pop();  // saca 4
    ms.pop();  // saca 2
    std::cout << "Min tras sacar 2: " << ms.getMin().value() << " (esperado: 3)\n";
    ms.pop();  // saca 7
    std::cout << "Min tras sacar 7: " << ms.getMin().value() << " (esperado: 3)\n";
    ms.pop();  // saca 3
    std::cout << "Min tras sacar 3: " << ms.getMin().value() << " (esperado: 5)\n";
    return 0;
}
