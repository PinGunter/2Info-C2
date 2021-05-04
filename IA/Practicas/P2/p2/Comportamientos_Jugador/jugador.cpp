#include "../Comportamientos_Jugador/jugador.hpp"
#include "motorlib/util.h"

#include <iostream>
#include <cmath>
#include <set>
#include <stack>
#include <queue>


// Este es el método principal que se piden en la practica.
// Tiene como entrada la información de los sensores y devuelve la acción a realizar.
// Para ver los distintos sensores mirar fichero "comportamiento.hpp"
Action ComportamientoJugador::think(Sensores sensores) {
	Action accion = actIDLE;

	//actualiza la variable actual
	actual.fila        = sensores.posF;
	actual.columna     = sensores.posC;
	actual.orientacion = sensores.sentido;
	actual.bikini = false;
	actual.zapatillas = false;

	cout << "Fila: " << actual.fila << endl;
	cout << "Col : " << actual.columna << endl;
	cout << "Ori : " << actual.orientacion << endl;

	// Capturo los destinos
	cout << "sensores.num_destinos : " << sensores.num_destinos << endl;
	objetivos.clear();
	for (int i=0; i<sensores.num_destinos; i++){
		estado aux;
		aux.fila = sensores.destino[2*i];
		aux.columna = sensores.destino[2*i+1];
		objetivos.push_back(aux);
	}

	//Si no hay plan construimos uno
	if (!hayPlan){
		hayPlan = pathFinding(sensores.nivel, actual, objetivos, plan);
	}

	if (hayPlan and plan.size() > 0){
		accion = plan.front();
		plan.erase(plan.begin());	
	} else{
		cout << "No tengo planes" << endl;
	}

	// --- PARTE DEL TUTORIAL ---- \\\ 

	// unsigned char contenidoCasilla;
	// mapaResultado[sensores.posF][sensores.posC] = sensores.terreno[0];

	// switch (sensores.sentido){
	// 	case norte: contenidoCasilla = mapaResultado[sensores.posF-1][sensores.posC];
	// 		break;
	// 	case este: contenidoCasilla = mapaResultado[sensores.posF][sensores.posC+1];
	// 		break;	
	// 	case sur: contenidoCasilla = mapaResultado[sensores.posF+1][sensores.posC];
	// 		break;
	// 	case oeste: contenidoCasilla = mapaResultado[sensores.posF][sensores.posC-1];
	// 		break;
	// }

	// if (sensores.terreno[2] == 'P' or sensores.terreno[2] == 'M'
	// 	or sensores.superficie[2]== 'a'){
	// 		accion = actTURN_R;
	// 	}
	// else{
	// 	accion = actFORWARD;
	// }

	// bool hay_plan = pathFinding (sensores.nivel, actual, objetivos, plan);

  return accion;
}


// Llama al algoritmo de busqueda que se usara en cada comportamiento del agente
// Level representa el comportamiento en el que fue iniciado el agente.
bool ComportamientoJugador::pathFinding (int level, const estado &origen, const list<estado> &destino, list<Action> &plan){
	switch (level){
		estado un_objetivo;
		case 0: cout << "Demo\n";
						un_objetivo = objetivos.front();
						cout << "fila: " << un_objetivo.fila << " col:" << un_objetivo.columna << endl;
			      return pathFinding_Profundidad(origen,un_objetivo,plan);
						break;

		case 1: cout << "Optimo numero de acciones\n";
			      // Incluir aqui la llamada al busqueda en anchura
						un_objetivo = objetivos.front();
						cout << "fila: " << un_objetivo.fila << " col:" << un_objetivo.columna << endl;
					return pathFinding_Anchura(origen,un_objetivo,plan);
						break;
		case 2: cout << "Optimo en coste 1 Objetivo\n";
						un_objetivo = objetivos.front();
						cout << "fila: " << un_objetivo.fila << " col:" << un_objetivo.columna << endl;
						return pathFinding_CosteUniforme(origen,un_objetivo,plan);
						break;
		case 3: cout << "Optimo en coste 3 Objetivos\n";
						// Incluir aqui la llamada al algoritmo de busqueda para 3 objetivos
						cout << "No implementado aun\n";
						break;
		case 4: cout << "Algoritmo de busqueda usado en el reto\n";
						// Incluir aqui la llamada al algoritmo de busqueda usado en el nivel 2
						cout << "No implementado aun\n";
						break;
	}
	return false;
}

//---------------------- Implementación de la busqueda en profundidad ---------------------------

