#include <iostream>
#include <string>

#include "../priorityQueues/priorityQueueWithArray.hpp"

struct Task {
    int id;
    std::string description;
    int exeTime;  // en ms
};

class TaskManager
{
   private:
    PriorityQueueWithArray<Task> tasks;

   public:
    void registerTask(int id, std::string desc, int tiempo, int prioridad)
    {
        tasks.push({id, desc, tiempo}, prioridad);
    }

    void executeAll()
    {
        if (tasks.isEmpty()) {
            std::cout << "No hay tareas pendientes en el sistema.\n";
            return;
        }

        int tiempoTotal = 0;
        while (!tasks.isEmpty()) {
            auto tareaOpt = tasks.pop();
            if (tareaOpt.has_value()) {
                Task t = tareaOpt.value();
                std::cout << "[CPU] Ejecutando Tarea ID " << t.id << ": " << t.description
                          << " (Tarda: " << t.exeTime << "ms)\n";
                tiempoTotal += t.exeTime;
            }
        }
        std::cout << ">> Tiempo total de procesamiento: " << tiempoTotal << "ms <<\n";
    }
};
