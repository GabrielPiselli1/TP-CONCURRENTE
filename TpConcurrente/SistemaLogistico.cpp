#include "SistemaLogistico.h"

#include <chrono>

SistemaLogistico::SistemaLogistico():mutexColas(1),mutexID(1),espaciosCinta(5),sincronizacion(0)
{
    generadorID = 0;

    productoresTerminados = false;

    paquetesProducidos = 0;

    procesadosAlta = 0;
    procesadosBaja = 0;

    esperaAlta = 0;
    esperaBaja = 0;
}

long long obtenerTiempoMs()
{
    auto ahora =std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(ahora.time_since_epoch() ).count();
}
