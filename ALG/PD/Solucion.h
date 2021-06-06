//
// Created by salva on 4/6/21.
//

#ifndef PD_SOLUCION_H
#define PD_SOLUCION_H


#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

class Solucion{
private:
    int ** M; //matriz de memoización
    int ** N; //matriz beneficios
    int ** Ar; //matriz donde guardamos los recursos usados
    std::vector<int> asignacion;
    int proyectos, recursos;
public:
    Solucion(std::ifstream & fichero);
    ~Solucion();
    void imprimir() const;

    int resolver();

    int B(int n, int r);

    std::vector<int> getAsignacion();
};



#endif //PD_SOLUCION_H