// Dado el codigo en caracter de una casilla del mapa dice si se puede
// pasar por ella sin riegos de morir o chocar.
bool EsObstaculo(unsigned char casilla){
	if (casilla=='P' or casilla=='M')
		return true;
	else
	  return false;
}


// Comprueba si la casilla que hay delante es un obstaculo. Si es un
// obstaculo devuelve true. Si no es un obstaculo, devuelve false y
// modifica st con la posición de la casilla del avance.
bool ComportamientoJugador::HayObstaculoDelante(estado &st){
	int fil=st.fila, col=st.columna;

  // calculo cual es la casilla de delante del agente
	switch (st.orientacion) {
		case 0: fil--; break;
		case 1: col++; break;
		case 2: fil++; break;
		case 3: col--; break;
	}

	// Compruebo que no me salgo fuera del rango del mapa
	if (fil<0 or fil>=mapaResultado.size()) return true;
	if (col<0 or col>=mapaResultado[0].size()) return true;

	// Miro si en esa casilla hay un obstaculo infranqueable
	if (!EsObstaculo(mapaResultado[fil][col])){
		// No hay obstaculo, actualizo el parametro st poniendo la casilla de delante.
    st.fila = fil;
		st.columna = col;
		return false;
	}
	else{
	  return true;
	}
}




struct nodo{
	estado st;
	int coste;
	list<Action> secuencia;
};

struct ComparaEstados{
	bool operator()(const estado &a, const estado &n) const{
		if ((a.fila > n.fila) or (a.fila == n.fila and a.columna > n.columna) or
	      (a.fila == n.fila and a.columna == n.columna and a.orientacion > n.orientacion))
			return true;
		else
			return false;
	}
};
struct ComparaNodos {
    bool operator()(const nodo &uno, const nodo &otro) { //operador para la priority queue
        return uno.coste < otro.coste;
    }
};

bool operator==(const estado & uno, const estado & otro){
    return
        uno.zapatillas == otro.zapatillas &&
        uno.bikini == otro.bikini &&
        uno.fila == otro.fila &&
        uno.columna == otro.columna &&
        uno.orientacion == otro.orientacion;
}

bool operator==(const nodo & uno, const nodo & otro){
    return
            uno.st == otro.st &&
            uno.secuencia == otro.secuencia &&
            uno.coste == otro.coste;
}

multiset<nodo,ComparaNodos>::const_iterator buscaNodo(const multiset<nodo,ComparaNodos> & abiertos,const nodo & n){
    for (auto it = abiertos.begin(); it != abiertos.end(); ++it){
        if (*(it) == n){
            return it;
        }
    }
    return abiertos.end();
}
// Implementación de la busqueda en profundidad.
// Entran los puntos origen y destino y devuelve la
// secuencia de acciones en plan, una lista de acciones.
bool ComportamientoJugador::pathFinding_Profundidad(const estado &origen, const estado &destino, list<Action> &plan) {
	//Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado,ComparaEstados> Cerrados; // Lista de Cerrados
	stack<nodo> Abiertos;								 // Lista de Abiertos

  nodo current;
	current.st = origen;
	current.secuencia.empty();

	Abiertos.push(current);

  while (!Abiertos.empty() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){

		Abiertos.pop();
		Cerrados.insert(current.st);

		// Generar descendiente de girar a la derecha
		nodo hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;
		if (Cerrados.find(hijoTurnR.st) == Cerrados.end()){
			hijoTurnR.secuencia.push_back(actTURN_R);
			Abiertos.push(hijoTurnR);

		}

		// Generar descendiente de girar a la izquierda
		nodo hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;
		if (Cerrados.find(hijoTurnL.st) == Cerrados.end()){
			hijoTurnL.secuencia.push_back(actTURN_L);
			Abiertos.push(hijoTurnL);
		}

		// Generar descendiente de avanzar
		nodo hijoForward = current;
		if (!HayObstaculoDelante(hijoForward.st)){
			if (Cerrados.find(hijoForward.st) == Cerrados.end()){
				hijoForward.secuencia.push_back(actFORWARD);
				Abiertos.push(hijoForward);
			}
		}

		// Tomo el siguiente valor de la Abiertos
		if (!Abiertos.empty()){
			current = Abiertos.top();
		}
	}

  cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna){
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else {
		cout << "No encontrado plan\n";
	}


	return false;
}







