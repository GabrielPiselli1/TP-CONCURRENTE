#ifndef SEMAFORO_H
#define SEMAFORO_H

#include <mutex>
#include <condition_variable>

class Semaforo
{
private:int contador;
    std::mutex mtx;
    std::condition_variable cv;

public:Semaforo(int valorInicial = 0);

    void wait();

    void signal();

    bool wait_for(int milisegundos);
};

#endif
