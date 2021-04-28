#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <vector>
#include <stdlib.h>

float w[] = {0.871845,  0.783319, 0.297428,  0.731423,  0.166111,  0.759542,  0.107488,  0.69598,  0.573772,  0.0891034,  0.936324,  0.52613};
int restante;   //Tamaño restante del recipiente actual
bool asignado;
int i,j;
int n; // Número de objetos
float R; // Capacidad máxima del recipiente


clock_t tantes;
clock_t tdespues;





int compare2 (const void * a, const void * b){
    return ( *(int*)b - *(int*)a );
}

float funcionSeleccion2(vector<float> & v, float actual, vector<float>::iterator & posicion){
    for (posicion=v.begin(); posicion != v.end(); ++posicion){
        if (actual + (*posicion) <= R){
            return (*posicion);
        }
    }
    posicion = v.begin();
    return *posicion;
}

vector<pair<float,int>> algoritmoVoraz2(){

    qsort(w, n, sizeof(float), compare2); // Ordenamos de los pesos de los objetos el vector por quicksort

    vector<float> pesos(w,w+n);       // Vector pesos
    vector<pair<float,int>> solucion; // Vector solución con peso y recipiente en el que se ha guardado
    float actual;                     //Peso objeto a introducir en el recipiente
    int n_recipientes = 1;            //Numero de recipientes utilizados
    float recipiente_actual = 0.0;    //Tamaño ocupado del recipiente actual
    vector<float>::iterator posicion;

    while (pesos.size() != 0){
        actual = funcionSeleccion2(pesos, recipiente_actual, posicion);
        pesos.erase(posicion); // Eliminamos el objeto actual que ya hemos introducido previamente.

        if (actual + recipiente_actual <= R){   //Si cabe en el recipiente actual, lo insertamos
            solucion.push_back(pair<float,int>(actual,n_recipientes));
            recipiente_actual+=actual;
        }
        else {  //Si no cabe lo insertamos en el siguiente recipiente
            n_recipientes++;
            solucion.push_back(pair<float,int>(actual,n_recipientes));
            recipiente_actual = actual;
        }
    }

    return solucion;
}


int main(int argc, char* argv[]) {

    n = 12;
    R=1.0; //Si no especifica el tamaño de cada recipiente, lo inicializamos a 1



    vector<pair<float,int>> solucion;

    restante = R;   //Capacidad restante

    i=1;


    tantes = clock();
    solucion=algoritmoVoraz2();
    tdespues = clock();
    pair<float, int> mejor=solucion.back();
    cout << "\ntiempo: "<< (double)(tdespues - tantes) / CLOCKS_PER_SEC << endl;
    cout << "El tamaño de los recipientes (R) es: " << R << endl;
    cout << "\nSe usan " << mejor.second << " recipientes" << endl;
    cout << "\nLa distribucion es: " << endl;
    for (auto e : solucion){
        cout << " " << e.first << " en recipiente " << e.second << endl;
    }
    cout << endl;

}