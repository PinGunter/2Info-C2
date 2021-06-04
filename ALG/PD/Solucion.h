//
// Created by salva on 4/6/21.
//

#ifndef PD_SOLUCION_H
#define PD_SOLUCION_H


#include <iostream>
#include <fstream>
#include <limits>

class Solucion{
private:
    int ** M; //matriz de memoización
    int ** N; //matriz beneficios
    int proyectos, recursos;
    void imprimir() const;
public:
    Solucion(std::ifstream & fichero);

    ~Solucion();

    int resolver();

    int B(int n, int r);
};



#endif //PD_SOLUCION_H
