#ifndef SISTEMALOGISTICO_H
#define SISTEMALOGISTICO_H

#include <deque>

#include "Paquete.h"
#include "Semaforo.h"

class SistemaLogistico
{
public:

    // Waiting Queue
    std::deque<Paquete> waitingQueue;

    // Processing Queue (cinta)
    std::deque<Paquete> processingQueue;

    // Semáforos
    Semaforo mutexColas;  // Exclusión mutua
    Semaforo mutexID;   // Evita race condition
    Semaforo espaciosCinta;  // Capacidad maxima 5
    Semaforo sincronizacion;  // Productor-Consumidor

    int generadorID;

    bool productoresTerminados;

    // Métricas
    int paquetesProducidos;

    int procesadosAlta;
    int procesadosBaja;

    long long esperaAlta;
    long long esperaBaja;

    SistemaLogistico();
};

long long obtenerTiempoMs();

#endif
