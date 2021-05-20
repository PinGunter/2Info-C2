#include <iostream>
#include <queue>
#include "Solucion.h"
using namespace std;

#include <iostream>
#include <vector>
#include <ctime>
using namespace std;


double uniforme(double max) //Genera un número uniformemente distribuido en el
//intervalo [0,1) a partir de uno de los generadores
//disponibles en C.
{
    int t = rand();
    double f = ((double)RAND_MAX+1.0);
    return (double)t/f;
}

void generaPesos(int n, double m, vector<double> &p) 
{
    double max = 2147483647; //los pesos serán números reales entre 0 y 2147483647
    srand (time(NULL)); 
    if (!(m <= 0 || m > max))
        max = m;

    for (int i = 0; i < n; i++) { 
        double u = uniforme(max);
        p.push_back(u); //uniforme entre 1 y max
    }
}



int main(int argc, char const *argv[]) // ./binario <numero_objetos> <capacidad_maxima_recipientes> <peso_maximo>
{

    double pesoMaximo = 1;
    int capacidad = 1;
    vector<double> pesos;

    if(argc != 4 && argc != 3 && argc != 2){
        cerr << "Error al introducir parámetros. Use: ./binario <numero_objetos> <capacidad_maxima_recipientes> <peso_maximo>" << endl;
        exit(-1);
    }

    int numeroObjetos = atoi(argv[1]);

    if(argc == 4){
        pesoMaximo = atoi(argv[3]);
    }

    if(argc == 3){
        capacidad = atoi(argv[2]); 
    }

    generaPesos(numeroObjetos, pesoMaximo, pesos);  // Generamos aleatoriamente el vector de los objetos con sus pesos

    cout << " VECTOR INICIAL DE PESOS "<< endl;
    for(int i=0; i<numeroObjetos; ++i){
        cout << pesos[i] << endl;
    }
    cout << endl;

    Solucion bb = algoritmo_BB(pesos,1);
    for (int i=0; i < bb.objetos.size(); i++){
            cout << "Objeto con peso: " << bb.pesos[i] << " en recipiente " << bb.objetos[i] << endl;
        }


    return 0;
}