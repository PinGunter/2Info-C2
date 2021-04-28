#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
//#include <algorithm>
//#include <vector>

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

int main(int argc, char **argv){
    n = atoi(argv[1]);
    w = new float[n];
    generapesos();
    for (int i=0; i < n; i++)
    {
        cout << w[i];
        if (i != n-1)
            cout << ", ";
    }
}