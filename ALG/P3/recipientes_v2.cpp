#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <vector>
#include <stdlib.h>

float *w;   //Vector con los pesos de los objetos
int restante;   //Tamaño restante del recipiente actual
bool asignado;
int i,j;
int n; // Número de objetos
float R; // Capacidad máxima del recipiente


clock_t tantes;
clock_t tdespues;


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

    if (argc < 2){
        cerr << "Formato " << argv[0] << " <numeroObjetos> <tamanyoRecipiente>" <<  endl;
        return -1;
    }

    n = atoi(argv[1]);  //Numero de objetos

    if(argc==3 && atof(argv[2])>1.0)
        R=atof(argv[2]); //Tamaño de cada recipiente
    else
        R=1.0; //Si no especifica el tamaño de cada recipiente, lo inicializamos a 1


    w = new float[n];//Vector con los pesos de los objetos

    vector<pair<float,int>> solucion;

    restante = R;   //Capacidad restante

    i=1;

    generapesos();  //Creamos los pesos de los objetos

    cout << "\nLos pesos son: " << endl;
    for (int k = 0; k < n; k++) cout << " " << w[k] << " ";
    cout << endl;

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