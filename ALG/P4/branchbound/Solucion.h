//
// Created by salva on 19/5/21.
//

#ifndef BRANCHBOUND_SOLUCION_H
#define BRANCHBOUND_SOLUCION_H
#include <iostream>
#include <vector>


class Solucion {
public:
    Solucion(const std::vector<double> & v, int tam_recipiente);
    bool Factible() const; // si cabe en el recipiente actual
    void PrimerValorComp(int k);
    void SigValComp(int k);
    int Comp(int k) const;
    float CotaLocal() const;
    bool HayMasValores(int k) const;
    float Evalua();
    int NumComponentes() const;
    bool EsSolucion() const;
    int CompActual() const;
    bool operator<(const Solucion & s) const;

    std::vector<int> objetos;
    std::vector<double> pesos;
    int cotaGlobal;
    int tam_recipiente;
    int posicion;
    int num_recipientes;
    double peso;
    int estimador;
};

Solucion algoritmo_BB(std::vector<double>pesos, int tam_recipiente);
#endif //BRANCHBOUND_SOLUCION_H
