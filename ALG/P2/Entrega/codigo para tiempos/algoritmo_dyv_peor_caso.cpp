#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int enteroEnSuPosicion(vector<int> &v) {
    int i_centro = v.size() / 2;
    int dif_centro = v[i_centro] - i_centro;
    int i_izqda = 0, i_dcha = v.size() - 1;
    bool puede_estar = true;

    while (i_izqda <= i_dcha && puede_estar) {
        if (dif_centro > 0){
            i_dcha = i_centro - 1;
        }
        else if (dif_centro < 0){
            if(i_izqda < v[i_izqda])
                puede_estar = false;
            else    
                i_izqda = i_centro + 1;
        }
        else
            return i_centro;

        i_centro = (i_izqda + i_dcha) / 2;
        dif_centro = v[i_centro] - i_centro;
    }
    return -1;
}

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        cerr << "Error en la llamada. Formato correcto: ./ejecutable <num_elementos>" << endl;
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]); // Tamanio del vector
    vector<int> v(n);
    for (long long int i=0; i < n; i++)
	    v[i] = i+1;
 
 
    auto inicio = clock();
    for (int i=0; i < 100000; i++)
        int res = enteroEnSuPosicion(v);
    auto fin = clock();
    auto tiempo = (fin - inicio) / 100000.0;
    //cout << res << endl;
    cout  << n << " " << (double)(tiempo) / CLOCKS_PER_SEC << endl;
    return 0;

}