// Sacar por la consola la secuencia del plan obtenido
void ComportamientoJugador::PintaPlan(list<Action> plan) {
	auto it = plan.begin();
	while (it!=plan.end()){
		if (*it == actFORWARD){
			cout << "A ";
		}
		else if (*it == actTURN_R){
			cout << "D ";
		}
		else if (*it == actTURN_L){
			cout << "I ";
		}
		else {
			cout << "- ";
		}
		it++;
	}
	cout << endl;
}


// Funcion auxiliar para poner a 0 todas las casillas de una matriz
void AnularMatriz(vector<vector<unsigned char> > &m){
	for (int i=0; i<m[0].size(); i++){
		for (int j=0; j<m.size(); j++){
			m[i][j]=0;
		}
	}
}


// Pinta sobre el mapa del juego el plan obtenido
void ComportamientoJugador::VisualizaPlan(const estado &st, const list<Action> &plan){
  AnularMatriz(mapaConPlan);
	estado cst = st;

	auto it = plan.begin();
	while (it!=plan.end()){
		if (*it == actFORWARD){
			switch (cst.orientacion) {
				case 0: cst.fila--; break;
				case 1: cst.columna++; break;
				case 2: cst.fila++; break;
				case 3: cst.columna--; break;
			}
			mapaConPlan[cst.fila][cst.columna]=1;
		}
		else if (*it == actTURN_R){
			cst.orientacion = (cst.orientacion+1)%4;
		}
		else {
			cst.orientacion = (cst.orientacion+3)%4;
		}
		it++;
	}
}



int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}


/* ========== BUSQUEDA EN ANCHURA =========== *\*/
bool ComportamientoJugador::pathFinding_Anchura(const estado &origen, const estado &destino, list<Action> &plan) {
	//Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado,ComparaEstados> Cerrados; // Lista de Cerrados
	queue<nodo> Abiertos;				 // Cola de Abiertos

  	nodo current;
	current.st = origen;
	current.secuencia.empty();

	Abiertos.push(current);

  while (!Abiertos.empty() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){

		Abiertos.pop();
		Cerrados.insert(current.st);

		// Generar descendiente de girar a la derecha
		nodo hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;
		if (Cerrados.find(hijoTurnR.st) == Cerrados.end()){
			hijoTurnR.secuencia.push_back(actTURN_R);
			Abiertos.push(hijoTurnR);

		}

		// Generar descendiente de girar a la izquierda
		nodo hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;
		if (Cerrados.find(hijoTurnL.st) == Cerrados.end()){
			hijoTurnL.secuencia.push_back(actTURN_L);
			Abiertos.push(hijoTurnL);
		}

		// Generar descendiente de avanzar
		nodo hijoForward = current;
		if (!HayObstaculoDelante(hijoForward.st)){
			if (Cerrados.find(hijoForward.st) == Cerrados.end()){
				hijoForward.secuencia.push_back(actFORWARD);
				Abiertos.push(hijoForward);
			}
		}

		// Tomo el siguiente valor de la Abiertos
		if (!Abiertos.empty()){
			current = Abiertos.front();
		}
	}

  cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna){
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else {
		cout << "No encontrado plan\n";
	}


	return false;
}

int ComportamientoJugador::determinarPeso(estado & actual, estado &siguiente){
	char casilla_actual = mapaResultado[actual.fila][actual.columna];
	char casilla_siguiente = mapaResultado[siguiente.fila][siguiente.columna];
	int peso = 0;
	//bikini - k
	//zapatillas - d
	//bosque - b |--
	//agua - a	 |	|- pesos mas grandes
	//arena - t  |--

	if (casilla_siguiente == 'K') {
        actual.bikini = true;
        actual.zapatillas = false; //solo se permite un objeto;
    }
	if (casilla_siguiente == 'D') {
        actual.zapatillas = true;
        actual.bikini = false; //solo se permite un objeto;
    }


	if  (siguiente.orientacion != actual.orientacion) { // si se rota
        if (casilla_actual == 'A'){ //Estamos en agua
            if (actual.bikini){
                peso += GIRO_BIKINI;
            } else{
                peso += GIRO_AGUA;
            }
        } else if (casilla_actual == 'B') { //bosque
            if (actual.zapatillas){
                peso += GIRO_ZAPATILLAS;
            } else{
                peso += GIRO_BOSQUE;
            }
        } else if (casilla_actual == 'T'){
            peso += GIRO_ARENA;
        } else{
            peso++;     //una casilla "normal"
        }
	} else{ //estamos avanzando hacia delante
        if (casilla_actual == 'A'){ //Estamos en agua
            if (actual.bikini){
                peso += AVANZA_BIKINI;
            } else{
                peso += AVANZA_AGUA;
            }
        } else if (casilla_actual == 'B') { //bosque
            if (actual.zapatillas){
                peso += AVANZA_ZAPATILLAS;
            } else{
                peso += AVANZA_BOSQUE;
            }
        } else if (casilla_actual == 'T'){
            peso += AVANZA_ARENA;
        } else{
            peso++;     //una casilla "normal"
        }
	}

	return peso;

}

