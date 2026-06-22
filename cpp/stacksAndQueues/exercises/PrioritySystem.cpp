#include <iostream>
#include <string>

#include "../priorityQueues/priorityQueueWithArray.hpp"

struct Paciente {
    std::string nombre;
    std::string sintoma;
};

// Función lista para simular la atención en el examen
void simularSalaEmergencias()
{
    PriorityQueueWithArray<Paciente> salaEspera;

    // Insertando pacientes con diferentes prioridades
    // 0 = Código Rojo (Paro), 2 = Trauma moderado, 5 = Resfriado
    salaEspera.push({"Juan Perez", "Paro Cardiaco"}, 0);
    salaEspera.push({"Maria Lopez", "Fiebre leve"}, 5);
    salaEspera.push({"Pedro Gomez", "Fractura expuesta"}, 1);
    salaEspera.push({"Ana Rodriguez", "Dolor de cabeza fuerte"}, 3);
    salaEspera.push({"Luis Martinez", "Insuficiencia respiratoria"}, 0);

    std::cout << "--- INICIANDO ATENCION DE PACIENTES (Por Prioridad) ---\n";

    while (!salaEspera.isEmpty()) {
        auto pacienteOpt = salaEspera.pop();
        if (pacienteOpt.has_value()) {
            Paciente p = pacienteOpt.value();
            std::cout << "[ATENDIDO] -> " << p.nombre << " | Motivo: " << p.sintoma << std::endl;
        }
    }
}
