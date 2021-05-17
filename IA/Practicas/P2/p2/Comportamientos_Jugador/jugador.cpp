#include "../Comportamientos_Jugador/jugador.hpp"
#include "motorlib/util.h"

#include <iostream>
#include <cmath>
#include <set>
#include <stack>
#include <queue>
#include <unistd.h>


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

    actualizarMapa(actual, sensores);


	// Capturo los objetivos
	cout << "sensores.num_destinos : " << sensores.num_destinos << endl;
	objetivos.clear();
	for (int i=0; i<sensores.num_destinos; i++){
		estado aux;
		aux.fila = sensores.destino[2*i];
		aux.columna = sensores.destino[2*i+1];
		objetivos.push_back(aux);
	}

	//Si no hay plan construimos uno
	if (sensores.nivel != 4){
        if (!hayPlan){
            hayPlan = pathFinding(sensores.nivel, actual, objetivos, plan);
        }
	} else{
        if (!hayPlan or haActualizadoMapa(actual)){
            hayPlan = pathFinding(sensores.nivel, actual, objetivos, plan);
        }
	}

	if (hayPlan and plan.size() > 0){
		accion = plan.front();
		plan.erase(plan.begin());
	} else{
		cout << "No tengo planes" << endl;
	}
	if (sensores.nivel == 4) {
        if (sensores.terreno[2] == 'P' or sensores.terreno[2] == 'M'
            or sensores.superficie[2]== 'a'){
            accion = actTURN_R;
        }
    }


	// --- PARTE DEL TUTORIAL ---- \\\

	// unsigned char contenidoCasilla;
    //	 mapaResultado[sensores.posF][sensores.posC] = sensores.terreno[0];

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
    estado un_objetivo;
    list<estado>::const_iterator it = destino.cbegin();
    switch (level){
        case 0: cout << "Demo\n";
						un_objetivo = destino.front();
						cout << "fila: " << un_objetivo.fila << " col:" << un_objetivo.columna << endl;
			      return pathFinding_Profundidad(origen,un_objetivo,plan);
						break;

		case 1: cout << "Optimo numero de acciones\n";
			      // Incluir aqui la llamada al busqueda en anchura
						un_objetivo = destino.front();
						cout << "fila: " << un_objetivo.fila << " col:" << un_objetivo.columna << endl;
					return pathFinding_Anchura(origen,un_objetivo,plan);
						break;
		case 2: cout << "Optimo en coste 1 Objetivo\n";
						un_objetivo = destino.front();
						cout << "fila: " << un_objetivo.fila << " col:" << un_objetivo.columna << endl;
						return pathFinding_CosteUniforme(origen,un_objetivo,plan);
						break;
		case 3: cout << "Optimo en coste 3 Objetivos\n";
						cout << "Objetivo A:\nfila: " << (*it).fila << " col: " << (*it).columna << endl;
						++it;
                        cout << "Objetivo B:\nfila: " << (*it).fila << " col: " << (*it).columna << endl;
                        ++it;
                        cout << "Objetivo C:\nfila: " << (*it).fila << " col: " << (*it).columna << endl;
                        return pathFinding_3_objetivos(origen,destino,plan);
                        break;
		case 4: cout << "Algoritmo de busqueda usado en el reto\n";
						return pathFinding_Reto(origen,destino, plan);
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

bool operator<(const nodo &uno, const nodo &otro) { //operador para la priority queue
    if ((otro.coste < uno.coste) or
        ((otro.coste == uno.coste) and (otro.st.objetivos.size() < uno.st.objetivos.size())))
        return  true;
    else return false;
}

bool operator==(const estado & uno, const estado & otro){
    return
            uno.zapatillas == otro.zapatillas &&
            uno.bikini == otro.bikini &&
            uno.fila == otro.fila &&
            uno.columna == otro.columna &&
            uno.orientacion == otro.orientacion &&
            uno.objetivos == otro.objetivos;
}

bool operator==(const nodo & uno, const nodo & otro){
    return
            uno.st == otro.st &&
            uno.secuencia == otro.secuencia &&
            uno.coste == otro.coste;
}

bool operator<(const list<estado> & uno, const list<estado> & otro){
    for (auto it = uno.cbegin(), et = otro.cbegin(); it != uno.cend() && et!=otro.cend(); ++it, ++et){
        if (((*it).fila > (*et).fila) or ((*it).fila == (*et).fila and (*it).columna > (*et).columna)){
            return true;
        }
    }
    return false;
}

bool estadoMenorQueOtro(const estado & uno, const estado & otro){   //funcion de comparacion para sort
    if ((uno.fila < otro.fila) or (uno.fila == otro.fila and uno.columna < otro.columna))
        return true;
    else return false;
}

struct ComparaEstados{
	bool operator()(const estado &a, const estado &n) const{
		if ((a.fila > n.fila) or (a.fila == n.fila and a.columna > n.columna) or
	      (a.fila == n.fila and a.columna == n.columna and a.orientacion > n.orientacion)
	      or (a.fila == n.fila and a.columna == n.columna and a.orientacion == n.orientacion and a.zapatillas > n.zapatillas)
             or (a.fila == n.fila and a.columna == n.columna and a.orientacion == n.orientacion and a.zapatillas == n.zapatillas and a.bikini > n.bikini)
                or (a.fila == n.fila and a.columna == n.columna and a.orientacion == n.orientacion and a.zapatillas == n.zapatillas and a.bikini == n.bikini and a.objetivos.size() < n.objetivos.size())
                    or (a.fila == n.fila and a.columna == n.columna and a.orientacion == n.orientacion and a.zapatillas == n.zapatillas and a.bikini == n.bikini and a.objetivos.size() == n.objetivos.size() and a.objetivos < n.objetivos))
			return true;
		else
			return false;
	}
};


void ComportamientoJugador::actualizarItems(estado &actual) {
    char casilla_actual = mapaResultado[actual.fila][actual.columna];

    if (casilla_actual == 'K') {
        actual.bikini = true;
        actual.zapatillas = false; //solo se permite un objeto;
    }
    if (casilla_actual == 'D') {
        actual.zapatillas = true;
        actual.bikini = false; //solo se permite un objeto;
    }
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
//	char casilla_siguiente = mapaResultado[siguiente.fila][siguiente.columna];
	int peso = 0;
	//bikini - k
	//zapatillas - d
	//bosque - b |--
	//agua - a	 |	|- pesos mas grandes
	//arena - t  |--

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


void actualizaObjetivos(estado & actual){
    list<estado>::iterator a_borrar = actual.objetivos.end();
    for (auto it = actual.objetivos.begin(); it != actual.objetivos.end(); ++it){
        if (actual.fila == (*it).fila and actual.columna == (*it).columna){
            a_borrar = it;
        }
    }
    if (a_borrar != actual.objetivos.end())
        actual.objetivos.erase(a_borrar);
}

bool ComportamientoJugador::pathFinding_CosteUniforme(const estado &origen, const estado &destino, list<Action> &plan) {
    cout << "Calculando plan costo uniforme" << endl;
    plan.clear();
    priority_queue<nodo> abiertos;
    set<estado, ComparaEstados> cerrados;

    nodo current;
    current.st = origen;
    current.secuencia.empty();
    abiertos.push(current);

    while (!abiertos.empty() and (current.st.fila != destino.fila or current.st.columna != destino.columna)) {
        while (cerrados.find(current.st) != cerrados.end()){
            abiertos.pop();
            current = abiertos.top();
        }
        cerrados.insert(current.st);

        //expandimos hijo derecho
        nodo hijo_derecho = current;
        hijo_derecho.st.orientacion = (hijo_derecho.st.orientacion + 1) % 4;
        //si no esta en cerrados:
        hijo_derecho.coste += determinarPeso(current.st,
                                             hijo_derecho.st); //calculamos el peso de pasar al hijo derecho
        if (cerrados.find(hijo_derecho.st) == cerrados.end()) {
            hijo_derecho.secuencia.push_back(actTURN_R);
            abiertos.push(hijo_derecho);
        }

        //expandimos hijo izquierdo
        nodo hijo_izquierdo = current;
        hijo_izquierdo.st.orientacion = (hijo_izquierdo.st.orientacion + 3) % 4;
        //si no esta en cerrados:
        hijo_izquierdo.coste += determinarPeso(current.st,
                                               hijo_izquierdo.st); //calculamos el peso de pasar al hijo izquierdo
        if (cerrados.find(hijo_izquierdo.st) == cerrados.end()) {
            hijo_izquierdo.secuencia.push_back(actTURN_L);
            abiertos.push(hijo_izquierdo);
        }

        //expandimos hijo de ir hacia delante
        nodo hijo_avanzar = current;

        hijo_avanzar.coste += determinarPeso(current.st, hijo_avanzar.st);
        if (!HayObstaculoDelante(hijo_avanzar.st)) {
            if (cerrados.find(hijo_avanzar.st) == cerrados.end()) {
                actualizarItems(hijo_avanzar.st);
                hijo_avanzar.secuencia.push_back(actFORWARD);
                abiertos.push(hijo_avanzar);
            }
        }

        if (!abiertos.empty()) {
            current = abiertos.top();
        }
    }
    cout << "Terminada la busqueda\n";

    if (current.st.fila == destino.fila and current.st.columna == destino.columna) {
        cout << "Cargando el plan\n";
        plan = current.secuencia;
        cout << "Longitud del plan: " << plan.size() << endl;
        PintaPlan(plan);
        // ver el plan en el mapa
        VisualizaPlan(origen, plan);
        return true;
    } else {
        cout << "No encontrado plan\n";
    }


    return false;

}

bool ComportamientoJugador::pathFinding_3_objetivos(const estado &origen, const list<estado> & destinos, list<Action> &plan){
    cout << "Calculando plan óptimo de batería con 3 objetivos" << endl;
    plan.clear();
    priority_queue<nodo> abiertos;
    set<estado, ComparaEstados> cerrados;

    nodo current;
    current.st = origen;
    current.coste = 0;
    current.secuencia.empty();
    for (auto e : destinos){        // inicializamos los destinos
        current.st.objetivos.push_back(e);
    }
    actualizaObjetivos(current.st); //comprobamos si esta en un objetivo al empezar el recorrido
    abiertos.push(current);


    while (!abiertos.empty() and (!current.st.objetivos.empty())) {
        while (cerrados.find(current.st) != cerrados.end()){
            abiertos.pop();
            current = abiertos.top();
        }
        cerrados.insert(current.st);

        //expandimos hijo derecho
        nodo hijo_derecho = current;
        hijo_derecho.st.orientacion = (hijo_derecho.st.orientacion + 1) % 4;
        //si no esta en cerrados
        hijo_derecho.coste += determinarPeso(current.st,
                                             hijo_derecho.st); //calculamos el peso de pasar al hijo derecho
        if (cerrados.find(hijo_derecho.st) == cerrados.end()) {
            hijo_derecho.secuencia.push_back(actTURN_R);
            abiertos.push(hijo_derecho);
        }

        //expandimos hijo izquierdo
        nodo hijo_izquierdo = current;
        hijo_izquierdo.st.orientacion = (hijo_izquierdo.st.orientacion + 3) % 4;
        //si no esta en cerrados:
        hijo_izquierdo.coste += determinarPeso(current.st,
                                               hijo_izquierdo.st); //calculamos el peso de pasar al hijo izquierdo
        if (cerrados.find(hijo_izquierdo.st) == cerrados.end()) {
            hijo_izquierdo.secuencia.push_back(actTURN_L);
            abiertos.push(hijo_izquierdo);
        }

        //expandimos hijo de ir hacia delante
        nodo hijo_avanzar = current;
        hijo_avanzar.coste += determinarPeso(current.st, hijo_avanzar.st);
        if (!HayObstaculoDelante(hijo_avanzar.st)) {
            actualizarItems(hijo_avanzar.st);
            actualizaObjetivos(hijo_avanzar.st);
            if (cerrados.find(hijo_avanzar.st) == cerrados.end()) {
                hijo_avanzar.secuencia.push_back(actFORWARD);
                abiertos.push(hijo_avanzar);
            }
        }

        if (!abiertos.empty()) {
            current = abiertos.top();
        }
    }
    cout << "Terminada la busqueda\n";

    if (current.st.objetivos.empty()) {
        cout << "Cargando el plan\n";
        plan = current.secuencia;
        cout << "Longitud del plan: " << plan.size() << endl;
        PintaPlan(plan);
        // ver el plan en el mapa
        VisualizaPlan(origen, plan);
        return true;
   } else {
       cout << "No encontrado plan\n";
   }


    return false;
}


void ComportamientoJugador::actualizarMapa(const estado & st, const Sensores & sensores){
    bool cambia = false;
    switch (st.orientacion){
        case 0:
            mapaResultado[st.fila-1][st.columna-1] = sensores.terreno[1];
            mapaResultado[st.fila-1][st.columna] = sensores.terreno[2];
            mapaResultado[st.fila-1][st.columna+1] = sensores.terreno[3];

            mapaResultado[st.fila-2][st.columna-2] = sensores.terreno[4];
            mapaResultado[st.fila-2][st.columna-1] = sensores.terreno[5];
            mapaResultado[st.fila-2][st.columna] = sensores.terreno[6];
            mapaResultado[st.fila-2][st.columna+1] = sensores.terreno[7];
            mapaResultado[st.fila-2][st.columna+2] = sensores.terreno[8];

            mapaResultado[st.fila-3][st.columna-3] = sensores.terreno[9];
            mapaResultado[st.fila-3][st.columna-2] = sensores.terreno[10];
            mapaResultado[st.fila-3][st.columna-1] = sensores.terreno[11];
            mapaResultado[st.fila-3][st.columna] = sensores.terreno[12];
            mapaResultado[st.fila-3][st.columna+1] = sensores.terreno[13];
            mapaResultado[st.fila-3][st.columna+2] = sensores.terreno[14];
            mapaResultado[st.fila-3][st.columna+3] = sensores.terreno[15];
            break;
        case 1:
            mapaResultado[st.fila-1][st.columna+1] = sensores.terreno[1];
            mapaResultado[st.fila][st.columna+1] = sensores.terreno[2];
            mapaResultado[st.fila+1][st.columna+1] = sensores.terreno[3];

            mapaResultado[st.fila-2][st.columna+2] = sensores.terreno[4];
            mapaResultado[st.fila-1][st.columna+2] = sensores.terreno[5];
            mapaResultado[st.fila][st.columna+2] = sensores.terreno[6];
            mapaResultado[st.fila+1][st.columna+2] = sensores.terreno[7];
            mapaResultado[st.fila+2][st.columna+2] = sensores.terreno[8];

            mapaResultado[st.fila-3][st.columna+3] = sensores.terreno[9];
            mapaResultado[st.fila-2][st.columna+3] = sensores.terreno[10];
            mapaResultado[st.fila-1][st.columna+3] = sensores.terreno[11];
            mapaResultado[st.fila][st.columna+3] = sensores.terreno[12];
            mapaResultado[st.fila+1][st.columna+3] = sensores.terreno[13];
            mapaResultado[st.fila+2][st.columna+3] = sensores.terreno[14];
            mapaResultado[st.fila+3][st.columna+3] = sensores.terreno[15];
            break;
        case 2:
            mapaResultado[st.fila+1][st.columna+1] = sensores.terreno[1];
            mapaResultado[st.fila+1][st.columna] = sensores.terreno[2];
            mapaResultado[st.fila+1][st.columna-1] = sensores.terreno[3];

            mapaResultado[st.fila+2][st.columna+2] = sensores.terreno[4];
            mapaResultado[st.fila+2][st.columna+1] = sensores.terreno[5];
            mapaResultado[st.fila+2][st.columna] = sensores.terreno[6];
            mapaResultado[st.fila+2][st.columna-1] = sensores.terreno[7];
            mapaResultado[st.fila+2][st.columna-2] = sensores.terreno[8];

            mapaResultado[st.fila+3][st.columna+3] = sensores.terreno[9];
            mapaResultado[st.fila+3][st.columna+2] = sensores.terreno[10];
            mapaResultado[st.fila+3][st.columna+1] = sensores.terreno[11];
            mapaResultado[st.fila+3][st.columna] = sensores.terreno[12];
            mapaResultado[st.fila+3][st.columna-1] = sensores.terreno[13];
            mapaResultado[st.fila+3][st.columna-2] = sensores.terreno[14];
            mapaResultado[st.fila+3][st.columna-3] = sensores.terreno[15];
            break;
        case 3:
            mapaResultado[st.fila+1][st.columna-1] = sensores.terreno[1];
            mapaResultado[st.fila][st.columna-1] = sensores.terreno[2];
            mapaResultado[st.fila-1][st.columna-1] = sensores.terreno[3];

            mapaResultado[st.fila+2][st.columna-2] = sensores.terreno[4];
            mapaResultado[st.fila+1][st.columna-2] = sensores.terreno[5];
            mapaResultado[st.fila][st.columna-2] = sensores.terreno[6];
            mapaResultado[st.fila-1][st.columna-2] = sensores.terreno[7];
            mapaResultado[st.fila-2][st.columna-2] = sensores.terreno[8];

            mapaResultado[st.fila+3][st.columna-3] = sensores.terreno[9];
            mapaResultado[st.fila+2][st.columna-3] = sensores.terreno[10];
            mapaResultado[st.fila+1][st.columna-3] = sensores.terreno[11];
            mapaResultado[st.fila][st.columna-3] = sensores.terreno[12];
            mapaResultado[st.fila-1][st.columna-3] = sensores.terreno[13];
            mapaResultado[st.fila-2][st.columna-3] = sensores.terreno[14];
            mapaResultado[st.fila-3][st.columna-3] = sensores.terreno[15];
            break;
    }
}

bool ComportamientoJugador::haActualizadoMapa(const estado &st) {
    bool ha_cambiado = false;
    switch (st.orientacion){
        case 0:
            ha_cambiado = mapaResultado[st.fila-3][st.columna-3] == '?' or mapaResultado[st.fila-3][st.columna] == '?' or mapaResultado[st.fila-3][st.columna+3] == '?';
            break;
        case 1:
            ha_cambiado = mapaResultado[st.fila-3][st.columna+3] == '?' or mapaResultado[st.fila][st.columna+3] == '?' or mapaResultado[st.fila+3][st.columna+3] == '?';
            break;

        case 2:
            ha_cambiado = mapaResultado[st.fila+3][st.columna+3] == '?' or mapaResultado[st.fila+3][st.columna] == '?' or mapaResultado[st.fila+3][st.columna-3] == '?';
            break;

        case 3:
            ha_cambiado = mapaResultado[st.fila+3][st.columna-3] == '?' or mapaResultado[st.fila][st.columna-3] == '?' or mapaResultado[st.fila-3][st.columna-3] == '?';
            break;
    }

    return ha_cambiado;
}


bool ComportamientoJugador::pathFinding_Reto(const estado &origen, const list <estado> &destinos, list <Action> &plan) {
    return pathFinding_CosteUniforme(origen,destinos.front(),plan);

}