int ComportamientoJugador::calculaDistanciaManhattan(const estado & origen, const estado & destino){
	int x = abs(destino.fila - origen.fila);
	int y = abs(destino.columna - origen.columna);
	return (x+y);
}

bool ComportamientoJugador::pathFinding_CosteUniforme(const estado &origen, const estado &destino, list<Action> &plan) {
	cout << "Calculando plan costo uniforme" << endl;
	plan.clear();
	multiset<nodo,ComparaNodos> abiertos; //no podemos usar una priority queue porque no podremos buscar en ella un elemento :(
	set<estado,ComparaEstados> cerrados;

	nodo current;
	current.st = origen;
	current.secuencia.empty();
	abiertos.insert(current);

	while (!abiertos.empty() and (current.st.fila != destino.fila or current.st.columna != destino.columna)){
        abiertos.erase(abiertos.begin());
        cerrados.insert(current.st);

        //expandimos hijo derecho
        nodo hijo_derecho = current;
        hijo_derecho.st.orientacion = (hijo_derecho.st.orientacion +1)%4;
        //si no esta en cerrados:
        if (cerrados.find(hijo_derecho.st) == cerrados.end()){
            hijo_derecho.coste += determinarPeso(current.st,hijo_derecho.st); //calculamos el peso de pasar al hijo derecho
            auto it = buscaNodo(abiertos,hijo_derecho);
            if (it != abiertos.cend()){
                if (hijo_derecho.coste <= it->coste){
                    abiertos.erase(it);
                    hijo_derecho.secuencia.push_back(actTURN_R);
                    abiertos.insert(hijo_derecho);
                }
            }else {
                hijo_derecho.secuencia.push_back(actTURN_R);
                abiertos.insert(hijo_derecho);
            }
        }

        //expandimos hijo izquierdo
        nodo hijo_izquierdo = current;
        hijo_izquierdo.st.orientacion = (hijo_izquierdo.st.orientacion +3)%4;
        //si no esta en cerrados:
        if (cerrados.find(hijo_izquierdo.st) == cerrados.end()){
            hijo_izquierdo.coste += determinarPeso(current.st,hijo_izquierdo.st); //calculamos el peso de pasar al hijo izquierdo
            auto it = buscaNodo(abiertos,hijo_izquierdo);
            if (it != abiertos.cend()){
                if (hijo_izquierdo.coste <= it->coste){
                    abiertos.erase(it);
                    hijo_izquierdo.secuencia.push_back(actTURN_L);
                    abiertos.insert(hijo_izquierdo);
                }
            }else {
                hijo_izquierdo.secuencia.push_back(actTURN_L);
                abiertos.insert(hijo_izquierdo);
            }
        }

        //expandimos hijo de ir hacia delante
        nodo hijo_avanzar = current;

        if (!HayObstaculoDelante(hijo_avanzar.st)){
            if (cerrados.find(hijo_avanzar.st) == cerrados.end()){
                hijo_avanzar.coste += determinarPeso(current.st, hijo_avanzar.st);
                auto it = buscaNodo(abiertos,hijo_avanzar);
                if (it != abiertos.cend()){
                    if (hijo_avanzar.coste <= it->coste){
                        abiertos.erase(it);
                        hijo_avanzar.secuencia.push_back(actFORWARD);
                        abiertos.insert(hijo_avanzar);
                    }
                }else {
                    hijo_avanzar.secuencia.push_back(actFORWARD);
                    abiertos.insert(hijo_avanzar);
                }
            }
        }

        if (!abiertos.empty()){
            current = *(abiertos.begin());
        }
	}
    cout << "Terminada la busqueda\n";

   // if (current.st.fila == destino.fila and current.st.columna == destino.columna){
        cout << "Cargando el plan\n";
        plan = current.secuencia;
        cout << "Longitud del plan: " << plan.size() << endl;
        PintaPlan(plan);
        // ver el plan en el mapa
        VisualizaPlan(origen, plan);
        return true;
//    }
//    else {
//        cout << "No encontrado plan\n";
//    }


    return false;

}