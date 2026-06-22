// StackWithTwoQueues: stack implementado con dos colas
//
// Usa dos colas señaladas por q1 y q2:
//   push(): encola en q1 → O(1)
//   pop():  mueve n-1 elementos de q1 a q2,
//           el último es el tope del stack,
//           luego intercambia q1 <-> q2 (swap de punteros) → O(n)
//   top():  similar a pop() pero devuelve el valor sin eliminarlo
//
// Estrategia: push es barato (O(1)), pop caro (O(n)) pero justo
// porque el elemento que se va está al final. Es el inverso de
// la implementación QueueWithTwoStacks.

#include <iostream>
#include <optional>

#include "../queues/Queue.hpp"

template <typename T>
class StackWithTwoQueues
{
   private:
    Queue<T>* q1;
    Queue<T>* q2;

   public:
    StackWithTwoQueues() : q1(new Queue<T>()), q2(new Queue<T>()) {}

    ~StackWithTwoQueues()
    {
        delete q1;
        delete q2;
    }

    void push(T val) { q1->push(val); }

    std::optional<T> pop()
    {
        if (q1->getSize() == 0) return std::nullopt;

        // Mover n-1 elementos de q1 a q2
        while (q1->getSize() > 1) {
            q2->push(q1->pop().value());
        }

        // El último elemento de q1 es el tope del stack
        T val = q1->pop().value();

        // Intercambiar punteros: q1 ahora apunta a q2 y viceversa
        Queue<T>* tmp = q1;
        q1 = q2;
        q2 = tmp;

        return val;
    }

    std::optional<T> top()
    {
        if (q1->getSize() == 0) return std::nullopt;

        // Mover n-1 elementos de q1 a q2
        while (q1->getSize() > 1) {
            q2->push(q1->pop().value());
        }

        // El último es el tope; lo guardamos y también lo pasamos a q2
        T val = q1->pop().value();
        q2->push(val);

        // Intercambiar punteros
        Queue<T>* tmp = q1;
        q1 = q2;
        q2 = tmp;

        return val;
    }

    int getSize() const { return q1->getSize(); }

    bool isEmpty() const { return q1->getSize() == 0; }
};

// Demo
int main()
{
    StackWithTwoQueues<int> s;
    s.push(10);
    s.push(20);
    s.push(30);

    std::cout << "Top: " << s.top().value() << " (esperado: 30)\n";
    std::cout << "Pop: " << s.pop().value() << " (esperado: 30)\n";
    std::cout << "Pop: " << s.pop().value() << " (esperado: 20)\n";
    s.push(40);
    std::cout << "Pop: " << s.pop().value() << " (esperado: 40)\n";
    std::cout << "Pop: " << s.pop().value() << " (esperado: 10)\n";
    std::cout << "Pop: vacío? " << (s.pop().has_value() ? "no" : "sí") << "\n";

    return 0;
}
