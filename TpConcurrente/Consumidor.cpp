#include "Consumidor.h"
#include <thread>
#include <chrono>

void consumidor(SistemaLogistico& sistema)
{
    while(true){
        Paquete paqueteProcesar;
        bool procesar = false;
        Paquete paqueteMover;
        bool mover = false;

        sistema.mutexColas.wait();

        if(sistema.productoresTerminados &&sistema.waitingQueue.empty() &&sistema.processingQueue.empty()){
        sistema.mutexColas.signal();
        break;
        }

        long long ahora = obtenerTiempoMs();
        int indiceListo = -1;

        for(size_t i = 0; i < sistema.processingQueue.size(); i++){
            if(ahora -sistema.processingQueue[i].tiempoIngresoCinta>= 550){    
                indiceListo = i;
                break;
            }
        }

        if(indiceListo != -1){
            paqueteProcesar = sistema.processingQueue[indiceListo];
            sistema.processingQueue.erase(sistema.processingQueue.begin()+ indiceListo);
            sistema.espaciosCinta.signal();
            procesar = true;
        }
        else if(!sistema.waitingQueue.empty() &&sistema.processingQueue.size() < 5){
            auto elegido=sistema.waitingQueue.end();
            //starvation
            for(
                auto it = sistema.waitingQueue.begin();
                it != sistema.waitingQueue.end();
                ++it
            )
            {
                if(it->prioridad == 0)
                {
                    long long espera =ahora -it->tiempoCreacion;
                    if(espera >= 6000)
                    {
                        elegido = it;
                        break;
                    }
                }
            }

            // Prioridad alta
            if(elegido == sistema.waitingQueue.end())
            {
                for(auto it = sistema.waitingQueue.begin();it != sistema.waitingQueue.end();++it){
                    if(it->prioridad == 1){
                        elegido = it;
                        break;
                    }
                }
            }

            // Agarra el que este mas adelante si no hay alta prioridad
            if(elegido == sistema.waitingQueue.end()){ 
                elegido =sistema.waitingQueue.begin();
            }

            paqueteMover = *elegido;
            sistema.waitingQueue.erase(elegido);
            mover = true;
            }

        sistema.mutexColas.signal();

        if(mover){
            sistema.espaciosCinta.wait();
                std::this_thread::sleep_for(std::chrono::milliseconds(420));
                paqueteMover.tiempoIngresoCinta = obtenerTiempoMs();
            sistema.mutexColas.wait();
                sistema.processingQueue.push_back(paqueteMover);
            sistema.mutexColas.signal();
}

        if(procesar)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(270));
            long long espera =obtenerTiempoMs()-paqueteProcesar.tiempoCreacion;
            sistema.mutexColas.wait();
                    if(paqueteProcesar.prioridad == 1){
                        sistema.procesadosAlta++;
                        sistema.esperaAlta += espera;
                    }
                    else{
                        sistema.procesadosBaja++;
                        sistema.esperaBaja += espera;
                    }
            sistema.mutexColas.signal();
        }

        if(!mover && !procesar)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
}
