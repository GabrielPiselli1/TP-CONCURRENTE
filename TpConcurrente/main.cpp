#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Pruebas.h"

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));

    //DESCOMENTAR EL QUE SE QUIERER EJECUTAR

    std::cout<< "SIMULADOR LOGISTICO\n\n";

    //CONFIGURACION A |4 SEGUNDOS APROX|
    //ejecutarPrueba(1,2,10,"Configuracion A (1P - 2C)");

    // CONFIGURACION B |20 SEGUNDOS APROX|
    //ejecutarPrueba(3,1,10,"Configuracion B (3P - 1C)");

    // CONFIGURACION C |8 SEGUNDOS APROX|
    //ejecutarPrueba(3,3,10,"Configuracion C (3P - 3C)");

    // CARGA MASIVA |382 SEGUNDOS APROX|
    //ejecutarPrueba(3,3,517,"Carga Masiva");

    // VACUIDAD |0 SEGUNDOS|
    //ejecutarPrueba(1,2,0,"Prueba Vacuidad");

    // SATURACION |3 SEGUNDOS|
    //ejecutarPruebaPrioridad(2,8,0,"Prueba Saturacion");

    // ANTI STARVATION |44 SEGUNDOS|
    //ejecutarPruebaPrioridad(1,60,1,"Prueba Anti-Starvation");

    return 0;
}
