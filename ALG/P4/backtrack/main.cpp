#include "solucion.h"
#include <algorithm>
#include <fstream>
using namespace std;

int puntuaciones_random(int max) {  // Entre 0 y 2147483647
    return rand() % max + 1;
}

vector<int> generaParticipantes(int n, int m) {
    vector <int> p(n,0);
    int max = 2147483647; //las puntuaciones serán números reales entre 0 y 2147483647
    long long suma = 0;
    srand (time(NULL));
    if (!(m <= 0 || m > max))
        max = m;

    for (int i = 0; i < n; i++) {
        int u = puntuaciones_random(max);
        p[i] = u; //uniforme entre 1 y max
        suma += p[i];
    }

    if(suma % 2 != 0){ // Si la suma de todas las puntuaciones es impar, sumamos 1 al último elemento del array.
        p[n-1] += 1;
        suma++;
    }

    cout << "Suma: " << suma << endl;
    return p;

}


int main(int argc, char ** argv)
{
    int arg1, arg2;

    if(argc != 2 && argc != 3){
        cerr << "Error al introducir los argumentos. Use: ./binario <numero_personas> <maximo_puntuacion>" << endl;
        exit(-1);
    }
    if(argc == 3){
        arg2 = atoi(argv[2]);
    }
    arg1 = atoi(argv[1]);

    ofstream fichero_backtrack("salida_backtrack.txt",ofstream::app);
    ofstream fichero_fb("salida_fb.txt",ofstream::app);
//    int falso  [] = {20, 3, 2,1 };
    vector<int> p = generaParticipantes(arg1,arg2);
//    vector<int> p (falso,falso+4);
    sort(p.begin(),p.end());
    cout << "BACKTRACKING" << endl;
    print(p);
    Solucion bt(p);
    auto inicio_bt = clock();
    bt.equilibrarEquipos();
    auto tiempo_bt = clock() - inicio_bt;
    cout << "Suma equipo 1: " << sumaVector(bt.getVectorEquipo()) << endl;
    cout << "Suma equipo 2: " << bt.getTotal() - sumaVector(bt.getVectorEquipo()) << endl;
    cout << "TIEMPO: " << (double) tiempo_bt / CLOCKS_PER_SEC << endl;
    fichero_backtrack << arg1 << " " << (double) tiempo_bt / CLOCKS_PER_SEC << endl;

cout << "\nFUERZA BRUTA" << endl;
Solucion fb(p);
auto inicio_fb = clock();
fb.equilibrarEquipos_FB();
auto tiempo_fb = clock() - inicio_fb;
cout << "Suma equipo 1: " << sumaVector(fb.getVectorEquipo()) << endl;
cout << "Suma equipo 2: "<< fb.getTotal() - sumaVector(fb.getVectorEquipo()) << endl;
cout << "TIEMPO: " << (double) tiempo_fb / CLOCKS_PER_SEC << endl;
fichero_fb << arg1 << " " << (double) tiempo_fb / CLOCKS_PER_SEC << endl;


    fichero_backtrack.close(); //fichero_fb.close();
}
