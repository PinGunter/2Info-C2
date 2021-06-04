#include <iostream>
#include "Solucion.h"
using namespace std;

int main(int argc, char **argv) {
    if (argc != 2){
        cerr << "Error, hace falta fichero con matriz de beneficios" << endl;
        exit(EXIT_FAILURE);
    }

    ifstream fichero(argv[1]);
    Solucion s(fichero);

    int optimo =  s.resolver();
    cout << "Solución: " << optimo << endl;
}
