//
// Created by salva on 14/5/21.
//

#include "solucion.h"
#include <iomanip>
#include <cmath>

Solucion::Solucion(const std::vector<int> &pesos)  : personas(pesos), solucion(pesos.size()), solucion_dif_minima(pesos.size()){
    numerosoluciones = 0;
    total = 0;
    for (auto e: pesos){
        total += e;
    }
    obj = total/2;
    mejor_diferencia = total*2;
}

int sumaVector(const std::vector<int> & v){
    int suma = 0;
    for (auto e: v){
        suma += e;
    }
    return suma;
}

void print(const std::vector<int> &A, std::ostream & os) {
    for(int i = 0; i < A.size(); i++)
    {
        os << std::setw(6) << A[i] << " ";
    }
    os << "\n";
}

void Solucion::resolver_BackTrack(int s, int k, int r) {
    if (numerosoluciones != 1) { //saber si ha encontrado la solucion optima
        solucion[k] = 1;
        if (s + personas[k] == obj) {
            numerosoluciones++;
            solucion_buena = solucion;
            print(solucion);
        } else if (s + personas[k] < obj) {    //si no te pasas => puede seguir explorando esa rama
            resolver_BackTrack(s + personas[k], k + 1, r - personas[k]);
        }
        solucion[k] = 0;
        if ((s + r - personas[k] >= obj) && (s+personas[k+1] <= obj)) {
            solucion[k] = 0;
            resolver_BackTrack(s, k + 1, r - personas[k]);
        }
        if (abs(obj - s) < abs(obj - mejor_diferencia)){
            mejor_diferencia = s;
            solucion_dif_minima = solucion;
        }
    } else
        return;
}


void Solucion::equilibrarEquipos() {
    resolver_BackTrack(0,0,total);
    if (numerosoluciones == 0){
        solucion_buena = solucion_dif_minima;
        print(solucion_buena);
    }
}

std::vector<int> Solucion::getSolucion() const {
    return solucion_buena;
}

std::vector<int> Solucion::getVectorEquipo() const {
    std::vector<int> v;
    for (int i=0; i < personas.size(); i++){
        if (solucion_buena[i] == true){
            v.push_back(personas[i]);
        }
    }
    return v;
}

int Solucion::getTotal() const{
    return total;
}

void Solucion::resolver_FB(int s, int k) {
    if (numerosoluciones == 0) {
        if (k == personas.size()) {
            if (s == obj) {
                numerosoluciones++;
                print(solucion);
                solucion_buena = solucion;
            }
            if (abs(obj - s) < abs(obj - mejor_diferencia)){
                mejor_diferencia = s;
                solucion_dif_minima = solucion;
            }
            return;
        }
        solucion[k] = 0;
        resolver_FB(s, k + 1);
        solucion[k] = 1;
        resolver_FB(s + personas[k], k + 1);


    } else return;
}

void Solucion::equilibrarEquipos_FB() {
    resolver_FB(0,0);
    if (numerosoluciones == 0){
        solucion_buena = solucion_dif_minima;
        print(solucion_buena);
    }
}
