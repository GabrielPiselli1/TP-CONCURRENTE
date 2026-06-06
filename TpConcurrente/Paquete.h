#ifndef PAQUETE_H
#define PAQUETE_H

struct Paquete
{
    int id;
    int prioridad; // 0 = baja, 1 = alta

    long long tiempoCreacion;
    long long tiempoIngresoCinta;
};

#endif
