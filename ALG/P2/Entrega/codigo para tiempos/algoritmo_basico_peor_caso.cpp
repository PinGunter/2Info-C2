#include <iostream>
#include <vector>
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
    vector<int> v(n);
    for (long long int i=0; i < n; i++)
	    v[i] = i+1;


    auto inicio = clock();
    for (int i=0; i < 1000; i++)
        int res = enteroEnSuPosicion(v);
    auto fin = clock();
    auto tiempo = (fin - inicio) / 1000.0;
    cout  << n << " " << (double)(tiempo) / CLOCKS_PER_SEC << endl;
    return 0;
}
