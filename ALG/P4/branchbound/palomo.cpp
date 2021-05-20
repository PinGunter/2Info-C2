#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/* bool ComparaVector(const vector<int> & a, const vector<int> & n){
    for(int i=0; i<a.size(); ++i){
        if(a[i] != n[i])
            return true;
    }
    return false;
} */

double uniforme() //Genera un nÃºmero uniformemente distribuido en el
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
            //|| (a.num_recipientes == n.num_recipientes && ComparaVector(a.indice_recipientes, n.indice_recipientes)))
            return true;
        else
            return false;
    }
};


void BranchAndBound(const vector<double> & objetos, double n, int r, vector<double> & pesos_salida, int & n_recipientes, vector<int> & solucion_salida){
    priority_queue<Nodo, vector<Nodo>, ComparaNodos> Abiertos;
    Nodo current;
    current.num_objetos_asignados = 0;
    current.num_recipientes = 1;
    current.indice_recipientes.resize(n);
    current.pesos.push_back(0);
    current.pesos.resize(n);
    int cota_global = n;

    Abiertos.push(current);

    while(!Abiertos.empty() && current.num_objetos_asignados < n && current.num_recipientes < cota_global){
        Abiertos.pop();

        for(int i=0; i<current.num_recipientes; ++i){
            for(int j=current.num_objetos_asignados; j<cota_global; ++j){
                Nodo hijoRecipienteUsado = current;
                hijoRecipienteUsado.num_objetos_asignados++;
                hijoRecipienteUsado.indice_recipientes[j] = i+1;
                hijoRecipienteUsado.pesos[i] += objetos[j];
                if(hijoRecipienteUsado.pesos[i] <= r){
                    if(hijoRecipienteUsado.num_objetos_asignados == n && hijoRecipienteUsado.num_recipientes < cota_global)
                        cota_global = hijoRecipienteUsado.num_recipientes;
                    Abiertos.push(hijoRecipienteUsado);
                }
            }
        }

        Nodo hijoNuevoRecipiente = current;
        hijoNuevoRecipiente.pesos[hijoNuevoRecipiente.num_recipientes-1] = 0;
        hijoNuevoRecipiente.pesos[hijoNuevoRecipiente.num_recipientes-1] += objetos[hijoNuevoRecipiente.num_objetos_asignados];
        hijoNuevoRecipiente.num_objetos_asignados++;
        hijoNuevoRecipiente.num_recipientes++;
        hijoNuevoRecipiente.indice_recipientes[hijoNuevoRecipiente.num_recipientes-1] = hijoNuevoRecipiente.num_recipientes;
        if(hijoNuevoRecipiente.num_objetos_asignados == n && hijoNuevoRecipiente.num_recipientes < cota_global)
            cota_global = hijoNuevoRecipiente.num_recipientes;
        Abiertos.push(hijoNuevoRecipiente);

        if(!Abiertos.empty())
            current = Abiertos.top();
    
    }

    pesos_salida = current.pesos;
    n_recipientes = current.num_recipientes;
    solucion_salida = current.indice_recipientes;
}


int main(){
    vector<double> objetos;
    generaPesos(objetos, 50);
    vector<double> pesos;
    int n_recipientes;
    const double R = 1;
    vector<int> solucion;
    solucion.resize(objetos.size());

    BranchAndBound(objetos, objetos.size(), R, pesos, n_recipientes, solucion);
    for(int i=0; i<solucion.size(); ++i){
        cout << solucion[i] << endl;
    }
    for(int i=1; i<=50; i++){
        cout << "Recipiente " << i << ": ";
        for(int j=0; j<objetos.size(); j++){
            if(solucion[j] == i)
                cout << objetos[solucion[j]] << " (" << j+1 << "),\t";
        }
        cout << endl;
    }

    cout << endl << endl << endl;

}