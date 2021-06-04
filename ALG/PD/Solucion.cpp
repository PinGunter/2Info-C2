//
// Created by salva on 4/6/21.
//

#include <iomanip>
#include "Solucion.h"

using namespace std;

Solucion::Solucion(ifstream &fichero) {
    fichero >> proyectos >> recursos;
    N = new int * [proyectos];
    for (int i=0; i < proyectos; i++){
        N[i] = new int [recursos];
    }

    for (int i=0; i < proyectos; i++){
        for (int j=0; j < recursos; j++){
            fichero >> N[i][j];
        }
    }

    M = new int * [proyectos];
    for (int i=0; i < proyectos; i++){
        M[i] = new int [recursos];
    }

    for (int i=0; i < proyectos; i++){
        for (int j=0; j < recursos; j++){
            M[i][j] = -1;
        }
    }

}

Solucion::~Solucion(){
    if (M != nullptr){
        for (int i=0; i < proyectos; i++){
            delete [] M[i];
        }
        delete [] M;
    }

    if (N != nullptr){
        for (int i=0; i < proyectos; i++){
            delete [] N[i];
        }
        delete [] N;
    }
}

int Solucion::B(int n, int r) {
    cout << "n:" << n << " r:" << r << endl;

    if (n == 1){
        return 0;
    }
    if (M[n-1][r-1] == -1){
        M[n-1][r-1] = -2; //numeric_limits<int>::min(); //"-infinito"
        for (int k=0; k < r; k++){
            M[n-1][r-1] = max(M[n-1][r-1],B(n-1,r-k) + N[n-1][k-1]);
        }
    }
    imprimir();

    return M[n-1][r-1];
}

int Solucion::resolver() {
    return B(proyectos,recursos);
}

void Solucion::imprimir() const {
//    cout << "\nBENEFICIOS: " << endl;
//    for (int i=0; i < proyectos; i++){
//        for (int j=0; j < recursos; j++){
//            cout << N[i][j] << " ";
//        }
//        cout << endl;
//    }

    cout << "MEMOIA: " << endl;
    for (int i=0; i < proyectos; i++){
        for (int j=0; j < recursos; j++){
            cout << setw(4) <<  M[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

