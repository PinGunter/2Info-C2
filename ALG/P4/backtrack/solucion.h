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
    void resolver_BackTrack(int s, int k, int r);
    void resolver_FB(int s, int k);

public:

    Solucion(const std::vector<int> &pesos);
    void equilibrarEquipos();
    void equilibrarEquipos_FB();
    std::vector<int> getSolucion() const;
    std::vector<int> getVectorEquipo() const;
    int getTotal() const;

};


//void Solucion::resolver_FB(int s, int k, int r, int i) {
////    if (numerosoluciones != 1) { //saber si ha encontrado la solucion optima
//        if (s + personas[k] == obj) {
//            numerosoluciones++;
//            solucion_buena = solucion;
//            return;
////            print(solucion);
//        }
//        if (i == personas.size()){
//            return;
//        }
//        solucion[k] = 1;
//        resolver_FB(s + personas[k], k + 1, r - personas[k],i+1);
//        solucion[k] = 0;
//        resolver_FB(s, k + 1, r - personas[k],i+1);
//
//
////        if (abs(obj - s) < abs(obj - mejor_diferencia)){
////            mejor_diferencia = s;
////            solucion_dif_minima = solucion;
////        }
////    } else
////        return;
//}



#endif //BACKTRACK_SOLUCION_H
