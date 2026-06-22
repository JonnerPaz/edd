// QueueWithTwoStacks: cola implementada con dos stacks
//
// Usa dos stacks internos:
//   - in:  para encolar (push aquí, O(1))
//   - out: para desencolar (pop de aquí, O(1) amortizado)
//
// En dequeue():
//   Si out está vacío, volcamos todo in → out (invierte el orden).
//   Luego hacemos pop de out.
//
// Esto da O(1) amortizado por operación porque cada elemento
// se mueve de in a out exactamente una vez a lo largo de su vida.

#include <iostream>
#include <optional>

#include "../Stacks/stack.hpp"

template <typename T>
class QueueWithTwoStacks
{
   private:
    Stack<T> in;
    Stack<T> out;

    // Vuelca todo _in sobre _out (invierte el orden)
    void transfer()
    {
        while (in.getSize() > 0) {
            out.push(in.pop().value());
        }
    }

   public:
    QueueWithTwoStacks() = default;

    void enqueue(T val) { in.push(val); }

    std::optional<T> dequeue()
    {
        if (out.getSize() == 0) {
            if (in.getSize() == 0) return std::nullopt;
            transfer();
        }
        T val = out.pop().value();
        return val;
    }

    std::optional<T> front()
    {
        if (out.getSize() == 0) {
            if (in.getSize() == 0) return std::nullopt;
            transfer();
        }
        // Sacamos y volvemos a poner (simula top() de Stack)
        T val = out.pop().value();
        out.push(val);
        return val;
    }

    int getSize() const { return in.getSize() + out.getSize(); }

    bool isEmpty() const { return getSize() == 0; }
};

// Demo
int main()
{
    QueueWithTwoStacks<int> q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);

    std::cout << "Front: " << q.front().value() << " (esperado: 1)\n";
    std::cout << "Dequeue: " << q.dequeue().value() << " (esperado: 1)\n";
    std::cout << "Dequeue: " << q.dequeue().value() << " (esperado: 2)\n";

    q.enqueue(5);
    q.enqueue(6);

    while (!q.isEmpty()) {
        std::cout << "Dequeue: " << q.dequeue().value() << "\n";
    }
    // Salida esperada: 3, 4, 5, 6

    return 0;
}
