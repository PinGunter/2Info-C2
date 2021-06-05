//
// Created by salva on 4/6/21.
//

#include <iomanip>
#include "Solucion.h"

using namespace std;

Solucion::Solucion(ifstream &fichero) {
    fichero >> proyectos >> recursos;
    recursos++;
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

    Ar = new int * [proyectos];
    for (int i=0; i < proyectos; i++){
        Ar[i] = new int [recursos];
    }

    for (int i=0; i < proyectos; i++){
        for (int j=0; j < recursos; j++){
            M[i][j] = -1;
            Ar[i][j] = -1;
        }
    }
    asignacion.resize(proyectos);



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

    if (Ar != nullptr){
        for (int i=0; i < proyectos; i++){
            delete [] Ar[i];
        }
        delete [] Ar;
    }
}

int Solucion::B(int n, int r) {
//    cout << "n:" << n << " r:" << r << endl;
//    imprimir();
    if (n == 0){
        return 0;
    }
    int prev = M[n-1][r];
    if (M[n-1][r] == -1){
        M[n-1][r] = -2; //numeric_limits<int>::min(); //"-infinito"
        for (int k=0; k <= r; k++){
            prev = M[n-1][r];
            M[n-1][r] = max(M[n-1][r],B(n-1,r-k) + N[n-1][k]);
            if (prev != M[n-1][r]){
                Ar[n - 1][r] = k;
            }
        }
    }


    return M[n-1][r];
}

int Solucion::resolver() {
    return B(proyectos,recursos-1);
}

void Solucion::imprimir() const {
    cout << "\nBENEFICIOS: " << endl;
    for (int i=0; i < proyectos; i++){
        for (int j=0; j < recursos; j++){
            cout << setw(3) << N[i][j] << " ";
        }
        cout << endl;
    }
//
//    cout << "MEMOIA: " << endl;
//    for (int i=0; i < proyectos; i++){
//        for (int j=0; j < recursos; j++){
//            cout << setw(3) <<  M[i][j] << " ";
//        }
//        cout << endl;
//    }
//    cout << endl;
//
//    cout << "Asignacion: " << endl;
//    for (int i=0; i < proyectos; i++){
//        for (int j=0; j < recursos; j++){
//            cout << setw(3) << Ar[i][j] << " ";
//        }
//        cout << endl;
//    }
//    cout << endl;
}

std::vector<int> Solucion::getAsignacion() {
    int desplazamiento = recursos-1;
    for (int i=proyectos-1; i >= 0; i--){
        asignacion[i] = Ar[i][desplazamiento];
        desplazamiento -= Ar[i][desplazamiento];
    }
    return asignacion;
}

//std::vector<int> Solucion::getAsignacion() const {
//
//}

