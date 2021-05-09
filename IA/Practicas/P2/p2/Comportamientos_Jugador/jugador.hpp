#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

//defines con los pesos
#define GIRO_BIKINI 5
#define GIRO_ZAPATILLAS 1
#define GIRO_AGUA 500
#define GIRO_BOSQUE 3
#define GIRO_ARENA 2
#define AVANZA_AGUA 200
#define AVANZA_BOSQUE 100
#define AVANZA_BIKINI 10
#define AVANZA_ZAPATILLAS 15
#define AVANZA_ARENA 2

#include "comportamientos/comportamiento.hpp"

#include <list>

struct estado {
  int fila;
  int columna;
  int orientacion;
  bool bikini, zapatillas;
};

class ComportamientoJugador : public Comportamiento {
  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size) {
      // Inicializar Variables de Estado
      hayPlan = false;
    }
    ComportamientoJugador(std::vector< std::vector< unsigned char> > mapaR) : Comportamiento(mapaR) {
      // Inicializar Variables de Estado
      hayPlan = false;

    }
    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);
    void VisualizaPlan(const estado &st, const list<Action> &plan);
    ComportamientoJugador * clone(){return new ComportamientoJugador(*this);}

  private:
    // Declarar Variables de Estado
    estado actual;
    list<estado> objetivos;
    list<Action> plan;
    bool hayPlan;

    // Métodos privados de la clase
    bool pathFinding(int level, const estado &origen, const list<estado> &destino, list<Action> &plan);
    bool pathFinding_Profundidad(const estado &origen, const estado &destino, list<Action> &plan);
    bool pathFinding_Anchura(const estado &origen, const estado &destino, list<Action> &plan);
    bool pathFinding_CosteUniforme(const estado &origen, const estado &destino, list<Action> &plan);
    bool pathFinding_3_objetivos(const estado &origen, const estado &destino, list<Action> &plan);


    int determinarPeso(estado & actual, estado & siguiente);
    int calculaDistanciaManhattan(const estado & origen, const estado & destino);
    void PintaPlan(list<Action> plan);
    bool HayObstaculoDelante(estado &st);

};


#endif
