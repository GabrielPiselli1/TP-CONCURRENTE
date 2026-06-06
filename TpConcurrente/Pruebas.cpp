#include "Pruebas.h"
#include "SistemaLogistico.h"
#include "Productor.h"
#include "Consumidor.h"

#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

void imprimirMetricas(SistemaLogistico& sistema,const std::string& nombre)
{
    std::cout << "\n----------------\n";
    std::cout << nombre << "\n";
    std::cout << "---------------\n";

    std::cout<< "Paquetes producidos: "<< sistema.paquetesProducidos<< "\n";

    std::cout<< "Procesados alta: "<< sistema.procesadosAlta<< "\n";

    std::cout<< "Procesados baja: "<< sistema.procesadosBaja<< "\n";

    long long promAlta = 0;
    long long promBaja = 0;

    if(sistema.procesadosAlta > 0)
    {
        promAlta = sistema.esperaAlta / sistema.procesadosAlta;
    }

    if(sistema.procesadosBaja > 0)
    {
        promBaja = sistema.esperaBaja / sistema.procesadosBaja;
    }

    std::cout<< "Promedio Alta: "<< promAlta<< " ms\n";

    std::cout<< "Promedio Baja: "<< promBaja<< " ms\n";
}

void ejecutarPrueba(int productores,int consumidores,int paquetesPorProductor,const std::string& nombre)
{
    SistemaLogistico sistema;

    std::vector<std::thread> productoresHilos;
    std::vector<std::thread> consumidoresHilos;

    auto inicio = std::chrono::steady_clock::now();

    for(int i = 0; i < consumidores; i++)
    {
        consumidoresHilos.emplace_back(consumidor,std::ref(sistema));
    }

    for(int i = 0; i < productores; i++)
    {
        productoresHilos.emplace_back(productor,std::ref(sistema),paquetesPorProductor);
    }

    for(auto& t : productoresHilos)
    {
        t.join();
    }

    sistema.mutexColas.wait();
    sistema.productoresTerminados = true;
    sistema.mutexColas.signal();

    for(int i = 0; i < consumidores * 5; i++)
    {
        sistema.sincronizacion.signal();
    }

    for(auto& t : consumidoresHilos)
    {
        t.join();
    }

    auto fin = std::chrono::steady_clock::now();

    std::cout<< "\nTiempo total: "<< std::chrono::duration_cast<std::chrono::seconds>(fin - inicio).count()<< " segundos\n";

    imprimirMetricas(sistema,nombre);
}

void ejecutarPruebaPrioridad(int consumidores,int cantidadAlta,int cantidadBaja,const std::string& nombre)
{
    SistemaLogistico sistema;

    std::vector<std::thread> productoresHilos;
    std::vector<std::thread> consumidoresHilos;

    auto inicio =std::chrono::steady_clock::now();

    for(int i = 0; i < consumidores; i++)
    {
        consumidoresHilos.emplace_back(consumidor,std::ref(sistema));
    }

    if(cantidadAlta > 0)
    {
        productoresHilos.emplace_back(productorPrioridadFija,std::ref(sistema),cantidadAlta,1);
    }

    if(cantidadBaja > 0)
    {
        productoresHilos.emplace_back(productorPrioridadFija,std::ref(sistema),cantidadBaja,0);
    }

    for(auto& t : productoresHilos)
    {
        t.join();
    }

    sistema.mutexColas.wait();
    sistema.productoresTerminados = true;
    sistema.mutexColas.signal();

    for(int i = 0; i < consumidores * 5; i++)
    {
        sistema.sincronizacion.signal();
    }

    for(auto& t : consumidoresHilos)
    {
        t.join();
    }

    auto fin = std::chrono::steady_clock::now();

    std::cout<< "\nTiempo total: "<< std::chrono::duration_cast<std::chrono::seconds>(fin - inicio).count()<< " segundos\n";

    imprimirMetricas(sistema,nombre);
}
