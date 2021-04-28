#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <vector>
#include <stdlib.h>
#include <fstream>

//problema de minimizar el número de recipientes de capacidad R donde almacenar objetos de peso w[k]<=R
//enfoque de fuerza bruta, comprueba todas las posibilidades
//para más de 12 objetos los tiempos se disparan (con 12 aprox minuto y medio, con 13 se va a 21 minutos)

float *w;
int *x;
int *solucion;
bool asignado;
int n;
int i,j;
const float R=1.0;
int mejor;
float *suma;


double uniforme() //Genera un número uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C. 
{
 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;
}


void generapesos() {

 srand(time(0));
 for (int i = 0; i < n; i++) {
     double u=uniforme();
     w[i]=u;
  }
}


int compare1 (const void * a, const void * b){
    return ( *(int*)a - *(int*)b );
}

vector<pair<float,int>> algoritmoVoraz1(){ //En nuestro caso, como los pesos siempre son menor a R y hay infinitos recipientes, siempre hay solución

    qsort(w, n, sizeof(float), compare1); // Ordenamos de los pesos de los objetos el vector por quicksort

    vector<float> pesos(w,w+n);       // Vector pesos
    vector<pair<float,int>> solucion; // Vector solución con peso y recipiente en el que se ha guardado
    float actual;                     //Peso objeto a introducir en el recipiente
    int n_recipientes = 1;            //Numero de recipientes utilizados
    float recipiente_actual = 0.0;    //Tamaño ocupado del recipiente actual

    while (pesos.size() != 0){
        actual = pesos.front();
        pesos.erase(pesos.begin()); // Eliminamos el objeto actual que ya hemos introducido previamente.

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




int main(int argc, char **argv){
    n = atoi(argv[1]);
    w = new float[n];

    ofstream salida1; salida1.open("optimalidad_greedy1.dat",ofstream::app);
    ofstream salida2; salida2.open("optimalidad_greedy2.dat",ofstream::app);
    int recipientes1 = 0, recipientes2 = 0;

    generapesos();

    recipientes1 = algoritmoVoraz1().back().second;
    recipientes2 = algoritmoVoraz2().back().second;

    salida1 << n << " " << recipientes1 << endl;
    salida2 << n << " " << recipientes2 << endl;

    salida1.close(); salida2.close();    
}