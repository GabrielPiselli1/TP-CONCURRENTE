#include "Productor.h"
#include <thread>
#include <cstdlib>
#include <chrono>

void productor(SistemaLogistico& sistema,int cantidad){
    for(int i = 0; i < cantidad; i++){
        Paquete p;
        p.tiempoCreacion = obtenerTiempoMs();
        
        p.prioridad = rand() % 2;
            sistema.mutexID.wait();
            sistema.generadorID++;
            p.id = sistema.generadorID;
            sistema.paquetesProducidos++;
        sistema.mutexID.signal();

        std::this_thread::sleep_for(std::chrono::milliseconds(90));

        sistema.mutexColas.wait();
            sistema.waitingQueue.push_back(p);
        sistema.mutexColas.signal();

        sistema.sincronizacion.signal();
    }
}

void productorPrioridadFija(SistemaLogistico& sistema,int cantidad,int prioridad){
    for(int i = 0; i < cantidad; i++)
    {
        Paquete p;
        p.tiempoCreacion = obtenerTiempoMs();
        p.prioridad = prioridad;
        sistema.mutexID.wait();
            sistema.generadorID++;
            p.id = sistema.generadorID;
            sistema.paquetesProducidos++;
        sistema.mutexID.signal();

        std::this_thread::sleep_for(std::chrono::milliseconds(90));

        sistema.mutexColas.wait();
            sistema.waitingQueue.push_back(p);
            sistema.mutexColas.signal();
        sistema.sincronizacion.signal();
    }
}
