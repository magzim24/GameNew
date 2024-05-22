#pragma once
#include "player.h"
using namespace ::std;

class Bot : public Player {
	
public:
	Bot();
	static int id;
	virtual Action* MakeDecisionAboutAttack(vector<Card*>, Player*) override;
	virtual  Action* MakeDecisionAboutDefend(Action* action, Card* trump_card) override;
private:
	void setName();
	
};
