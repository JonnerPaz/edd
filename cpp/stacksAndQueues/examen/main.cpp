// Se necesita procesar operaciones similares a:
// [(1+)7,8(0+)5,6(2x)1,0]
//  Donde:
//  (N operador) = prioridad, operación a realizar
//  x,y = Valores a operar
//  []+ = lista de valores a aplicar en la operación
#include <iostream>
#include <ostream>
#include <string>
#include <utility>

#include "./List.hpp"
#include "./isBalanced.hpp"
#include "./priorityQueueWithArray.hpp"

using namespace std;

enum OperationType { ADDITION = '+', SUBSTRACTION = '-', DIVISION = '/', MULTIPLICATION = '*' };

// Esto es lo que voy a guardar en la cola de prioridades.
// Todas las operaciones deben estar organizadas en la estructura antes de
// lanzarlas a la cola
struct Operation {
    std::pair<int, OperationType> operand;
    std::pair<int, int> numbers;
};

int processOperation(const string allOperations)
{
    List<Operation> operations;

    if (!isBalanced(allOperations)) {
        cout << "No se puede procesar las operaciones por fallo de sintaxis" << endl;
        cout << "Revisa nuevamente las operaciones que escogiste" << endl;
        return -1;
    }

    int pathing = 0;
    bool insideOperand = true;
    for (char c : allOperations) {
        if (c == ']' || c == '[') {
            pathing++;

            // cuando llegue a ']' ya terminó de hacer todas las operaciones. Sal del ciclo
            if (pathing == 2) break;
            continue;
        }

        if (c == '(') {
            continue;
        }

        if (insideOperand) {
            if (isdigit(c)) {
                cout << "Prioridad: " << c << endl;
            } else if (c == '+' || c == '-' || c == '/' || c == 'x') {
                cout << "Operación: " << c << endl;
                insideOperand = false;
            }
        } else {
            if (isdigit(c)) {
                cout << "Número: " << c << endl;
            } else if (c == ',') {
                cout << "Separador de números" << endl;
            }
        }
    }

    PriorityQueue<Operation>* opQueue = new PriorityQueue<Operation>();

    for (int i = 0; i < operations.getSize(); i++) {
        auto op = operations.get(i)->getData();
        opQueue->push(op);
    }

    char finalOperand = allOperations.at(-1);
    // todos los números ordenados en la cola, en su respectiva prioridad

    int resultOperation = 0;
    // crear un arreglo donde se guarden todas las operaciones
    // opLists
    while (!opQueue->isEmpty()) {
        auto op = opQueue->pop().value();

        switch (op.operand.second) {
            case ADDITION:
                resultOperation += (op.numbers.first + op.numbers.second);
                break;
            case SUBSTRACTION:
                resultOperation += (op.numbers.first - op.numbers.second);
                break;
            case MULTIPLICATION:
                resultOperation += (op.numbers.first * op.numbers.second);
                break;
            case DIVISION:
                resultOperation += (op.numbers.first / op.numbers.second);
                break;
            default:
                break;
        }
    }

    // Hacer el operando final acorde a lo que está fuera del corchete

    return resultOperation;
}

int main()
{
    processOperation("[(1+)7,8(0+)5,6(2x)1,0]");
    return 0;
}
