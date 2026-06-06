#include "Semaforo.h"
#include <chrono>

Semaforo::Semaforo(int valorInicial){
    contador = valorInicial;
}

void Semaforo::wait(){
    std::unique_lock<std::mutex> lock(mtx);
    while(contador == 0){cv.wait(lock);};
    contador--;
}

void Semaforo::signal(){
    std::unique_lock<std::mutex> lock(mtx);
    contador++;
    cv.notify_one();
}

bool Semaforo::wait_for(int milisegundos){
    std::unique_lock<std::mutex> lock(mtx);
    auto limite = std::chrono::milliseconds(milisegundos);
    while(contador == 0){
        if(cv.wait_for(lock, limite) == std::cv_status::timeout){return false;}
    }
    contador--;
    return true;
}
