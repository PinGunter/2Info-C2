#include <iostream>
#include "Solucion.h"
using namespace std;

ostream & operator<<(ostream & os, const vector<int> & v){
    for (auto e : v){
        os << e << " ";
    }
    os << endl;
    return os;
}

int main(int argc, char **argv) {
    if (argc != 2){
        cerr << "Error, hace falta fichero con matriz de beneficios" << endl;
        exit(EXIT_FAILURE);
    }

    ifstream fichero(argv[1]);
    Solucion s(fichero);

    int optimo =  s.resolver();
    vector<int> v = s.getAsignacion();
    s.imprimir();
    cout << "Solución: " << optimo << endl;
    cout << "Asignación: " << endl;
    for (int i=0; i < v.size(); i++){
        cout << "Al proyecto " << i+1 << " se le asignan " << v[i] << " recursos" << endl;
    }
}
