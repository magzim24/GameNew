#include <algorithm>
#include "battle.h"
#include "player.h"
#include "card.h"
#include "action.h"
using namespace ::std;

bool Battle::IsCardsRepulsed(Card* trumpCard) {
	for (Action* action : this->actions) {
		if (!(action->IsRepulsed(trumpCard))) {
			return false;
		}
	}
	return true;
}
Battle::Battle() {
	this->currentCardsOnDesk = vector<Card*>();
}
int Battle::AmountOfActions() {
	return this->actions.end() - this->actions.begin();
}
bool Battle::IsCardValueExists(Card* card) {
	if (find(this->currentCardsOnDesk.begin(), 
			 this->currentCardsOnDesk.end(), card)
		!= this->currentCardsOnDesk.end()) {
		return true;
	}
	return false;
}
void Battle::AddValueToCardValueVector(Card* card) {
	if (!IsCardValueExists(card)) {
		this->currentCardsOnDesk.push_back(card);
	}
}
vector<Card*> Battle::GetCurrentCardsOnDesk() {
	return this->currentCardsOnDesk;
}

void Battle::AddAction(Action* action) {
	this->actions.push_back(action);
	if (action->GetAttackingCard()) {
		this->AddValueToCardValueVector(action->GetAttackingCard());
	}
	if (action->GetDefendingCard()) {
		this->AddValueToCardValueVector(action->GetDefendingCard());
	}
	
	
}
const vector<Action*>& Battle::GetAllActionsOfBattle() {
	return actions;
}

void Battle::CardsOnDeskReset() {
	this->currentCardsOnDesk.clear();
}

void Battle::ActionsReset() {
	this->actions.clear();
}