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

//Metodo 1: selecciona primero el que tenga menor peso

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

    tantes = clock();
    solucion=algoritmoVoraz1();
    tdespues = clock();
    cout << n << " " << (double)(tdespues - tantes) / CLOCKS_PER_SEC << endl;

}