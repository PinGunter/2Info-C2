#include "agent_robot.h"
#include "environment.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <utility>

using namespace std;

// -----------------------------------------------------------
Agent::ActionType Agent::Think()
{
	ActionType accion = actFORWARD;

    if (turn_){
        accion = actTURN_R;
        turn_ = false;
        count_ = false;
        size_ = 1;
    } else{
        if (!CNY70_){
            accion = actFORWARD;
            if (count_){
                size_++;
            }
        }
        else{
            if (count_){
                accion = actIDLE;
                cout << "Tamaño: " << size_ * size_ << endl;
            }
            else{
                accion = actTURN_R;
                turn_ = true;
            }
        }
    }
	return accion;

}
// -----------------------------------------------------------
void Agent::Perceive(const Environment &env)
{
	CNY70_ = env.isFrontier();
	BUMPER_ = env.isBump();
}
// -----------------------------------------------------------
string ActionStr(Agent::ActionType accion)
{
	switch (accion)
	{
	case Agent::actFORWARD: return "FORWARD";
	case Agent::actTURN_L: return "TURN LEFT";
	case Agent::actTURN_R: return "TURN RIGHT";
	case Agent::actBACKWARD: return "BACKWARD";
	case Agent::actPUSH: return "PUSH";
	case Agent::actIDLE: return "IDLE";
	default: return "???";
	}
}
