//
// Created by salva on 14/5/21.
//

#ifndef BACKTRACK_SOLUCION_H
#define BACKTRACK_SOLUCION_H

#include <vector>
#include <iostream>

void print(const std::vector<int> & A);
int sumaVector(const std::vector<int> & A);
class Solucion {

private:

    std::vector<int> personas;
    std::vector<int> solucion;
    int numerosoluciones;
    int total;
    int obj;
    int mejor_diferencia;
    std::vector<int> solucion_buena;
    std::vector<int> solucion_dif_minima;
    void resolver(int s, int k, int r);

public:

    Solucion(const std::vector<int> &pesos);
    void equilibrarEquipos();
    std::vector<int> getSolucion() const;
    std::vector<int> getVectorEquipo() const;
    int getTotal() const;

};


#endif //BACKTRACK_SOLUCION_H
