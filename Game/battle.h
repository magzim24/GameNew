#pragma once
#include <vector>
#include <string>
#include "card.h"
#include "action.h"
#include "player.h"
using namespace ::std;

class Battle {
private:
	vector<Action*> actions;
	vector<Card*> currentCardsOnDesk;
	bool IsCardValueExists(Card*);
public:
	Battle();
	bool IsCardsRepulsed(Card*);
	int AmountOfActions();
	void CardsOnDeskReset();
	void AddValueToCardValueVector(Card*);
	void ActionsReset();
	vector<Card*> GetCurrentCardsOnDesk();
	void AddAction(Action*);
	const vector<Action*>& GetAllActionsOfBattle();
};