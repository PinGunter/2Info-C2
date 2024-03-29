#ifndef AGENT__
#define AGENT__

#include <string>
#include <iostream>
using namespace std;

// -----------------------------------------------------------
//				class Agent
// -----------------------------------------------------------
class Environment;
class Agent
{
public:
	Agent(){
	   CNY70_=false;
	   BUMPER_=false;
	   turn_ = false;
	   size_ = count_ = 0;
	}

	enum ActionType
	{
	    actFORWARD,
	    actTURN_L,
	    actTURN_R,
	    actBACKWARD,
	    actPUSH,
	    actIDLE
	};
	void Perceive(const Environment &env);
	ActionType Think();

private:
	bool CNY70_;
	bool BUMPER_;
    bool turn_;
    int size_,count_;

};

string ActionStr(Agent::ActionType);

#endif
