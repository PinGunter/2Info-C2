#ifndef PLAYER_H
#define PLAYER_H
#define DEPTH 8
#include "environment.h"

double miPuntuacion(const Environment & estado, int jugador);


class Player{
    public:
      Player(int jug);
      Environment::ActionType Think();
      void Perceive(const Environment &env);
      double Poda_AlfaBeta(Environment act, int player, int depth, Environment::ActionType & accion, double alpha, double beta);

    private:
      int jugador_;
      Environment actual_;
};
#endif
