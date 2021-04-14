#include <iostream>
#include <vector>
#include "generador.h"
using namespace std;

int enteroEnSuPosicion(vector<int> & v)
{
    int res = -1;
    for (int i=0; i < v.size() && res == -1; ++i)
        if (v[i] == i)
            res = i;
    return res;
}

int main(int argc, char const *argv[])
{
    if (argc != 2){
        cerr << "Error en la llamada. Formato correcto: ./ejecutable <num_elementos>" << endl;
        exit(EXIT_FAILURE); 
    }
    
    int n = atoi(argv[1]); // Tamanio del vector
    vector<int> v = generar_vector(n);

    //Mostramos los valores del vector
     cout << "Vector: ";
     for (auto e : v){ //
         cout << e << " ";
     }
     cout << endl;

    int res = enteroEnSuPosicion(v);

    if (res != -1){
    	cout << "Se cumple la condición con el elemento: " << res << endl;
    } else{
    	cout << "Ningún elemento cumple la condición " << endl;
    }
    return 0;
}
