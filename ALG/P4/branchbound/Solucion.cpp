//
// Created by salva on 19/5/21.
//

#include "Solucion.h"
#include <queue>
#include <algorithm>
using namespace std;


Solucion::Solucion(const std::vector<double> & v, int tam_recipiente) : pesos(v), objetos(v.size(),0) {
    cotaGlobal = v.size();
    this->tam_recipiente = tam_recipiente;
    posicion = 0;
    num_recipientes = 0;
    peso = 0;
    estimador = 0;
}

bool Solucion::Factible() const {
    int recipiente_actual = objetos[posicion];
    double suma = 0;
    for (int i=0; i < pesos.size(); i++){
        if (objetos[i] == recipiente_actual)
            suma += pesos[i];
    }
    return suma < tam_recipiente;
}

void Solucion::PrimerValorComp(int k) {
    objetos[k] = 0;
}

void Solucion::SigValComp(int k) {
    objetos[k]++;
}

int Solucion::Comp(int k) const {
    return objetos[k];
}

float Solucion::CotaLocal() const {
    return *(max_element(objetos.begin(), objetos.end()));
}

bool Solucion::HayMasValores(int k) const {
    return objetos[k] != tam_recipiente +1;
}

float Solucion::Evalua() {
    return num_recipientes;
}

int Solucion::NumComponentes() const {
    return objetos.size();
}

bool Solucion::EsSolucion() const {
    bool ok = true;
    for (int i = 0; i < objetos.size() && ok; i++) {
        if (objetos[i] == 0) {
            ok = false;
        }
    }

    return ok;
}

int Solucion::CompActual() const {
    return posicion;
}

bool Solucion::operator<(const Solucion &s) const {
    return estimador < s.estimador;
}

Solucion algoritmo_BB(vector<double>pesos, int tam_recipiente) {
    priority_queue<Solucion> Q;
    Solucion n_e(pesos,tam_recipiente), mejor_solucion(pesos,tam_recipiente);
    int k = 0;
    float CG = pesos.size(); // inicializado a n porque nunca vas a usar maś de N recipientes
    float ganancia_actual;

    Q.push(n_e);
    while (!Q.empty() && (Q.top().CotaLocal() < CG)){ // cotaLocal > CG o cotaLocal < CG ?
        n_e = Q.top();
        Q.pop();
        k = n_e.CompActual();
        for (n_e.PrimerValorComp(k+1); n_e.HayMasValores(k+1); n_e.SigValComp(k+1)){
            if (n_e.EsSolucion()){
                ganancia_actual = n_e.Evalua();
                if (ganancia_actual > CG) {
                    CG = ganancia_actual;
                    mejor_solucion = n_e;
                }
            } else if (n_e.Factible() && n_e.CotaLocal() < CG){
                    Q.push(n_e);
            }

        }
    }

    return mejor_solucion;
}

