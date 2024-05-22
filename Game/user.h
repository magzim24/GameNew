#pragma once
#include <vector>
#include "card.h"
#include "action.h"
#include "player.h"
using namespace ::std;

class User: public Player{
public:
	
	User();
	void setName();
	//virtual string getTypeOfPlayer() override;
};