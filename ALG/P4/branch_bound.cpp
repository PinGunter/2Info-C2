#include <iostream>
#include <queue>
#include <vector>

using namespace std;

double uniforme() //Genera un número uniformemente distribuido en el
//intervalo [0,1) a partir de uno de los generadores
//disponibles en C.
{
    int t = rand();
    double f = ((double)RAND_MAX+1.0);
    return (double)t/f;
}

void generaPesos(vector<double> & w, int n) {

    srand(time(0));
    for (int i = 0; i < n; i++) {
        double u=uniforme();
        w.push_back(u);
    }
}

struct Nodo{
    vector<int> indice_recipientes;
    vector<double> pesos;
    int num_objetos_asignados;
    int num_recipientes;
};

struct ComparaNodos{
    bool operator()(const Nodo & a, const Nodo & n)const{
        if(a.num_recipientes > n.num_recipientes) 
            return true;
        else
            return false;
    }
};


void BranchAndBound(const vector<double> & objetos, double n, int r, vector<double> & pesos_salida, int & n_recipientes, vector<int> & solucion_salida, int & podas_salida, unsigned long long & nodos_explorados_salida, int & tamanio_salida){
    priority_queue<Nodo, vector<Nodo>, ComparaNodos> Abiertos;
    Nodo current;
    current.num_objetos_asignados = 0;
    current.num_recipientes = 1;
    current.indice_recipientes.resize(n);
    current.pesos.push_back(0);
    current.pesos.resize(n);
    int cota_global = n;
    bool primera_iteracion = true;
    bool salir;
    bool bandera = true;
    int n_podas = 0;
    int nodos_explorados = 0;
    int max_abiertos = 1;

    Abiertos.push(current);

    while(!Abiertos.empty() && current.num_objetos_asignados < n){
        if(max_abiertos < Abiertos.size())
             max_abiertos = Abiertos.size();
        Abiertos.pop();
        ++nodos_explorados;
        
        for(int i=0; i<current.num_recipientes; ++i){
            for(int j=0; j<n; ++j){
                Nodo hijoRecipienteUsado = current;
                hijoRecipienteUsado.num_objetos_asignados++;
                if(hijoRecipienteUsado.indice_recipientes[j] == 0){
                    hijoRecipienteUsado.indice_recipientes[j] = i+1;
                    hijoRecipienteUsado.pesos[i] += objetos[j];
                
                    if(hijoRecipienteUsado.pesos[i] <= r && hijoRecipienteUsado.num_recipientes < cota_global){
                        if(hijoRecipienteUsado.num_objetos_asignados == n && hijoRecipienteUsado.num_recipientes < cota_global){    //COTA
                            cota_global = hijoRecipienteUsado.num_recipientes;
                            Abiertos.push(hijoRecipienteUsado);
                        }
                        else if(hijoRecipienteUsado.num_objetos_asignados < n)
                            Abiertos.push(hijoRecipienteUsado);
                        else
                            ++n_podas;    
                    }
                    else
                        ++n_podas;
                }
            }
        }

        if(!primera_iteracion){
            Nodo hijoNuevoRecipiente = current;
            hijoNuevoRecipiente.pesos[hijoNuevoRecipiente.num_recipientes] = 0;
            salir = false;
            for(int i=0; i<n && !salir; ++i){
                if(hijoNuevoRecipiente.indice_recipientes[i] == 0){
                    salir = true;
                    hijoNuevoRecipiente.indice_recipientes[i] = hijoNuevoRecipiente.num_recipientes+1;
                    hijoNuevoRecipiente.pesos[hijoNuevoRecipiente.num_recipientes] += objetos[i];
                }
            }
            ++hijoNuevoRecipiente.num_objetos_asignados;
            ++hijoNuevoRecipiente.num_recipientes;
            if(hijoNuevoRecipiente.pesos[hijoNuevoRecipiente.num_recipientes-1] <= r){
                if(hijoNuevoRecipiente.num_objetos_asignados == n && (hijoNuevoRecipiente.num_recipientes < cota_global || bandera)){
                    bandera = false;
                    cota_global = hijoNuevoRecipiente.num_recipientes;
                    Abiertos.push(hijoNuevoRecipiente);
                }
                else if(hijoNuevoRecipiente.num_objetos_asignados < n)
                    Abiertos.push(hijoNuevoRecipiente);
                else
                    ++n_podas;    
            }
            else
                ++n_podas;
        }
        primera_iteracion=false;
        if(!Abiertos.empty())
            current = Abiertos.top();
    
    }

    pesos_salida = current.pesos;
    n_recipientes = current.num_recipientes;
    solucion_salida = current.indice_recipientes;
}


int main(int argc, char **argv){
    time_t ini, fin;
    //double aMano [] = {0.0369008 , 0.884313,  0.224251 , 0.445077,  0.28718 , 0.148414,  0.185183,  0.842165 , 0.898367,  0.582267};
    vector<double> objetos;
    generaPesos(objetos, atoi(argv[1]));
    vector<double> pesos;
    int n_recipientes;
    const double R = 1;
    vector<int> solucion;
    solucion.resize(objetos.size());
    int podas, tamanio;
    unsigned long long nodos;
    
    for(int i=0; i<objetos.size(); ++i)
        cout << objetos[i] << " (" << i+1 << "),\t";

    ini = clock();
    BranchAndBound(objetos, objetos.size(), R, pesos, n_recipientes, solucion, podas, nodos, tamanio);
    fin = clock();
    
    cout << endl;
    for(int i=0; i<solucion.size(); ++i){
        cout << solucion[i] << "\t";
    }
    cout << endl;
    for(int i=0; i<objetos.size(); i++){
        cout << "Recipiente " << i+1 << ": ";
        for(int j=0; j<objetos.size(); j++){
            if(solucion[j] == (i+1))
                cout << objetos[j] << " (" << j+1 << "),\t";
        }
        cout << endl;
    }

    cout << endl << endl << endl 
         << "TIEMPO: " << ((double)(fin-ini))/CLOCKS_PER_SEC << endl 
         << "TAMAÑO MAX COLA: " << tamanio << endl
         << "NODOS EXPLORADOS: " << nodos << endl
         << "NÚMERO DE PODAS: " << podas << endl;

}
